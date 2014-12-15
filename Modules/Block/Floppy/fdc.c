#include <enviroment.h>

#include "floppy.h"
#include "fdc.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define MAX_REPLIES 16
static unsigned char reply_buffer[MAX_REPLIES];

#define ST0		(reply_buffer[0])
#define ST1		(reply_buffer[1])
#define ST2		(reply_buffer[2])
#define ST3		(reply_buffer[0]) /* result of GETSTATUS */
#define R_TRACK 	(reply_buffer[3])
#define R_HEAD		(reply_buffer[4])
#define R_SECTOR	(reply_buffer[5])
#define R_SIZECODE	(reply_buffer[6])

/* waits until the fdc becomes ready */
static int fdc_wait_until_ready (void)
{
  int counter, status;

  for (counter = 0; counter < 10000; counter++) 
  {
    status = port_uint8_in (FDC_REGISTER_MAIN_STATUS);		
    if (status & STATUS_READY)
    {
      return status;
    }
  }
  
  return -1;
}

/* sends a command byte to the fdc */
bool fdc_output_byte (uint8_t byte)
{
  int status;

  status = fdc_wait_until_ready ();

  if (status < 0)
  {
    return FALSE;
  }
  
  if ((status & (STATUS_READY | STATUS_DIR | STATUS_DMA)) == STATUS_READY)
  {
    port_uint8_out (FDC_REGISTER_DATA, byte);
    
    return TRUE;
  }
  
  return FALSE;
}

int fdc_get_byte (void)
{
  uint8_t msr;
  uint8_t data;
  int tmo;
   
  for (tmo = 0 ; tmo < 12800 ; tmo++) 
  {
    msr = port_uint8_in (FDC_REGISTER_MAIN_STATUS);
    if ((msr & 0xD0) == 0xD0) 
    {
      data = port_uint8_in (FDC_REGISTER_DATA);
      return data;
    } 
  }

  DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Get byte time outed.\n");

  return -1;   /* read timeout */
}

/* gets the response from the fdc */
static int fdc_get_result (void)
{
  int i, status;

  for (i = 0 ; i < MAX_REPLIES; i++) 
  {
    status = fdc_wait_until_ready ();

    if (status < 0)
    {
      break;
    }
     
    status &= STATUS_DIR | STATUS_READY | STATUS_BUSY | STATUS_DMA;

    if ((status & ~STATUS_BUSY) == STATUS_READY)
    {
      return i;
    }
    
    if (status == (STATUS_DIR | STATUS_READY | STATUS_BUSY))
    {
      reply_buffer[i] = port_uint8_in (FDC_REGISTER_DATA);
    }
    else
    {
      break;
    }
  }
  
  return -1;
}

#define MORE_OUTPUT -2
/* does the fdc need more output? */
static int need_more_output (void)
{
  int status;

  status = fdc_wait_until_ready ();

  if (status < 0)
  {
    return -1;
  }
    
  if ((status & (STATUS_READY | STATUS_DIR | STATUS_DMA)) == STATUS_READY)
  {
    return MORE_OUTPUT;
  }

  return fdc_get_result ();
}

static int fifo_depth = 0xa;
static int no_fifo = 0;

static bool fdc_configure (void)
{
  /* Turn on FIFO */
  fdc_output_byte (COMMAND_CONFIGURE);
  
  if (need_more_output () != MORE_OUTPUT)
  {
    return FALSE;
  }
  
  fdc_output_byte (0);
  fdc_output_byte (0x10 | (no_fifo & 0x20) | (fifo_depth & 0xf));

  /* pre-compensation from track 0 upwards */
  fdc_output_byte (0);	
  
  return TRUE;
}	

/*
 * Floppy Driver initialization
 * =============================
 */

/* Determine the floppy disk controller type */
/* This routine was written by David C. Niemi */

int fdc_get_version (void)
{
  int r, i;

  /* get floppy controller version */
  fdc_output_byte (COMMAND_VERSION);
  i = fdc_get_byte ();

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC version is %i.\n", i);
  
  /* 82072 and better know DUMPREGS */
  fdc_output_byte (COMMAND_DUMP_REGISTERS);	

  r = fdc_get_result ();
  if (r <= 0)
  {
    /* No FDC present ??? */
    return FDC_TYPE_NONE;	
  }
  
  if ((r == 1) && (reply_buffer[0] == 0x80))
  {
    /* 8272a/765 don't know DUMPREGS */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is an 8272A.\n");
    
    return FDC_TYPE_8272A;	
  }
  
  if (r != 10) 
  {
    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
	"FDC init: DUMPREGS: unexpected return of %d bytes.", r);
	
    return FDC_TYPE_UNKNOWN;
  }

  if (!fdc_configure ()) 
  {
    /* 82072 doesn't know CONFIGURE */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is an 82072.\n");
    
    return FDC_TYPE_82072;      	
  }

  fdc_output_byte (COMMAND_PERPENDICULAR);

  if (need_more_output () == MORE_OUTPUT) 
  {
    fdc_output_byte (0);
  } 
  else 
  {
    /* 82072A as found on Sparcs. */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is an 82072A.\n");

    return FDC_TYPE_82072A;	
  }

  fdc_output_byte (COMMAND_UNLOCK);
  r = fdc_get_result ();

  if ((r == 1) && (reply_buffer[0] == 0x80))
  {
    /* Pre-1991 82077, doesn't know LOCK/UNLOCK */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is a pre-1991 82077.\n");
    
    return FDC_TYPE_82077_ORIG;	
  }

  if ((r != 1) || (reply_buffer[0] != 0x00)) 
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"FDC init: UNLOCK: unexpected return of %d bytes.", r);

    return FDC_TYPE_UNKNOWN;
  }
  
  fdc_output_byte (COMMAND_PART_ID);
  r = fdc_get_result ();

  if (r != 1) 
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"FDC init: PARTID: unexpected return of %d bytes.", r);
	
    return FDC_TYPE_UNKNOWN;
  }
  
  if (reply_buffer[0] == 0x80) 
  {
    /* Revised 82077AA passes all the tests */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is a post-1991 82077.\n");
    
    return FDC_TYPE_82077;	
  }

  switch (reply_buffer[0] >> 5) 
  {
    case 0x0:
    {
      /* Either a 82078-1 or a 82078SL running at 5Volt */
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is an 82078.\n");
      
      return FDC_TYPE_82078;
    }
    
    case 0x1:
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is a 44pin 82078.\n");
      
      return FDC_TYPE_82078;
    }
    
    case 0x2:
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FDC is a S82078B.\n");
      
      return FDC_TYPE_S82078B;
    }
    
    case 0x3:
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "FDC is a National Semiconductor PC87306.\n");
      
      return FDC_TYPE_87306;
    }
    
    default:
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"FDC init: 82078 variant with unknown PARTID=%d.\n",
	reply_buffer[0] >> 5);
	  
      return FDC_TYPE_82078_UNKNOWN;
    }
  }
} /* get_fdc_version */

#if FALSE
/*
 * reset is done by pulling bit 2 of DOR low for a while (old FDCs),
 * or by setting the self clearing bit 7 of STATUS (newer FDCs)
 */
void fdc_reset (void)
{
	SET_INTR(reset_interrupt);
	FDCS->reset = 0;
	reset_fdc_info(0);

	/* Pseudo-DMA may intercept 'reset finished' interrupt.  */
	/* Irrelevant for systems with true DMA (i386).          */
	fd_disable_dma();

  if (FDCS->version >= FDC_82072A)
  {
    fd_outb(0x80 | (FDCS->dtr &3), FD_STATUS);
  }
  else 
  {
    system_port_out_u8 (FDCS->dor & ~0x04, FD_REGISTER_DIGITAL_OUTPUT);
    system_sleep (FD_RESET_DELAY);
    system_port_out_u8 (FDCS->dor, FD_REGISTER_DIGITAL_OUTPUT);
  }
}

#define CODE2SIZE (ssize = ((1 << SIZECODE) + 3) >> 2)
#define FM_MODE(x,y) ((y) & ~(((x)->rate & 0x80) >>1))
#define CT(x) ((x) | 0x40)

static void setup_format_params (int track)
{
  struct fparm {
    unsigned char track,head,sect,size;
  } *here = (struct fparm *)floppy_track_buffer;
  int il,n;
  int count,head_shift,track_shift;

	raw_cmd = &default_raw_cmd;
	raw_cmd->track = track;

	raw_cmd->flags = FD_RAW_WRITE | FD_RAW_INTR | FD_RAW_SPIN |
		FD_RAW_NEED_DISK | FD_RAW_NEED_SEEK;
	raw_cmd->rate = _floppy->rate & 0x43;
	raw_cmd->cmd_count = NR_F;
	COMMAND = FM_MODE(_floppy,FD_FORMAT);
	DR_SELECT = UNIT(current_drive) + PH_HEAD(_floppy,format_req.head);
	F_SIZECODE = FD_SIZECODE(_floppy);
	F_SECT_PER_TRACK = _floppy->sect << 2 >> F_SIZECODE;
	F_GAP = _floppy->fmt_gap;
	F_FILL = FD_FILL_BYTE;

	raw_cmd->kernel_data = floppy_track_buffer;
	raw_cmd->length = 4 * F_SECT_PER_TRACK;

	/* allow for about 30ms for data transport per track */
	head_shift  = (F_SECT_PER_TRACK + 5) / 6;

	/* a ``cylinder'' is two tracks plus a little stepping time */
	track_shift = 2 * head_shift + 3;

	/* position of logical sector 1 on this track */
	n = (track_shift * format_req.track + head_shift * format_req.head)
		% F_SECT_PER_TRACK;

	/* determine interleave */
	il = 1;
	if (_floppy->fmt_gap < 0x22)
		il++;

	/* initialize field */
	for (count = 0; count < F_SECT_PER_TRACK; ++count) {
		here[count].track = format_req.track;
		here[count].head = format_req.head;
		here[count].sect = 0;
		here[count].size = F_SIZECODE;
	}
	/* place logical sectors */
	for (count = 1; count <= F_SECT_PER_TRACK; ++count) {
		here[n].sect = count;
		n = (n+il) % F_SECT_PER_TRACK;
		if (here[n].sect) { /* sector busy, find next free sector */
			++n;
			if (n>= F_SECT_PER_TRACK) {
				n-=F_SECT_PER_TRACK;
				while (here[n].sect) ++n;
			}
		}
	}
}

static void redo_format(void)
{
	buffer_track = -1;
	setup_format_params(format_req.track << STRETCH(_floppy));
	floppy_start();
}

static struct cont_t format_cont={
	format_interrupt,
	redo_format,
	bad_flp_intr,
	generic_done };

static int do_format(kdev_t device, struct format_descr *tmp_format_req)
{
  int ret;
  int drive=DRIVE(device);

  LOCK_FDC(drive,1);
  set_floppy(device);

  if (!_floppy ||
	    _floppy->track > DP->tracks ||
	    tmp_format_req->track >= _floppy->track ||
	    tmp_format_req->head >= _floppy->head ||
	    (_floppy->sect << 2) % (1 <<  FD_SIZECODE(_floppy)) ||
	    !_floppy->fmt_gap) {
		process_fd_request();
		return -EINVAL;
	}

  format_req = *tmp_format_req;
  format_errors = 0;
  cont = &format_cont;
  errors = &format_errors;
  IWAIT(redo_format);
  process_fd_request();

  return ret;
}
/*
 * Formulate a read/write request.
 * this routine decides where to load the data (directly to buffer, or to
 * tmp floppy area), how much data to load (the size of the buffer, the whole
 * track, or a single sector)
 * All floppy_track_buffer handling goes in here. If we ever add track buffer
 * allocation on the fly, it should be done here. No other part should need
 * modification.
 */

static int make_raw_rw_request(void)
{
	int aligned_sector_t;
	int max_sector, max_size, tracksize, ssize;

	set_fdc(DRIVE(CURRENT->rq_dev));

	raw_cmd = &default_raw_cmd;
	raw_cmd->flags = FD_RAW_SPIN | FD_RAW_NEED_DISK | FD_RAW_NEED_DISK |
		FD_RAW_NEED_SEEK;
	raw_cmd->cmd_count = NR_RW;
	if (CURRENT->cmd == READ){
		raw_cmd->flags |= FD_RAW_READ;
		COMMAND = FM_MODE(_floppy,FD_READ);
	} else if (CURRENT->cmd == WRITE){
		raw_cmd->flags |= FD_RAW_WRITE;
		COMMAND = FM_MODE(_floppy,FD_WRITE);
	} else {
		DPRINT("make_raw_rw_request: unknown command\n");
		return 0;
	}

	max_sector = _floppy->sect * _floppy->head;

	TRACK = CURRENT->sector / max_sector;
	sector_t = CURRENT->sector % max_sector;
	if (_floppy->track && TRACK >= _floppy->track)
		return 0;
	HEAD = sector_t / _floppy->sect;

	if (((_floppy->stretch & FD_SWAPSIDES) || TESTF(FD_NEED_TWADDLE)) &&
	    sector_t < _floppy->sect)
		max_sector = _floppy->sect;

	/* 2M disks have phantom sectors on the first track */
	if ((_floppy->rate & FD_2M) && (!TRACK) && (!HEAD)){
		max_sector = 2 * _floppy->sect / 3;
		if (sector_t >= max_sector){
			current_count_sectors = minimum(_floppy->sect - sector_t,
							CURRENT->nr_sectors);
			return 1;
		}
		SIZECODE = 2;
	} else
		SIZECODE = FD_SIZECODE(_floppy);
	raw_cmd->rate = _floppy->rate & 0x43;
	if ((_floppy->rate & FD_2M) &&
	    (TRACK || HEAD) &&
	    raw_cmd->rate == 2)
		raw_cmd->rate = 1;

	if (SIZECODE)
		SIZECODE2 = 0xff;
	else
		SIZECODE2 = 0x80;
	raw_cmd->track = TRACK << STRETCH(_floppy);
	DR_SELECT = UNIT(current_drive) + PH_HEAD(_floppy,HEAD);
	GAP = _floppy->gap;
	CODE2SIZE;
	SECT_PER_TRACK = _floppy->sect << 2 >> SIZECODE;
	SECTOR = ((sector_t % _floppy->sect) << 2 >> SIZECODE) + 1;
	tracksize = _floppy->sect - _floppy->sect % ssize;
	if (tracksize < _floppy->sect){
		SECT_PER_TRACK ++;
		if (tracksize <= sector_t % _floppy->sect)
			SECTOR--;
		while (tracksize <= sector_t % _floppy->sect){
			while(tracksize + ssize > _floppy->sect){
				SIZECODE--;
				ssize >>= 1;
			}
			SECTOR++; SECT_PER_TRACK ++;
			tracksize += ssize;
		}
		max_sector = HEAD * _floppy->sect + tracksize;
	} else if (!TRACK && !HEAD && !(_floppy->rate & FD_2M) && probing)
		max_sector = _floppy->sect;

	aligned_sector_t = sector_t - (sector_t % _floppy->sect) % ssize;
	max_size = CURRENT->nr_sectors;
	if ((raw_cmd->track == buffer_track) && 
	    (current_drive == buffer_drive) &&
	    (sector_t >= buffer_min) && (sector_t < buffer_max)) {
		/* data already in track buffer */
		if (CT(COMMAND) == FD_READ) {
			copy_buffer(1, max_sector, buffer_max);
			return 1;
		}
	} else if (aligned_sector_t != sector_t || CURRENT->nr_sectors < ssize){
		if (CT(COMMAND) == FD_WRITE){
			if (sector_t + CURRENT->nr_sectors > ssize &&
			    sector_t + CURRENT->nr_sectors < ssize + ssize)
				max_size = ssize + ssize;
			else
				max_size = ssize;
		}
		raw_cmd->flags &= ~FD_RAW_WRITE;
		raw_cmd->flags |= FD_RAW_READ;
		COMMAND = FM_MODE(_floppy,FD_READ);
	} else if ((unsigned long)CURRENT->buffer < MAX_DMA_ADDRESS) {
		unsigned long dma_limit;
		int direct, indirect;

		indirect= transfer_size(ssize,max_sector,max_buffer_sectors*2) -
			sector_t;

		/*
		 * Do NOT use minimum() here---MAX_DMA_ADDRESS is 64 bits wide
		 * on a 64 bit machine!
		 */
		max_size = buffer_chain_size();
		dma_limit = (MAX_DMA_ADDRESS - ((unsigned long) CURRENT->buffer)) >> 9;
		if ((unsigned long) max_size > dma_limit) {
			max_size = dma_limit;
		}
		/* 64 kb boundaries */
		if (CROSS_64KB(CURRENT->buffer, max_size << 9))
			max_size = (K_64 - ((long) CURRENT->buffer) % K_64)>>9;
		direct = transfer_size(ssize,max_sector,max_size) - sector_t;
		/*
		 * We try to read tracks, but if we get too many errors, we
		 * go back to reading just one sector at a time.
		 *
		 * This means we should be able to read a sector even if there
		 * are other bad sectors on this track.
		 */
		if (!direct ||
		    (indirect * 2 > direct * 3 &&
		     *errors < DP->max_errors.read_track &&
		     /*!TESTF(FD_NEED_TWADDLE) &&*/
		     ((!probing || (DP->read_track&(1<<DRS->probed_format)))))){
			max_size = CURRENT->nr_sectors;
		} else {
			raw_cmd->kernel_data = CURRENT->buffer;
			raw_cmd->length = current_count_sectors << 9;
			if (raw_cmd->length == 0){
				DPRINT("zero dma transfer attempted from make_raw_request\n");
				DPRINT("indirect=%d direct=%d sector_t=%d",
					indirect, direct, sector_t);
				return 0;
			}
			return 2;
		}
	}

	if (CT(COMMAND) == FD_READ)
		max_size = max_sector; /* unbounded */

	/* claim buffer track if needed */
	if (buffer_track != raw_cmd->track ||  /* bad track */
	    buffer_drive !=current_drive || /* bad drive */
	    sector_t > buffer_max ||
	    sector_t < buffer_min ||
	    ((CT(COMMAND) == FD_READ ||
	      (aligned_sector_t == sector_t && CURRENT->nr_sectors >= ssize))&&
	     max_sector > 2 * max_buffer_sectors + buffer_min &&
	     max_size + sector_t > 2 * max_buffer_sectors + buffer_min)
	    /* not enough space */){
		buffer_track = -1;
		buffer_drive = current_drive;
		buffer_max = buffer_min = aligned_sector_t;
	}
	raw_cmd->kernel_data = floppy_track_buffer + 
		((aligned_sector_t-buffer_min)<<9);

	if (CT(COMMAND) == FD_WRITE){
		/* copy write buffer to track buffer.
		 * if we get here, we know that the write
		 * is either aligned or the data already in the buffer
		 * (buffer will be overwritten) */
#ifdef FLOPPY_SANITY_CHECK
		if (sector_t != aligned_sector_t && buffer_track == -1)
			DPRINT("internal error offset !=0 on write\n");
#endif
		buffer_track = raw_cmd->track;
		buffer_drive = current_drive;
		copy_buffer(ssize, max_sector, 2*max_buffer_sectors+buffer_min);
	} else
		transfer_size(ssize, max_sector,
			      2*max_buffer_sectors+buffer_min-aligned_sector_t);

	/* round up current_count_sectors to get dma xfer size */
	raw_cmd->length = sector_t+current_count_sectors-aligned_sector_t;
	raw_cmd->length = ((raw_cmd->length -1)|(ssize-1))+1;
	raw_cmd->length <<= 9;
#ifdef FLOPPY_SANITY_CHECK
	if ((raw_cmd->length < current_count_sectors << 9) ||
	    (raw_cmd->kernel_data != CURRENT->buffer &&
	     CT(COMMAND) == FD_WRITE &&
	     (aligned_sector_t + (raw_cmd->length >> 9) > buffer_max ||
	      aligned_sector_t < buffer_min)) ||
	    raw_cmd->length % (128 << SIZECODE) ||
	    raw_cmd->length <= 0 || current_count_sectors <= 0){
		DPRINT("fractionary current count b=%lx s=%lx\n",
			raw_cmd->length, current_count_sectors);
		if (raw_cmd->kernel_data != CURRENT->buffer)
			printk("addr=%d, length=%ld\n",
			       (int) ((raw_cmd->kernel_data - 
				       floppy_track_buffer) >> 9),
			       current_count_sectors);
		printk("st=%d ast=%d mse=%d msi=%d\n",
		       sector_t, aligned_sector_t, max_sector, max_size);
		printk("ssize=%x SIZECODE=%d\n", ssize, SIZECODE);
		printk("command=%x SECTOR=%d HEAD=%d, TRACK=%d\n",
		       COMMAND, SECTOR, HEAD, TRACK);
		printk("buffer drive=%d\n", buffer_drive);
		printk("buffer track=%d\n", buffer_track);
		printk("buffer_min=%d\n", buffer_min);
		printk("buffer_max=%d\n", buffer_max);
		return 0;
	}

	if (raw_cmd->kernel_data != CURRENT->buffer){
		if (raw_cmd->kernel_data < floppy_track_buffer ||
		    current_count_sectors < 0 ||
		    raw_cmd->length < 0 ||
		    raw_cmd->kernel_data + raw_cmd->length >
		    floppy_track_buffer + (max_buffer_sectors  << 10)){
			DPRINT("buffer overrun in schedule dma\n");
			printk("sector_t=%d buffer_min=%d current_count=%ld\n",
			       sector_t, buffer_min,
			       raw_cmd->length >> 9);
			printk("current_count_sectors=%ld\n",
			       current_count_sectors);
			if (CT(COMMAND) == FD_READ)
				printk("read\n");
			if (CT(COMMAND) == FD_READ)
				printk("write\n");
			return 0;
		}
	} else if (raw_cmd->length > CURRENT->nr_sectors << 9 ||
		   current_count_sectors > CURRENT->nr_sectors){
		DPRINT("buffer overrun in direct transfer\n");
		return 0;
	} else if (raw_cmd->length < current_count_sectors << 9){
		DPRINT("more sectors than bytes\n");
		printk("bytes=%ld\n", raw_cmd->length >> 9);
		printk("sectors=%ld\n", current_count_sectors);
	}
	if (raw_cmd->length == 0){
		DPRINT("zero dma transfer attempted from make_raw_request\n");
		return 0;
	}
#endif
	return 2;
}
#endif
