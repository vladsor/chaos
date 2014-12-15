/* Bits of main status register: */

/* drive busy mask */
#define STATUS_BUSYMASK		0x0F		

/* FDC busy */
#define STATUS_BUSY		0x10		

/* 0- DMA mode */
#define STATUS_DMA		0x20		

/* 0- cpu->fdc */
#define STATUS_DIR		0x40		

/* Data reg ready */
#define STATUS_READY		0x80		


/* Bits of FD_ST0: */

/* drive select mask */
#define STATUS0_DS		0x03		

/* Head (Address) */
#define STATUS0_HA		0x04		

/* Not Ready */
#define STATUS0_NR		0x08		

/* Equipment check error */
#define STATUS0_ECE		0x10		

/* Seek end */
#define STATUS0_SE		0x20		

/* Interrupt code mask */
#define STATUS0_INTR		0xC0		

/* Bits of FD_ST1: */

/* Missing Address Mark */
#define STATUS1_MAM		0x01		

/* Write Protect */
#define STATUS1_WP		0x02		

/* No Data - unreadable */
#define STATUS1_ND		0x04		

/* OverRun */
#define STATUS1_OR		0x10		

/* CRC error in data or addr */
#define STATUS1_CRC		0x20		

/* End Of Cylinder */
#define STATUS1_EOC		0x80		


/* Bits of FD_ST2: */

/* Missing Address Mark (again) */
#define STATUS2_MAM		0x01		

/* Bad Cylinder */
#define STATUS2_BC		0x02		

/* Scan Not Satisfied */
#define STATUS2_SNS		0x04		

/* Scan Equal Hit */
#define STATUS2_SEH		0x08		

/* Wrong Cylinder */
#define STATUS2_WC		0x10		

/* CRC error in data field */
#define STATUS2_CRC		0x20		

/* Control Mark = deleted */
#define STATUS2_CM		0x40		


/* Bits of FD_ST3: */

/* Head (Address) */
#define STATUS3_HA		0x04		

/* drive is double-sided */
#define STATUS3_DS		0x08		

/* Track Zero signal (1=track 0) */
#define STATUS3_TZ		0x10		

/* drive is ready */
#define STATUS3_RY		0x20		

/* Write Protect */
#define STATUS3_WP		0x40		

/* Drive Fault */
#define STATUS3_FT		0x80		


/* command bytes (these are 765 commands + options such as MFM, etc): */

/* move to track 0 */
#define COMMAND_RECALIBRATE	0x07	

/* seek track */
#define COMMAND_SEEK		0x0F	

/* read with MT, MFM, SKip deleted */
#define COMMAND_READ		0xE6	

/* write with MT, MFM */
#define COMMAND_WRITE		0xC5	

/* Sense Interrupt Status */
#define COMMAND_SENSEI		0x08	

/* specify HUT etc */
#define COMMAND_SPECIFY		0x03	

/* format one track */
#define COMMAND_FORMAT		0x4D	

/* get version code */
#define COMMAND_VERSION		0x10	

/* configure FIFO operation */
#define COMMAND_CONFIGURE	0x13	

/* perpendicular r/w mode */
#define COMMAND_PERPENDICULAR	0x12	

/* read ST3 */
#define COMMAND_GET_STATUS	0x04	

/* dump the contents of the fdc regs */
#define COMMAND_DUMP_REGISTERS	0x0E	

/* prints the header of a sector */
#define COMMAND_READ_ID		0xEA	

/* Fifo config unlock */
#define COMMAND_UNLOCK		0x14	

/* Fifo config lock */
#define COMMAND_LOCK		0x94	

/* seek out (i.e. to lower tracks) */
#define COMMAND_SEEK_OUT	0x8f	

/* seek in (i.e. to higher tracks) */
#define COMMAND_SEEK_IN		0xcf	

/* the following commands are new in the 82078. They are not used in the
 * floppy driver, except the first three. These commands may be useful for apps
 * which use the FDRAWCMD interface. For doc, get the 82078 spec sheets at
 * http://www-techdoc.intel.com/docs/periph/fd_contr/datasheets/ */

/* part id ("extended" version cmd) */
#define COMMAND_PART_ID		0x18	

/* save fdc regs for later restore */
#define COMMAND_SAVE		0x2E	

/* drive specification: Access to the 2 Mbps data transfer rate for tape drives 
*/
#define COMMAND_DRIVESPEC	0x8E	

/* later restore */
#define COMMAND_RESTORE		0x4E    

/* configure FDC's powersave features */
#define COMMAND_POWERDOWN	0x27	

/* format and write in one go. */
#define COMMAND_FORMAT_AND_WRITE	0xEF    

/* ISO format (which is a clean way to pack more sectors on a track) */
#define COMMAND_OPTION		0x33	

enum fdc_t
{
    /* FDC version return types: */
    FDC_TYPE_NONE = 0x00,

    /* DO NOT USE THIS TYPE EXCEPT IF IDENTIFICATION FAILS EARLY */
    FDC_TYPE_UNKNOWN = 0x10,

    /* Intel 8272a, NEC 765 */	
    FDC_TYPE_8272A = 0x20,

    /* Non-Intel 1MB-compatible FDC, can't detect */
    FDC_TYPE_765ED = 0x30,

    /* Intel 82072; 8272a + FIFO + DUMPREGS */
    FDC_TYPE_82072 = 0x40,

    /* 82072A (on Sparcs) */
    FDC_TYPE_82072A = 0x45,

    /* Original version of 82077AA, sans LOCK */
    FDC_TYPE_82077_ORIG = 0x51,

    /* 82077AA-1 */
    FDC_TYPE_82077 = 0x52,

    /* Unknown 82078 variant */
    FDC_TYPE_82078_UNKNOWN = 0x5F,

    /* 44pin 82078 or 64pin 82078SL */
    FDC_TYPE_82078 = 0x60,

    /* 82078-1 (2Mbps fdc) */
    FDC_TYPE_82078_1 = 0x61,

    /* S82078B (first seen on Adaptec AVA-2825 VLB  SCSI/EIDE/Floppy controller) */
    FDC_TYPE_S82078B = 0x62,

    /* National Semiconductor PC 87306 */
    FDC_TYPE_87306 = 0x63,
};

extern int fdc_get_version (void);
