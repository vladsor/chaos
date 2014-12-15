#include <enviroment.h>

#include "floppy.h"
#include "fdc.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* globals */
static volatile bool done = FALSE;
static bool is_disk_change = FALSE;
static volatile bool motor = FALSE;
static volatile int mtick = 0;

static volatile uint64_t motor_time = 0;

static uint8_t fdc_status[7];
static uint8_t statsz = 0;
static uint8_t sr0 = 0;
static uint8_t fdc_track = 0xFF;
static drive_geometry_t geometry = { DG144_HEADS, DG144_TRACKS, DG144_SPT };

uint8_t *dma_buffer = NULL;
uint8_t *address = NULL;

void motor_handler (void);

static bool fdc_wait (bool sensei);

static bool fdc_rw (
    int block,
    uint8_t *blockbuff,
    bool read,
    unsigned long nosectors);

void block2hts (int block,int *head,int *track,int *sector);
void floppy_irq_handler (unsigned int irq_number);

/* Program DMA for transfer. */
static inline bool floppy_dma_transfer (unsigned int length, bool read)
{
  dma_transfer (FLOPPY_DMA_CHANNEL, length, 
    read ? STORM_DMA_OPERATION_READ : STORM_DMA_OPERATION_WRITE, 
    STORM_DMA_TRANSFER_MODE_SINGLE, FALSE);

  return TRUE;
}       

#if FALSE
/*
 * Drive parameters (user modifiable)
 */
typedef struct floppy_drive_params 
{
  char cmos;                    /* cmos type */
        
  /* Spec2 is (HLD<<1 | ND), where HLD is head load time (1=2ms, 2=4 ms 
   * etc) and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA).
   */
  unsigned long max_dtr;                /* Step rate, usec */
  unsigned long hlt;                    /* Head load/settle time, msec */
  unsigned long hut;                    /* Head unload time (remnant of 
                                         * 8" drives) */
  unsigned long srt;                    /* Step rate, usec */

  unsigned long spinup;         /* time needed for spinup (expressed
                                 * in jiffies) */
  unsigned long spindown;               /* timeout needed for spindown */
  unsigned char spindown_offset;        /* decides in which position the disk
                                         * will stop */
  unsigned char select_delay;   /* delay to wait after select */
  unsigned char rps;            /* rotations per second */
  unsigned char tracks;         /* maximum number of tracks */
  unsigned long timeout;                /* timeout for interrupt requests */
        
  unsigned char interleave_sect;        /* if there are more sectors, use 
                                         * interleave */
        
  struct floppy_max_errors max_errors;
        
  char flags;                   /* various flags, including ftd_msg */
/*
 * Announce successful media type detection and media information loss after
 * disk changes.
 * Also used to enable/disable printing of overrun warnings.
 */

#define FTD_MSG 0x10
#define FD_BROKEN_DCL 0x20
#define FD_DEBUG 0x02
#define FD_SILENT_DCL_CLEAR 0x4
#define FD_INVERTED_DCL 0x80

  char read_track;              /* use readtrack during probing? */

/*
 * Auto-detection. Each drive type has eight formats which are
 * used in succession to try to read the disk. If the FDC cannot lock onto
 * the disk, the next format is tried. This uses the variable 'probing'.
 */
  short autodetect[8];          /* autodetected formats */
        
  int checkfreq; /* how often should the drive be checked for disk 
                        * changes */
  int native_format; /* native format of this drive */
};

/*
 * this struct defines the different floppy drive types.
 */
typedef struct 
{
  floppy_drive_params params;
  const char *name; /* name printed while booting */
} floppy_drive_type;

floppy_drive_type default_drive_params[]= 
{
/* NOTE: the time values in jiffies should be in msec!
 CMOS drive type
  |    Maximum data rate supported by drive type
  |    |  Head load time, msec
  |    |  |   Head unload time, msec (not used)
  |    |  |   |     Step rate interval, usec
  |    |  |   |     |       Time needed for spinup time (jiffies)
  |    |  |   |     |       |      Timeout for spinning down (jiffies)
  |    |  |   |     |       |      |   Spindown offset (where disk stops)
  |    |  |   |     |       |      |   |     Select delay
  |    |  |   |     |       |      |   |     |     RPS
  |    |  |   |     |       |      |   |     |     |    Max number of tracks
  |    |  |   |     |       |      |   |     |     |    |     Interrupt timeout
  |    |  |   |     |       |      |   |     |     |    |     |   Max nonintlv. sectors
  |    |  |   |     |       |      |   |     |     |    |     |   | -Max Errors- flags */
{{0, 500,16, 16, 8000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  80, 3*HZ, 20, {3,1,2,0,2}, 0,
      0, { 7, 4, 8, 2, 1, 5, 3,10}, 3*HZ/2, 0 }, "unknown" },

{{1, 300,16, 16, 8000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  40, 3*HZ, 17, {3,1,2,0,2}, 0,
     0, { 1, 0, 0, 0, 0, 0, 0, 0}, 3*HZ/2, 1 }, "360K PC" }, /*5 1/4 360 KB PC*/

{{2, 500,16, 16, 6000, 4*HZ/10, 3*HZ, 14, SEL_DLY, 6,  83, 3*HZ, 17, {3,1,2,0,2}, 0,
      0, { 2, 5, 6,23,10,20,12, 0}, 3*HZ/2, 2 }, "1.2M" }, /*5 1/4 HD AT*/

{{3, 250,16, 16, 3000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  83, 3*HZ, 20, {3,1,2,0,2}, 0,
      0, { 4,22,21,30, 3, 0, 0, 0}, 3*HZ/2, 4 }, "720k" }, /*3 1/2 DD*/

{{4, 500,16, 16, 4000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 20, {3,1,2,0,2}, 0,
      0, { 7, 4,25,22,31,21,29,11}, 3*HZ/2, 7 }, "1.44M" }, /*3 1/2 HD*/

{{5,1000,15,  8, 3000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 40, {3,1,2,0,2}, 0,
      0, { 7, 8, 4,25,28,22,31,21}, 3*HZ/2, 8 }, "2.88M AMI BIOS" }, /*3 1/2 ED*/

{{6,1000,15,  8, 3000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 40, {3,1,2,0,2}, 0,
      0, { 7, 8, 4,25,28,22,31,21}, 3*HZ/2, 8 }, "2.88M" } /*3 1/2 ED*/
/*    |  --autodetected formats---    |      |      |
 *    read_track                      |      |    Name printed when booting
 *                                    |     Native format
 *                  Frequency of disk change checks */
};

/*
 * Geometry
 */
typedef struct
{
  /* nr of sectors total */
  uint32_t size;     

  /* sectors per track */
  uint32_t sectors_per_track;

  /* nr of heads */
  uint32_t number_of_heads;

  /* nr of tracks */
  uint32_t number_of_tracks;

  /* !=0 means double track steps */
  uint32_t stretch;   

  /* gap1 size */
  uint8_t gap;     

  /* data rate. |= 0x40 for perpendicular */
  uint8_t rate;    

  /* stepping rate, head unload time */
  uint8_t spec1;   

  /* gap2 size */
  uint8_t fmt_gap; 

  /* used only for predefined formats */
  const char *name;      
} floppy_type_t;


/*
 * This struct defines the different floppy types.
 *
 * Bit 0 of 'stretch' tells if the tracks need to be doubled for some
 * types (e.g. 360kB diskette in 1.2MB drive, etc.).  Bit 1 of 'stretch'
 * tells if the disk is in Commodore 1581 format, which means side 0 sectors
 * are located on side 1 of the disk but with a side 0 ID, and vice-versa.
 * This is the same as the Sharp MZ-80 5.25" CP/M disk format, except that the
 * 1581's logical side 0 is on physical side 1, whereas the Sharp's logical
 * side 0 is on physical side 0 (but with the misnamed sector IDs).
 * 'stretch' should probably be renamed to something more general, like
 * 'options'.  Other parameters should be self-explanatory (see also
 * setfdprm(8)).
 */
static floppy_type_t floppy_type[32] = 
{
  {   0, 0, 0,  0, 0, 0x00, 0x00, 0x00, 0x00, NULL   }, /*  0 no testing    */
  { 720, 9, 2, 40, 0, 0x2A, 0x02, 0xDF, 0x50, "d360" }, /*  1 360KB PC      */
  {2400,15, 2, 80, 0, 0x1B, 0x00, 0xDF, 0x54, "h1200"}, /*  2 1.2MB AT      */
  { 720, 9, 1, 80, 0, 0x2A, 0x02, 0xDF, 0x50, "D360" }, /*  3 360KB SS 3.5" */
  {1440, 9, 2, 80, 0, 0x2A, 0x02, 0xDF, 0x50, "D720" }, /*  4 720KB 3.5"    */
  { 720, 9, 2, 40, 1, 0x23, 0x01, 0xDF, 0x50, "h360" }, /*  5 360KB AT      */
  {1440, 9, 2, 80, 0, 0x23, 0x01, 0xDF, 0x50, "h720" }, /*  6 720KB AT      */
  {2880,18, 2, 80, 0, 0x1B, 0x00, 0xCF, 0x6C, "H1440"}, /*  7 1.44MB 3.5"   */
  {5760,36, 2, 80, 0, 0x1B, 0x43, 0xAF, 0x54, "E2880"}, /*  8 2.88MB 3.5"   */
  {6240,39, 2, 80, 0, 0x1B, 0x43, 0xAF, 0x28, "E3120"}, /*  9 3.12MB 3.5"   */

  {2880,18, 2, 80, 0, 0x25, 0x00, 0xDF, 0x02, "h1440"}, /* 10 1.44MB 5.25"  */
  {3360,21, 2, 80, 0, 0x1C, 0x00, 0xCF, 0x0C, "H1680"}, /* 11 1.68MB 3.5"   */
  { 820,10, 2, 41, 1, 0x25, 0x01, 0xDF, 0x2E, "h410" }, /* 12 410KB 5.25"   */
  {1640,10, 2, 82, 0, 0x25, 0x02, 0xDF, 0x2E, "H820" }, /* 13 820KB 3.5"    */
  {2952,18, 2, 82, 0, 0x25, 0x00, 0xDF, 0x02, "h1476"}, /* 14 1.48MB 5.25"  */
  {3444,21, 2, 82, 0, 0x25, 0x00, 0xDF, 0x0C, "H1722"}, /* 15 1.72MB 3.5"   */
  { 840,10, 2, 42, 1, 0x25, 0x01, 0xDF, 0x2E, "h420" }, /* 16 420KB 5.25"   */
  {1660,10, 2, 83, 0, 0x25, 0x02, 0xDF, 0x2E, "H830" }, /* 17 830KB 3.5"    */
  {2988,18, 2, 83, 0, 0x25, 0x00, 0xDF, 0x02, "h1494"}, /* 18 1.49MB 5.25"  */
  {3486,21, 2, 83, 0, 0x25, 0x00, 0xDF, 0x0C, "H1743"}, /* 19 1.74 MB 3.5"  */

  {1760,11, 2, 80, 0, 0x1C, 0x09, 0xCF, 0x00, "h880" }, /* 20 880KB 5.25"   */
  {2080,13, 2, 80, 0, 0x1C, 0x01, 0xCF, 0x00, "D1040"}, /* 21 1.04MB 3.5"   */
  {2240,14, 2, 80, 0, 0x1C, 0x19, 0xCF, 0x00, "D1120"}, /* 22 1.12MB 3.5"   */
  {3200,20, 2, 80, 0, 0x1C, 0x20, 0xCF, 0x2C, "h1600"}, /* 23 1.6MB 5.25"   */
  {3520,22, 2, 80, 0, 0x1C, 0x08, 0xCF, 0x2e, "H1760"}, /* 24 1.76MB 3.5"   */
  {3840,24, 2, 80, 0, 0x1C, 0x20, 0xCF, 0x00, "H1920"}, /* 25 1.92MB 3.5"   */
  {6400,40, 2, 80, 0, 0x25, 0x5B, 0xCF, 0x00, "E3200"}, /* 26 3.20MB 3.5"   */
  {7040,44, 2, 80, 0, 0x25, 0x5B, 0xCF, 0x00, "E3520"}, /* 27 3.52MB 3.5"   */
  {7680,48, 2, 80, 0, 0x25, 0x63, 0xCF, 0x00, "E3840"}, /* 28 3.84MB 3.5"   */

  {3680,23, 2, 80, 0, 0x1C, 0x10, 0xCF, 0x00, "H1840"}, /* 29 1.84MB 3.5"   */
  {1600,10, 2, 80, 0, 0x25, 0x02, 0xDF, 0x2E, "D800" }, /* 30 800KB 3.5"    */
  {3200,20, 2, 80, 0, 0x1C, 0x00, 0xCF, 0x2C, "H1600"}, /* 31 1.6MB 3.5"    */
};
#endif

/* init driver */
bool floppy_driver_init (void)
{
  int version;
  
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Initing Floppy Drive...\n");
  
//  system_call_port_range_register (0x3F2, 6, "Floppy drive controller");

  /* Register the DMA channel. */
  dma_register (FLOPPY_DMA_CHANNEL, (void **) &dma_buffer);

  /* install IRQ6 handler */
//  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
//  {
//    irq_handler ();
//  }
  irq_register (FLOPPY_IRQ_CHANNEL, floppy_irq_handler);

//  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
//  {
//    motor_handler ();
//  }
//  timer_register (motor_handler, 100);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Initialising Floppy driver...\n");

  fdc_reset ();

  version = fdc_get_version ();
  
  if (version == FDC_TYPE_NONE || version == FDC_TYPE_UNKNOWN)
  {
    return FALSE;
  }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Initing Floppy Drive... End.\n");
  
  return TRUE;
}

/* Interrupt handler. */
#if 0
void irq_handler (void)
{
  system_call_thread_name_set ("IRQ handler");

  if (system_call_irq_register (6, "Floppy Drive") != STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
               "Could not allocate IRQ %d.", 6);
    return;
  }

  while (TRUE)
  {
    system_call_irq_wait (6);

    /* signal operation finished */
    done = TRUE;

    system_call_irq_acknowledge (6);
  }
}
#endif

void floppy_irq_handler (unsigned int irq_number UNUSED)
{
    done = TRUE;
}

#if 0
void motor_handler (void)
{
  system_call_thread_name_set ("Motor handler");

  while (TRUE)
  {
    timer_sleep_milli (100);

    if (mtick > 0)
    {
      mtick -= 100;
      if (mtick <= 0)
      {
        /* turn off floppy motor */
        system_port_out_u8 (FDC_REGISTER_DIGITAL_OUTPUT, 0x0C);  
        motor = FALSE;
      }
    }
  }
}
#endif
void motor_handler (void)
{
    if (mtick > 0)
    {
	mtick -= 0;
	if (mtick <= 0)
	{
	    port_uint8_out (FDC_REGISTER_DIGITAL_OUTPUT, 0x0C);
	}
    }
}

/* this waits for FDC command to complete */
bool fdc_wait (bool sensei)
{
   bool is_time_out = FALSE;
   int i;

   DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Waiting Floppy Drive...\n");

   /* wait for IRQ6 handler to signal command finished */
   /* set timeout to 1 second */
   for (i = 0 ; i < 100 ; i++)
   {
     if (done)
     {
       break;
     }
     timer_sleep_milli (10);
   } 
   
   is_time_out = (i == 100);
   
   /* read in command result bytes */
   statsz = 0;
   
   while ((statsz < 7) && 
          (port_uint8_in (FDC_REGISTER_MAIN_STATUS) & (1 << 4))) 
   {
      fdc_status[statsz] = fdc_get_byte ();
//      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
//                           "status[%u]=%u.", statsz, status[statsz]);
      statsz++;
   }
   
//   log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
//                        "status[0]=%u.", status[0]);

   if (sensei) 
   {
      /* send a "sense interrupt status" command */
      fdc_output_byte (COMMAND_SENSEI);
      sr0 = fdc_get_byte ();
      fdc_track = fdc_get_byte ();
   }

   DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Waiting Floppy Drive... done.\n");

   done = FALSE;
   
   if (is_time_out) 
   {
      /* timed out! */
      
      /* check for diskchange */
      if (port_uint8_in (FDC_REGISTER_DIGITAL_INPUT) & 0x80)  
      {
        is_disk_change = TRUE;
      }

      DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Time outed.\n");
      return FALSE;
   }
   
   return TRUE;
}

/*
 * converts linear block address to head/track/sector
 * 
 * blocks are numbered 0..heads*tracks*spt-1
 * blocks 0..spt-1 are serviced by head #0
 * blocks spt..spt*2-1 are serviced by head 1
 * 
 * WARNING: garbage in == garbage out
 */
void block2hts (int block, int *head, int *track, int *sector)
{
   *head = (block % (geometry.sectors_per_track * geometry.heads)) / 
           geometry.sectors_per_track;

   *track = block / (geometry.sectors_per_track * geometry.heads);

   *sector = block % geometry.sectors_per_track + 1;
}



/**** disk operations ****/

/* this gets the FDC to a known state */
void fdc_reset (void)
{
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Reseting Floppy Drive...\n");


  /* stop the motor and disable IRQ/DMA */
  port_uint8_out (FDC_REGISTER_DIGITAL_OUTPUT, 0);
   
  mtick = 0;
  motor_time = 0;
  motor = FALSE;

  /* program data rate (500K/s) */
  port_uint8_out (FDC_REGISTER_DATA_RATE_SELECT, 0);

  /* re-enable interrupts */
  port_uint8_out (FDC_REGISTER_DIGITAL_OUTPUT, 0x0C);

  /* resetting triggered an interrupt - handle it */
  done = TRUE;
  fdc_wait (TRUE);

  /* specify drive timings (got these off the BIOS) */
  fdc_output_byte (COMMAND_SPECIFY);
  fdc_output_byte (0xdf);  /* SRT = 3ms, HUT = 240ms */
  fdc_output_byte (0x02);  /* HLT = 16ms, ND = 0 */
   
  /* clear "disk change" status */
  floppy_seek (1);
  floppy_recalibrate ();

  is_disk_change = FALSE;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Reseting Floppy Drive... End.\n");
}

/* this returns whether there was a disk change */
bool disk_change(void)
{
  return is_disk_change;
}

/* this turns the motor on */
void fdc_motor_on (void)
{
  if (!motor) 
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Motor On.\n");

    /* stop motor kill countdown */
    mtick = -1;     

    port_uint8_out (FDC_REGISTER_DIGITAL_OUTPUT, 0x1C);

    /* delay 500ms for motor to spin up */
    timer_sleep_milli (500); 
    motor = TRUE;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Motor END.\n");
  }
}

/* this turns the motor off */
void fdc_motor_off (void)
{
  if (motor) 
  {
    /* start motor kill countdown: 2s */
    mtick = 2000;   
  }
}

/* floppy_recalibrate the drive */
void floppy_recalibrate (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Floppy drive recalibrate.\n");

    /* turn the motor on */
    fdc_motor_on ();
   
    /* send actual command bytes */
    fdc_output_byte (COMMAND_RECALIBRATE);
    fdc_output_byte (0);

    /* wait until seek finished */
    fdc_wait (TRUE);
   
    /* turn the motor off */
    fdc_motor_off ();
}

/* seek to track */
bool floppy_seek (int track)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Floppy drive seek.\n");

    if (fdc_track == track)  /* already there? */
    {
        return TRUE;
    }
   
    fdc_motor_on ();
   
    /* send actual command bytes */
    fdc_output_byte (COMMAND_SEEK);
    fdc_output_byte (0);
    fdc_output_byte (track);

    /* wait until seek finished */
    if (!fdc_wait (TRUE))
    {
	    /* timeout! */
	    return FALSE;     
    }

    /* now let head settle for 15ms */
    timer_sleep_milli (15);
   
    fdc_motor_off ();
   
    /* check that seek worked */
    if ((sr0 != 0x20) || (fdc_track != track))
    {
	    return FALSE;
    }

    return TRUE;
}

/* checks drive geometry - call this after any disk change */
bool log_disk (drive_geometry_t *g)
{
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Checking drive geometry...");

  /* get drive in a known status before we do anything */
  fdc_reset ();

  /* assume disk is 1.68M and try and read block #21 on first track */
  geometry.heads = DG168_HEADS;
  geometry.tracks = DG168_TRACKS;
  geometry.sectors_per_track = DG168_SPT;

  if (floppy_driver_read_block (20, NULL, 1)) 
  {
    /* disk is a 1.68M disk */
    if (g) 
    {
      g->heads = geometry.heads;
      g->tracks = geometry.tracks;
      g->sectors_per_track = geometry.sectors_per_track;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "+ 1.68M");
    return TRUE;             
  }
   
  /* OK, not 1.68M - try again for 1.44M reading block #18 on first track */
  geometry.heads = DG144_HEADS;
  geometry.tracks = DG144_TRACKS;
  geometry.sectors_per_track = DG144_SPT;

  if (floppy_driver_read_block (17, NULL, 1)) 
  {
    /* disk is a 1.44M disk */
    if (g) 
    {
      g->heads = geometry.heads;
      g->tracks = geometry.tracks;
      g->sectors_per_track = geometry.sectors_per_track;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "+ 1.44M");
    return TRUE;
  }
   
  /* it's not 1.44M or 1.68M - we don't support it */
  DEBUG_PRINT (DEBUG_LEVEL_WARNING, "- Unknown");
  
  return FALSE;
}

/* read block (blockbuff is 512 byte buffer) */
bool floppy_driver_read_block (
    int block, 
    uint8_t *blockbuff, 
    unsigned long nosectors)
{
  int track = 0, sector = 0, head = 0, track2 = 0, result = 0;
  unsigned long loop = 0;

  /* The FDC can read multiple sides at once but not multiple tracks */
        
  block2hts (block, &head, &track, &sector);
  block2hts (block + nosectors, &head, &track2, &sector);

  if (track != track2)
  {
    for (loop = 0 ; loop < nosectors ; loop++)
    {
      result = fdc_rw (block + loop, blockbuff + (loop * 512), TRUE, 1);
    }
    return result;
  }
  
  return fdc_rw (block, blockbuff, TRUE, nosectors);
}

/* write block (blockbuff is 512 byte buffer) */
bool floppy_driver_write_block (
    int block, 
    uint8_t *blockbuff, 
    unsigned long nosectors)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Writing block...");
	
    return fdc_rw (block, blockbuff, FALSE, nosectors);
}

/*
 * since reads and writes differ only by a few lines, this handles both.  This
 * function is called by read_block() and write_block()
 */
bool fdc_rw (int block, uint8_t *blockbuff, bool read, unsigned long nosectors)
{
    unsigned int head, track, sector, tries;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Read/Write operation...");
   
    /* convert logical address into physical address */
    block2hts (block, &head, &track, &sector);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
       "head = %u, track = %u, sector = %u", 
       head, track, sector);
   
    /* spin up the disk */
    fdc_motor_on ();

    if (!read) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "copy data from data buffer into track buffer ...");

	/* copy data from data buffer into track buffer */
	memory_copy (dma_buffer, blockbuff, nosectors * 512);
    }
   
    for (tries = 0 ; tries < 3 ; tries++) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "TRY=%u", tries);

	/* check for diskchange */
	if (port_uint8_in (FDC_REGISTER_DIGITAL_INPUT) & 0x80) 
	{
	    is_disk_change = TRUE;

	    /* clear "disk change" status */
	    floppy_seek (1);  
	    floppy_recalibrate ();
	    fdc_motor_off ();
      
	    DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
		"Disk change detected. Trying again.\n");
         
	    return fdc_rw (block, blockbuff, read, nosectors);
	}
    
	/* move head to right track */
	if (!floppy_seek (track)) 
	{
	    fdc_motor_off ();
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Error seeking to track.\n");

	    return FALSE;
	}
      
	/* program data rate (500K/s) */
	port_uint8_out (FDC_REGISTER_CONFIGURATION_CONTROL, 0);

	/* send command */
	if (read)
	{
	    floppy_dma_transfer (nosectors * 512, FALSE);

	    fdc_output_byte (COMMAND_READ);
	}  
	else 
	{
	    floppy_dma_transfer (nosectors * 512, TRUE);

	    fdc_output_byte (COMMAND_WRITE);
	}
      
	fdc_output_byte (head << 2);
	fdc_output_byte (track);
	fdc_output_byte (head);
	fdc_output_byte (sector);

        /* 512 bytes/sector */
	fdc_output_byte (2);               
	fdc_output_byte (geometry.sectors_per_track);

	if (geometry.sectors_per_track == DG144_SPT)
	{
	    /* gap 3 size for 1.44M read/write */
	    fdc_output_byte (DG144_GAP3RW);  
	}
	else
	{
	    /* gap 3 size for 1.68M read/write */      
	    fdc_output_byte (DG168_GAP3RW);  
	}
      
	/* DTL = unused */
	fdc_output_byte (0xFF);            
      
	/* wait for command completion */
        /* read/write don't need "sense interrupt status" */
	if (!fdc_wait (FALSE)) 
        {
	    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
		"Timed out, trying operation again after reset().\n");
		 
	    fdc_reset ();
	    return fdc_rw (block, blockbuff, read, nosectors);
	}
      
	if ((fdc_status[0] & 0xC0) == 0)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
              "Operation Ok[%u]", fdc_status[0]);

	    /* worked! outta here! */
	    break;
	}

	/* oops, try again... */
	floppy_recalibrate ();  
    }
   
    /* stop the motor */
    fdc_motor_off ();

    if (read && (blockbuff != NULL)) 
    {
	/* copy data from track buffer into data buffer */
	memory_copy (blockbuff, dma_buffer, nosectors * 512);
    }

    return (tries != 3);
}

/* this formats a track, given a certain geometry */
bool format_track (uint8_t track, drive_geometry_t *g)
{
  int head;
  int sector;
  int sector_id;
  int split;
  uint8_t temp_buffer[256];
  unsigned int i;

  /* check geometry */
  if ((g->sectors_per_track != DG144_SPT) && 
      (g->sectors_per_track != DG168_SPT))
  {
    return FALSE;
  }
   
  /* spin up the disk */
  fdc_motor_on ();

  /* program data rate (500K/s) */
  port_uint8_out (FDC_REGISTER_CONFIGURATION_CONTROL, 0);

  /* seek to track */
  floppy_seek (track);  

  /* precalc some constants for interleave calculation */
  split = g->sectors_per_track / 2;

  if (g->sectors_per_track & 1) 
  {
    split++;
  }
     
  for (head = 0 ; head < g->heads ; head++) 
  {
    /* for each head... */
      
    /* check for diskchange */
    if (port_uint8_in (FDC_REGISTER_DIGITAL_INPUT) & 0x80) 
    {
      is_disk_change = TRUE;

      /* clear "disk change" status */
      floppy_seek (1);  
      floppy_recalibrate ();
      fdc_motor_off ();

      return FALSE;
    }

    /* reset buffer index */
    i = 0;   

    for (sector = 0 ; sector < g->sectors_per_track ; sector++) 
    {
      /* for each sector... */

      /* calculate 1:2 interleave */
      sector_id = sector / 2 + 1;
      
      if (sector & 1)
      {
        sector_id += split;
      }
         
      /* add some head skew (2 sectors should be enough) */
      if (head & 1) 
      {
        sector_id -= 2;
        if (sector_id < 1)
        {
          sector_id += g->sectors_per_track;
        }
      }
      
      /* add some track skew (1/2 a revolution) */
      if (track & 1) 
      {
        sector_id -= g->sectors_per_track / 2;
        if (sector_id < 1)
        {
          sector_id += g->sectors_per_track;
        }
      }
         
      /**** interleave now calculated - sector ID is stored in r_id ****/

      /* fill in sector ID's */
      temp_buffer[i++] = track;
      temp_buffer[i++] = head;
      temp_buffer[i++] = sector_id;
      temp_buffer[i++] = 2;
    }

    /* copy sector ID's to track buffer */

    memory_copy (dma_buffer, temp_buffer, i);
      
    /* start dma xfer */

    floppy_dma_transfer (i, TRUE);
      
    /* prepare "format track" command */
    fdc_output_byte (COMMAND_FORMAT);
    fdc_output_byte (head << 2);
    fdc_output_byte (2);
    fdc_output_byte (g->sectors_per_track);

    if (g->sectors_per_track == DG144_SPT)
    {
      /* gap3 size for 1.44M format */      
      fdc_output_byte (DG144_GAP3FMT);    
    }
    else
    {
      /* gap3 size for 1.68M format */
      fdc_output_byte (DG168_GAP3FMT);    
    }
  
    /* filler byte */
    fdc_output_byte (0);     
         
    /* wait for command to finish */
    if (!fdc_wait (FALSE))
    {
      return FALSE;
    }
      
    if (fdc_status[0] & 0xC0) 
    {
      fdc_motor_off ();
      return FALSE;
    }
  }
  
  fdc_motor_off ();
   
  return TRUE;
}
