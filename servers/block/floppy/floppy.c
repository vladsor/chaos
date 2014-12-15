/*
GazOS Operating System
Copyright (C) 1999  Gareth Owen <gaz@athene.co.uk>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "config.h"
#include "floppy.h"

/* globals */
static volatile bool done = FALSE;
static bool is_disk_change = FALSE;
static bool motor = FALSE;
static int mtick = 0;

static volatile time_type motor_time = 0;
static volatile time_type time_out = 0;

static volatile int tmout = 0;
static BYTE status[7] = { 0 };
static BYTE statsz = 0;
static BYTE sr0 = 0;
static BYTE fdc_track = 0xff;
static drive_geometry_type geometry = { DG144_HEADS, DG144_TRACKS, DG144_SPT };

u8 *dma_buffer;

/* prototypes */
void sendbyte(int byte);
int getbyte(void);
void irq6(void);
void int1c(void);
static bool waitfdc(bool sensei);
static bool fdc_rw(int block,BYTE *blockbuff,bool read,unsigned long nosectors);
void block2hts(int block,int *head,int *track,int *sector);
void irq_handler (void);

/* Program DMA for transfer. */
static bool dma_transfer (u8 *buffer, unsigned int length, bool direction)
{
  if (!direction)
  {
    log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
               "DMA read transfer...");
    if (system_call_dma_transfer (FLOPPY_DMA_CHANNEL, length,
                                       STORM_DMA_OPERATION_WRITE,
                                       STORM_DMA_TRANSFER_MODE_BLOCK,
                                       STORM_DMA_AUTOINIT_ENABLE) != TRUE)
    {
      log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
                 "DMA transfer failed!!.");
      return FALSE;
    }
  }
  else
  {
    log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
               "DMA write transfer...");
    if (system_call_dma_transfer (FLOPPY_DMA_CHANNEL, length,
                                       STORM_DMA_OPERATION_READ,
                                       STORM_DMA_TRANSFER_MODE_BLOCK,
                                       STORM_DMA_AUTOINIT_ENABLE) != TRUE)
    {
      log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
                 "DMA transfer failed!!.");
      return FALSE;
    }
  }
  return TRUE;
}

/* helper functions */

/* init driver */
bool init (void)
{
   int i;

   log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Initing Floppy Drive...");

   system_call_port_range_register(0x3F2, 6, "Floppy drive controller");
   
   /* install IRQ6 handler */
   if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
   {
     irq_handler ();
   }

  /* Register the DMA channel. */

  if (system_call_dma_register (FLOPPY_DMA_CHANNEL, 
      (void **) &dma_buffer) != STORM_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_ERROR,
               "Cannot register DMA");
    return FALSE;
  }

  reset ();

  /* get floppy controller version */
  sendbyte (COMMAND_VERSION);
  i = getbyte();

  log_print (&log_structure, LOG_URGENCY_INFORMATIVE, 
             "Initialising Floppy driver...  ");

  if (i == 0x80)
  {
    log_print (&log_structure, LOG_URGENCY_INFORMATIVE, 
               "NEC765 controller found");
  }
  else
  {
    log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE, 
                         "Enhanced controller found, version: %lu", i);
  }
  log_print (&log_structure, LOG_URGENCY_DEBUG, 
             "Initing Floppy Drive... End");
  return TRUE;
}

/* Interrupt handler. */

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
    irq6 ();
    system_call_irq_acknowledge (6);
  }
}

/* deinit driver */
//void deinit(void)
//{
//   set_irq_handler(6,NULL,&oldirq6);
//   kprint("uninstalling IRQ6 handler\n");
//   set_irq_handler(0x1c,NULL,&oldint1c);
//   kprint("uninstalling timer handler\n");
//   
//   /* stop motor forcefully */
//   system_port_out_u8(FDC_DOR,0x0c);
//}

/* sendbyte() routine from intel manual */
void sendbyte(int byte)
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0;tmo < 128;tmo++) 
   {
      msr = system_port_in_u8 (FDC_MSR);
      if ((msr & 0xc0) == 0x80) 
      {
	 system_port_out_u8 (FDC_DATA,byte);
	 return;
      }
//      system_port_in_u8(0x80);   /* delay */
   }
}

/* getbyte() routine from intel manual */
int getbyte(void)
{
   volatile int msr;
   int tmo;
   
   for ( tmo = 0 ; tmo < 128 ; tmo++ ) 
   {
      msr = system_port_in_u8 (FDC_MSR);
      if ((msr & 0xd0) == 0xd0) 
      {
	 return system_port_in_u8 (FDC_DATA);
      } 
//      system_port_in_u8(0x80);   /* delay */
   }

   return -1;   /* read timeout */
}

/* this waits for FDC command to complete */
bool waitfdc (bool sensei)
{
   time_type begin_time, current_time;
   bool is_time_out = FALSE;
   
   log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Waiting Floppy Drive...");

   /* set timeout to 1 second */
   time_out = 1000;
   
   system_call_timer_read (&begin_time);

   /* wait for IRQ6 handler to signal command finished */
   do
   {
     system_call_timer_read (&current_time);
     is_time_out = (current_time >= begin_time + time_out);
   } while (!done && !is_time_out);
   
   /* read in command result bytes */
   statsz = 0;
   while ((statsz < 7) && (system_port_in_u8(FDC_MSR) & (1<<4))) 
   {
      status[statsz++] = getbyte();
   }

   if (sensei) 
   {
      /* send a "sense interrupt status" command */
      sendbyte(COMMAND_SENSEI);
      sr0 = getbyte();
      fdc_track = getbyte();
   }

   log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Waiting Floppy Drive... done");
   
   done = FALSE;
   
   if (is_time_out) 
   {
      /* timed out! */
      if (system_port_in_u8(FDC_DIR) & 0x80)  /* check for diskchange */
      {
	is_disk_change = TRUE;
      }
      return FALSE;
   } 
   else
   {
     return TRUE;
   }
}

/* This is the IRQ6 handler */
void irq6(void)
{
   /* signal operation finished */
   done = TRUE;
}

/* This is the timer (int 1ch) handler */
void int1c(void)
{
   if (tmout) --tmout;     /* bump timeout */
   
   if (mtick > 0)
     --mtick;
   else if (!mtick && motor) {
      system_port_out_u8(FDC_DOR,0x0c);  /* turn off floppy motor */
      motor = FALSE;
   }
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
void block2hts(int block,int *head,int *track,int *sector)
{
   *head = (block % (geometry.spt * geometry.heads)) / (geometry.spt);
   *track = block / (geometry.spt * geometry.heads);
   *sector = block % geometry.spt + 1;
}



/**** disk operations ****/

/* this gets the FDC to a known state */
void reset(void)
{
   log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Reseting Floppy Drive...");

   /* stop the motor and disable IRQ/DMA */
   system_port_out_u8(FDC_DOR,0);
   
   mtick = 0;
   motor_time = 0;
   motor = FALSE;

   /* program data rate (500K/s) */
   system_port_out_u8 (FDC_DRS, 0);

   /* re-enable interrupts */
   system_port_out_u8 (FDC_DOR, 0x0c);

   /* resetting triggered an interrupt - handle it */
   done = TRUE;
   waitfdc (TRUE);

   /* specify drive timings (got these off the BIOS) */
   sendbyte (COMMAND_SPECIFY);
   sendbyte (0xdf);  /* SRT = 3ms, HUT = 240ms */
   sendbyte (0x02);  /* HLT = 16ms, ND = 0 */
   
   /* clear "disk change" status */
   seek (1);
   recalibrate ();

   is_disk_change = FALSE;
   
   log_print(&log_structure, LOG_URGENCY_DEBUG, 
             "Reseting Floppy Drive... End");
}

/* this returns whether there was a disk change */
bool disk_change(void)
{
   return is_disk_change;
}

/* this turns the motor on */
void motor_on(void)
{
  if (!motor) 
  {
    log_print(&log_structure, LOG_URGENCY_DEBUG, "Motor On");
    mtick = -1;     /* stop motor kill countdown */
    system_port_out_u8 (FDC_DOR,0x1c);
    system_sleep (500); /* delay 500ms for motor to spin up */
    motor = TRUE;
  }
}

/* this turns the motor off */
void motor_off(void)
{
  if (motor) 
  {
    log_print(&log_structure, LOG_URGENCY_DEBUG, "Motor Off");
    mtick = 13500;   /* start motor kill countdown: 36 ticks ~ 2s */
  }
}

/* recalibrate the drive */
void recalibrate (void)
{
   /* turn the motor on */
   motor_on ();
   
   /* send actual command bytes */
   sendbyte (COMMAND_RECALIBRATE);
   sendbyte (0);

   /* wait until seek finished */
   waitfdc (TRUE);
   
   /* turn the motor off */
   motor_off ();
}

/* seek to track */
bool seek (int track)
{
   if (fdc_track == track)  /* already there? */
   {
     return TRUE;
   }
   
   motor_on ();
   
   /* send actual command bytes */
   sendbyte (COMMAND_SEEK);
   sendbyte (0);
   sendbyte (track);

   /* wait until seek finished */
   if (!waitfdc (TRUE))
   {
     return FALSE;     /* timeout! */
   }

   /* now let head settle for 15ms */
   system_sleep(15);
   
   motor_off ();
   
   /* check that seek worked */
   if ((sr0 != 0x20) || (fdc_track != track))
   {
     return FALSE;
   }
   else
   {
     return TRUE;
   }
}

/* checks drive geometry - call this after any disk change */
bool log_disk (drive_geometry_type *g)
{
   /* get drive in a known status before we do anything */
   reset ();

   /* assume disk is 1.68M and try and read block #21 on first track */
   geometry.heads = DG168_HEADS;
   geometry.tracks = DG168_TRACKS;
   geometry.spt = DG168_SPT;

   if (read_block(20,NULL,1)) 
   {
      /* disk is a 1.68M disk */
      if (g) 
      {
	 g->heads = geometry.heads;
	 g->tracks = geometry.tracks;
	 g->spt = geometry.spt;
      }
      return TRUE;             
   }
   
   /* OK, not 1.68M - try again for 1.44M reading block #18 on first track */
   geometry.heads = DG144_HEADS;
   geometry.tracks = DG144_TRACKS;
   geometry.spt = DG144_SPT;

   if (read_block(17,NULL,1)) 
   {
      /* disk is a 1.44M disk */
      if (g) 
      {
	 g->heads = geometry.heads;
	 g->tracks = geometry.tracks;
	 g->spt = geometry.spt;
      }
      return TRUE;
   }
   
   /* it's not 1.44M or 1.68M - we don't support it */
   return FALSE;
}

/* read block (blockbuff is 512 byte buffer) */
bool read_block (int block, BYTE *blockbuff, unsigned long nosectors)
{
  int track = 0, sector = 0, head = 0, track2 = 0, result = 0;
  unsigned long loop = 0;

  log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Reading block...");

/* The FDC can read multiple sides at once but not multiple tracks */
	
  block2hts (block, &head, &track, &sector);
  block2hts (block + nosectors, &head, &track2, &sector);
	
  if (track != track2)
  {
    for ( loop = 0 ; loop < nosectors ; loop++ )
    {
      result = fdc_rw ( block + loop, blockbuff + (loop * 512), TRUE, 1);
    }
    return result;
  }
  return fdc_rw (block, blockbuff, TRUE, nosectors);
}

/* write block (blockbuff is 512 byte buffer) */
bool write_block (int block, BYTE *blockbuff, unsigned long nosectors)
{
  log_print(&log_structure, LOG_URGENCY_DEBUG, 
               "Writing block...");
  return fdc_rw (block, blockbuff, FALSE, nosectors);
}

/*
 * since reads and writes differ only by a few lines, this handles both.  This
 * function is called by read_block() and write_block()
 */
bool fdc_rw (int block, u8 *blockbuff, bool read, unsigned long nosectors)
{
  unsigned int head, track, sector, tries;
  u8 *p_tbaddr = dma_buffer;
  u8 *p_blockbuff = blockbuff;
  unsigned int copy_count = 0;

  log_print (&log_structure, LOG_URGENCY_DEBUG, 
               "Read/Write operation...");
   
  /* convert logical address into physical address */
  block2hts (block, &head, &track, &sector);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
               "head=%lu, track=%lu, sector=%lu", head, track, sector);
   
  /* spin up the disk */
  motor_on ();

  if (!read && blockbuff) 
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG, 
               "copy data from data buffer into track buffer ...");
    /* copy data from data buffer into track buffer */
    for ( copy_count = 0 ; copy_count < (nosectors * 512); copy_count++ ) 
    {
      *p_tbaddr = *p_blockbuff;
      p_blockbuff++;
      p_tbaddr++;
    }
  }
   
  for ( tries = 0 ; tries < 3 ; tries++ ) 
  {
    /* check for diskchange */
      if (system_port_in_u8 (FDC_DIR) & 0x80) 
      {
	 is_disk_change = TRUE;
	 seek (1);  /* clear "disk change" status */
	 recalibrate ();
	 motor_off ();
	 log_print (&log_structure, LOG_URGENCY_WARNING,
	            "Disk change detected. Trying again.");
	 
	 return fdc_rw (block, blockbuff, read, nosectors);
      }
      /* move head to right track */
      if (!seek (track)) 
      {
	 motor_off ();
	 log_print (&log_structure, LOG_URGENCY_ERROR,
	            "Error seeking to track.");
	 return FALSE;
      }
      
      /* program data rate (500K/s) */
      system_port_out_u8 (FDC_CCR, 0);
      
      /* send command */
      if (read)
      {
//	 dma_xfer(2,tbaddr,nosectors*512,FALSE);
//         dma_transfer (dma_buffer, nosectors * 512, FALSE);
    log_print (&log_structure, LOG_URGENCY_INFORMATIVE,
               "DMA read transfer...");
    system_call_dma_transfer (FLOPPY_DMA_CHANNEL, nosectors * 512,
                                       STORM_DMA_OPERATION_READ,
                                       STORM_DMA_TRANSFER_MODE_SINGLE,
                                       STORM_DMA_AUTOINIT_DISABLE);
	 sendbyte (COMMAND_READ);
      } 
      else 
      {
//	 dma_xfer(2,tbaddr,nosectors*512,TRUE);
	 dma_transfer (dma_buffer, nosectors * 512, TRUE);

	 sendbyte (COMMAND_WRITE);
      }
      
      sendbyte (head << 2);
      sendbyte (track);
      sendbyte (head);
      sendbyte (sector);
      sendbyte (2);               /* 512 bytes/sector */
      sendbyte (geometry.spt);

      if (geometry.spt == DG144_SPT)
      {
	sendbyte (DG144_GAP3RW);  /* gap 3 size for 1.44M read/write */
      }
      else
      {
	sendbyte (DG168_GAP3RW);  /* gap 3 size for 1.68M read/write */
      }
      
      sendbyte (0xff);            /* DTL = unused */
      
      /* wait for command completion */
      /* read/write don't need "sense interrupt status" */
      if (!waitfdc(TRUE)) 
      {
	log_print (&log_structure, LOG_URGENCY_WARNING,
	           "Timed out, trying operation again after reset()");
	reset ();
	return fdc_rw (block, blockbuff, read, nosectors);
      }
      
      if ((status[0] & 0xC0) == 0)
      {
	log_print (&log_structure, LOG_URGENCY_DEBUG, "Operation Ok");
        break;   /* worked! outta here! */
      }

      recalibrate ();  /* oops, try again... */
   }
   
  /* stop the motor */
  motor_off ();

  if (read && (blockbuff != NULL)) 
  {
    /* copy data from track buffer into data buffer */
    p_blockbuff = blockbuff;
    p_tbaddr = dma_buffer;
    log_print_formatted (&log_structure, LOG_URGENCY_WARNING,
	           "Data: %X %X %X %X", 
		   dma_buffer[0], dma_buffer[3], dma_buffer[7], dma_buffer[11]);
    for ( copy_count = 0 ; copy_count < (nosectors * 512) ; copy_count++ ) 
    {
      *p_blockbuff = *p_tbaddr;
      p_blockbuff++;
      p_tbaddr++;
    }
  }

  return (tries != 3);
}

/* this formats a track, given a certain geometry */
bool format_track (u8 track, drive_geometry_type *g)
{
   int h,r,r_id,split;
   BYTE tmpbuff[256];
   unsigned char *p_tbaddr = (char *)0x8000;
   unsigned int i;
   unsigned int copycount = 0;

   /* check geometry */
   if (g->spt != DG144_SPT && g->spt != DG168_SPT)
   {
     return FALSE;
   }
   
   /* spin up the disk */
   motor_on ();

   /* program data rate (500K/s) */
   system_port_out_u8 (FDC_CCR,0);

   seek (track);  /* seek to track */

   /* precalc some constants for interleave calculation */
   split = g->spt / 2;
   if (g->spt & 1) split++;
   
   for ( h = 0 ; h < g->heads ; h++ ) 
   {
      /* for each head... */
      
      /* check for diskchange */
      if (system_port_in_u8(FDC_DIR) & 0x80) 
      {
	 is_disk_change = TRUE;
	 seek (1);  /* clear "disk change" status */
	 recalibrate ();
	 motor_off ();
	 return FALSE;
      }

      i = 0;   /* reset buffer index */
      for ( r = 0 ; r < g->spt ; r++ ) 
      {
	 /* for each sector... */

	 /* calculate 1:2 interleave */
	 r_id = r / 2 + 1;
	 if (r & 1) r_id += split;
	 
	 /* add some head skew (2 sectors should be enough) */
	 if (h & 1) 
	 {
	    r_id -= 2;
	    if (r_id < 1) r_id += g->spt;
	 }
      
	 /* add some track skew (1/2 a revolution) */
	 if (track & 1) 
	 {
	    r_id -= g->spt / 2;
	    if (r_id < 1) r_id += g->spt;
	 }
	 
	 /**** interleave now calculated - sector ID is stored in r_id ****/

	 /* fill in sector ID's */
	 tmpbuff[i++] = track;
	 tmpbuff[i++] = h;
	 tmpbuff[i++] = r_id;
	 tmpbuff[i++] = 2;
      }

      /* copy sector ID's to track buffer */
      for(copycount = 0; copycount<i; copycount++) 
      {
      	*p_tbaddr = tmpbuff[copycount];
      	p_tbaddr++;
      }
//      movedata(_my_ds(),(long)tmpbuff,_dos_ds,tbaddr,i);
      
      /* start dma xfer */
//      dma_xfer (2,tbaddr,i,TRUE);
      dma_transfer (dma_buffer, i, TRUE);
      
      
      /* prepare "format track" command */
      sendbyte (COMMAND_FORMAT);
      sendbyte (h << 2);
      sendbyte (2);
      sendbyte (g->spt);
      if (g->spt == DG144_SPT)      
	sendbyte (DG144_GAP3FMT);    /* gap3 size for 1.44M format */
      else
	sendbyte (DG168_GAP3FMT);    /* gap3 size for 1.68M format */
      sendbyte (0);     /* filler byte */
	 
      /* wait for command to finish */
      if (!waitfdc (FALSE))
	return FALSE;
      
      if (status[0] & 0xc0) 
      {
	 motor_off ();
	 return FALSE;
      }
   }
   
   motor_off ();
   
   return TRUE;
}
