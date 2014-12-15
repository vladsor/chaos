
#ifndef FDC_H
#define FDC_H

/* datatypes */

/* drive geometry */
typedef struct 
{
    uint8_t heads;
    uint8_t tracks;
    uint8_t sectors_per_track;     

} drive_geometry_t;

/* drive geometries */
#define DG144_HEADS       2     /* heads per drive (1.44M) */
#define DG144_TRACKS     80     /* number of tracks (1.44M) */
#define DG144_SPT        18     /* sectors per track (1.44M) */
#define DG144_GAP3FMT  0x54     /* gap3 while formatting (1.44M) */
#define DG144_GAP3RW   0x1b     /* gap3 while reading/writing (1.44M) */

#define DG168_HEADS       2     /* heads per drive (1.68M) */
#define DG168_TRACKS     80     /* number of tracks (1.68M) */
#define DG168_SPT        21     /* sectors per track (1.68M) */
#define DG168_GAP3FMT  0x0c     /* gap3 while formatting (1.68M) */
#define DG168_GAP3RW   0x1c     /* gap3 while reading/writing (1.68M) */

/* IO ports: */

/* Digital Output Register */
#define FDC_REGISTER_DIGITAL_OUTPUT             0x3F2

/* Main Status Register (input) */
#define FDC_REGISTER_MAIN_STATUS                0x3F4

/* Data Rate Select Register (output) */
#define FDC_REGISTER_DATA_RATE_SELECT           0x3F4

/* Data Register */
#define FDC_REGISTER_DATA                       0x3F5

/* Digital Input Register (input) */
#define FDC_REGISTER_DIGITAL_INPUT              0x3F7

/* Configuration Control Register (output) */
#define FDC_REGISTER_CONFIGURATION_CONTROL      0x3F7

/* command bytes (these are 765 commands + options such as MFM, etc): */

/* specify drive timings */
#define COMMAND_SPECIFY         0x03

/* write data (+ MT,MFM) */
#define COMMAND_WRITE           0xC5

/* read data (+ MT,MFM,SK) */
#define COMMAND_READ            0xE6  

/* recalibrate */
#define COMMAND_RECALIBRATE     0x07  

/* sense interrupt status */
#define COMMAND_SENSEI          0x08  

/* format track (+ MFM) */
#define COMMAND_FORMAT          0x4D  

/* seek track */
#define COMMAND_SEEK            0x0F  

/* FDC version */
#define COMMAND_VERSION         0x10  

#define FLOPPY_DMA_CHANNEL      0x02

#define FLOPPY_IRQ_CHANNEL	0X06

/* function prototypes */

extern bool floppy_driver_init (void);
extern void fdc_reset (void);

extern bool floppy_driver_read_block (int block, uint8_t *buffer, 
    unsigned long nosectors);
    
extern bool floppy_driver_write_block (int block, uint8_t *buffer, 
    unsigned long nosectors);

bool disk_change (void);

void fdc_motor_on (void);
void fdc_motor_off (void);

void floppy_recalibrate (void);
bool floppy_seek (int track);
bool log_disk (drive_geometry_t *g);

bool format_track (uint8_t track, drive_geometry_t *g);

/* prototypes */
bool fdc_output_byte (uint8_t byte);
int fdc_get_byte (void);

#endif /* FDC_H */
