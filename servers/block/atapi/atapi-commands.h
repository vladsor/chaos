/* The CompactFlash Association (CFA) feature set provides support for solid 
   state memory devices. */

#define ATA_COMMAND_NOP				0x00
#define ATA_COMMAND_DEVICE_RESET		0x08
#define ATA_COMMAND_IDENTIFY_DEVICE		0xEC
#define ATA_COMMAND_IDENTIFY_PACKET_DEVICE	0xA1
#define ATA_COMMAND_FLUSH_CACHE			0xE7

#define ATAPI_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE 0x03

#define ATAPI_COMMAND_READ_SECTORS		0x20
#define ATAPI_COMMAND_WRITE_SECTORS		0x30
#define ATAPI_COMMAND_CFA_WRITE_SECTORS_WITHOUT_ERASE 0x38
#define ATAPI_COMMAND_READ_VERIFY_SECTORS	0x40
#define ATAPI_COMMAND_SEEK			0x70
#define ATAPI_COMMAND_CFA_TRANSLATE_SECTOR	0x87
#define ATAPI_COMMAND_EXECUTE_DEVICE_DIAGNOSTIC	0x90
#define ATAPI_COMMAND_INITIALIZE_DEVICE_PARAMETERS 0x91
#define ATAPI_COMMAND_DOWNLOAD_MICROCODE	0x92
#define ATAPI_COMMAND_PACKET			0xA0

#define ATAPI_COMMAND_SERVICE			0xA2
#define ATAPI_COMMAND_SMART			0xB0
#define ATAPI_COMMAND_CFA_ERASE_SECTORS		0xC0
#define ATAPI_COMMAND_READ_MULTIPLE		0xC4
#define ATAPI_COMMAND_WRITE_MULTIPLE		0xC5
#define ATAPI_COMMAND_SET_MULTIPLE_MODE		0xC6
#define ATAPI_COMMAND_READ_DMA_QUEUED		0xC7
#define ATAPI_COMMAND_READ_DMA			0xC8
#define ATAPI_COMMAND_WRITE_DMA			0xCA
#define ATAPI_COMMAND_WRITE_DMA_QUEUED		0xCC
#define ATAPI_COMMAND_CFA_WRITE_MULTIPLE_WITHOUT_ERASE 0xCD
#define ATAPI_COMMAND_GET_MEDIA_STATUS		0xDA
#define ATAPI_COMMAND_MEDIA_LOCK		0xDE
#define ATAPI_COMMAND_MEDIA_UNLOCK		0xDF
#define ATAPI_COMMAND_STANDBY_IMMEDIATE		0xE0
#define ATAPI_COMMAND_IDLE_IMMEDIATE		0xE1
#define ATAPI_COMMAND_STANDBY			0xE2
#define ATAPI_COMMAND_IDLE			0xE3
#define ATAPI_COMMAND_READ_BUFFER		0xE4
#define ATAPI_COMMAND_CHECK_POWER_MODE		0xE5
#define ATAPI_COMMAND_SLEEP			0xE6

#define ATAPI_COMMAND_WRITE_BUFFER		0xE8

#define ATAPI_COMMAND_MEDIA_EJECT		0xED
#define ATAPI_COMMAND_SET_FEATURES		0xEF
#define ATAPI_COMMAND_SECURITY_SET_PASSWORD	0xF1
#define ATAPI_COMMAND_SECURITY_UNLOCK		0xF2
#define ATAPI_COMMAND_SECURITY_ERASE_PREPARE	0xF3
#define ATAPI_COMMAND_SECURITY_ERASE_UNIT	0xF4
#define ATAPI_COMMAND_SECURITY_FREEZE_LOCK	0xF5
#define ATAPI_COMMAND_SECURITY_DISABLE_PASSWORD	0xF6
#define ATAPI_COMMAND_READ_NATIVE_MAX_ADDRESS	0xF8
#define ATAPI_COMMAND_SET_MAX_ADDRESS		0xF9

#define ATA_MASTER_DRIVE_SELECT 0xA0 
#define ATA_SLAVE_DRIVE_SELECT 0xB0


/* ATA/ATAPI drive registers */

/* read: alternate status/error */
#define	ATA_ALTERNATE_STATUS_REGISTER(BASE) = (BASE + 0x206)

/* write: drive command */
#define	ATA_COMMAND_REGISTER(BASE) = (BASE + 7)

/* ATA: MSB of cylinder */
#define	ATA_CYLINDER_HIGH_REGISTER(BASE) = (BASE + 5)

/* ATA: LSB of cylinder */
#define	ATA_CYLINDER_LOW_REGISTER(BASE) = (BASE + 4)

/* data (16-bit) */
#define	ATA_DATA_REGISTER(BASE) = (BASE + 0)

/* write: device control */
#define	ATA_DEVICE_CONTROL_REGISTER(BASE) = (BASE + 0x206)

/* SRST is the host software reset bit */
#define ATA_SRST 4

/* nIEN is the enable bit for the device interrupt to the host. When the nIEN bit is cleared to zero, and
the device is selected, INTRQ shall be enabled through a tri-state buffer and shall be asserted or
negated by the device as appropriate. When the nIEN bit is set to one, or the device is not
selected, the INTRQ signal shall be in a high impedance state. */
#define ATA_nIEN 2

/* drive select; head */
#define	ATA_DEVICE_HEAD_REGISTER(BASE) = (BASE + 6)

/* DEV - Device select. Cleared to zero selects Device 0. Set to one selects Device 1.*/
#define ATA_DEV 0x10

/* read: error */
#define	ATA_ERROR_REGISTER(BASE) = (BASE + 1)

/* Bit 2 - ABRT (command aborted) is set to one to indicate the requested command has been
command aborted because the command code or a command parameter is invalid or some other
error has occurred. */
#define ATA_ABRT 4

/* write: feature reg */
#define	ATA_FEATURES_REGISTER(BASE) = (BASE + 1)

/* ATA: sector count */
#define	ATA_SECTOR_COUNT_REGISTER(BASE) = (BASE + 2)

/* sector */
#define	ATA_SECTOR_NUMBER_REGISTER(BASE) = (BASE + 3)

/* read: status and error flags */
#define	ATA_STATUS_REGISTER(BASE) = (BASE + 7)

/* Busy */
#define ATA_STATE_BUSY 0x80

/* Device ready */
#define ATA_STATE_DRDY 0x40

/* Data request */
#define ATA_STATE_DRQ 0x08

/* Error or CHK */
#define ATA_STATE_ERR 0x01


/* ATAPI: interrupt reason */
#define	ATA_INTERRUPT_REASON_REGISTER ATA_SECTOR_COUNT_REGISTER

#if FALSE
/* ATAPI: LSB of transfer count */
#define	ATA_REG_LOCNT	ATA_REG_LOCYL

/* ATAPI: MSB of transfer count */	
#define	ATA_REG_HICNT	ATA_REG_HICYL
#endif

/* Delays from Linux ide.h (milliseconds) */
#define	WAIT_READY	30	/* RDY asserted, use 5000 for notebook/APM */
#define	WAIT_ID		30000	/* ATA device responds to 'identify' */
#define	WAIT_PID	3	/* ATAPI device responds to 'identify' */
#define	WAIT_CMD	10000	/* IRQ occurs in response to command */
#define	WAIT_DRQ	20	/* DRQ asserted after ATA_CMD_WR(MUL) */



typedef struct
{
  u16 general_configuration;
  u16 number_of_logical_cylinders;
  u16 specific_configuration;
  u16 number_of_logical heads;
  u16 retired0;
  u16 retired1;
  u16 number_of_logical_sectors_per_logical_track;
  u16 retired2;
  u16 retired3;
  u16 retired4;
  u8  serial_number[20];
  u16 retired5;
  u16 retired6;
  u16 obsolete;
  u8  firmware_revision[8];
  u8  model[40];
  u16 unnamed0; 
/*
15-8 80h
7-0 00h =Reserved
    01h-FFh = Maximum number of sectors that shall be transferred per interrupt
on READ/WRITE MULTIPLE commands
*/
  u16 reserved0;
  u16 capabilities[2];
/*
15-14 Reserved for the IDENTIFY PACKET DEVICE command.
13 1=Standby timer values as specified in this standard are supported
   0=Standby timer values shall be managed by the device
12 Reserved for the IDENTIFY PACKET DEVICE command.
11 1=IORDY supported
   0=IORDY may be supported
10 1=IORDY may be disabled
9 Shall be set to one. Utilized by IDENTIFY PACKET DEVICE command.
8 Shall be set to one. Utilized by IDENTIFY PACKET DEVICE command.
7-0 retired
*/

/*
15 Shall be cleared to zero.
14 Shall be set to one.
13-1 Reserved.
0 Shall be set to one to indicate a device specific Standby timer value
minimum.
*/
  u16 retired7;
  u16 retired8;
  u16 unnamed1;
/*
15-3 Reserved
2 1=the fields reported in word 88 are valid
  0=the fields reported in word 88 are not valid
1 1=the fields reported in words 64-70 are valid
  0=the fields reported in words 64-70 are not valid
0 1=the fields reported in words 54-58 are valid
  0=the fields reported in words 54-58 may be valid
*/
  u16 number_of_current_logical_cylinders;
  u16 number_of_current_logical_heads;
  u16 number_of_current_logical_sectors_per_track;
  u16 current_capacity_in_sectors[2];
  u16 unnamed2;
/*
8 1=Multiple sector setting is valid
7-0 xxh=Current setting for number of sectors that shall be transferred per
interrupt on R/W Multiple command
*/
  u16 total_number_of_user_addressable_sectors[2];/* (LBA mode only) */
  u16 retired9;
  u16 unnamed3;
/*
10 1= Multiword DMA mode 2 is selected
   0= Multiword DMA mode 2 is not selected
9 1= Multiword DMA mode 1 is selected
  0= Multiword DMA mode 1 is not selected
8 1= Multiword DMA mode 0 is selected
  0= Multiword DMA mode 0 is not selected
2 1= Multiword DMA mode 2 and below are supported
1 1= Multiword DMA mode 1 and below are supported
0 1= Multiword DMA mode 0 is supported
*/
  u16 unnamed4;
/*
7-0 Advanced PIO modes supported
*/
  u16 minimum_multiword_dma_transfer_cycle_time_per_word;
/*
15-0 Cycle time in nanoseconds
*/
  u16 manufacturers_recommended_multiword_dma_transfer_cycle_time;
/*
15-0 Cycle time in nanoseconds
*/
  u16 minimum_pio_transfer_cycle_time_without_flow_control;
/*
15-0 Cycle time in nanoseconds
*/
  u16 minimum_pio_transfer_cycle_time_with_iordy_flow_control;
/*
15-0 Cycle time in nanoseconds
*/
  u16 reserved1; /* (for future command overlap and queuing) */
  u16 reserved2[4] /* for IDENTIFY PACKET DEVICE command.*/
  u16 queue_depth;
/*
4-0 Maximum queue depth - 1
*/
  u16 reserved3[4];

  u16 major_version;
/*
0000h or FFFFh = device does not report version
15 Reserved
14 Reserved for ATA/ATAPI-14
13 Reserved for ATA/ATAPI-13
12 Reserved for ATA/ATAPI-12
11 Reserved for ATA/ATAPI-11
10 Reserved for ATA/ATAPI-10
9 Reserved for ATA/ATAPI-9
8 Reserved for ATA/ATAPI-8
7 Reserved for ATA/ATAPI-7
6 Reserved for ATA/ATAPI-6
5 1=supports ATA/ATAPI-5
4 1=supports ATA/ATAPI-4
3 1=supports ATA-3
2 1=supports ATA-2
1 Obsolete
0 Reserved
*/
  u16 minor_version;
/*
0000h or FFFFh = device does not report version
0001h-FFFEh = see 8.12.43
*/
  u16 command_set[2];
/*
If words 82 and 83 = 0000h or FFFFh command set
notification not supported.
82
15 Obsolete
14 1=NOP command supported
13 1=READ BUFFER command supported
12 1=WRITE BUFFER command supported
11 Obsolete
10 1=Host Protected Area feature set supported
9 1=DEVICE RESET command supported
8 1=SERVICE interrupt supported
7 1=release interrupt supported
6 1=look-ahead supported
5 1=write cache supported
4 1=supports PACKET Command feature set
3 1=supports Power Management feature set
2 1=supports Removable Media feature set
1 1=supports Security Mode feature set
0 1=supports SMART feature set

83 
15 Shall be cleared to zero
14 Shall be set to one
13-7 Reserved
6 1=SET FEATURES subcommand required to spinup after power-up
5 1=Power-Up In Standby feature set supported
4 1=Removable Media Status Notification feature set supported
3 1=Advanced Power Management feature set supported
2 1=CFA feature set supported
1 1=READ/WRITE DMA QUEUED supported
0 1=DOWNLOAD MICROCODE command supported
*/
  u16 command_set_extensions; 
/*
Command set/feature supported extension. If words 82, 83, and 84 = 0000h or FFFFh
command set notification extension is not supported.

15 Shall be cleared to zero
14 Shall be set to one
*/
 u16 command_set_enable[2];
/* Command set/feature enabled. If words 85, 86, and 87 = 0000h or FFFFh command
set enabled notification is not supported.
85
15 Obsolete
14 1=NOP command supported
13 1=READ BUFFER command supported
12 1=WRITE BUFFER command supported
11 Obsolete
10 1=Host Protected Area feature set supported
9 1=DEVICE RESET command supported
8 1=SERVICE interrupt enabled
7 1=release interrupt enabled
6 1=look-ahead enabled
5 1=write cache enabled
4 1=supports PACKET Command feature set
3 1=supports Power Management feature set
2 1=supports Removable Media feature set
1 1= Security Mode feature set enabled
0 1= SMART feature set enabled

86
6 1=SET FEATURES subcommand required to spin-up after power-up
5 1=Power-Up In Standby feature set enabled
4 1=Removable Media Status Notification feature set enabled
3 1=Advanced Power Management feature set enabled
2 1=CFA feature set supported
1 1=READ/WRITE DMA QUEUED command supported
0 1=DOWNLOAD MICROCODE command supported
*/
  u16 command_set_default;
/*
15 Shall be cleared to zero
14 Shall be set to one
*/

  u16 unnamed5;
/*
12 1=Ultra DMA mode 4 is selected
   0=Ultra DMA mode 4 is not selected
11 1=Ultra DMA mode 3 is selected
   0=Ultra DMA mode 3 is not selected
10 1=Ultra DMA mode 2 is selected
   0=Ultra DMA mode 2 is not selected
9 1=Ultra DMA mode 1 is selected
  0=Ultra DMA mode 1 is not selected
8 1=Ultra DMA mode 0 is selected
  0=Ultra DMA mode 0 is not selected
4 1=Ultra DMA mode 4 and below are supported
3 1=Ultra DMA mode 3 and below are supported
2 1=Ultra DMA mode 2 and below are supported
1 1=Ultra DMA mode 1 and below are supported
0 1=Ultra DMA mode 0 is supported
*/

  u16 time_required_for_security_erase_unit_completion;
  u16 time_required_for_enhanced_security_erase_completion;

  u16 current_advanced_power_management_value;
  u16 master_password_revision_code;
  u16 hardware_reset_result;
/*
The contents of bits 12-0 of this word shall change only during
the execution of a hardware reset.
15 Shall be cleared to zero.
14 Shall be set to one.
13 1=device detected CBLID- above ViH
0=device detected CBLID- below ViL
12-8 Device 1 hardware reset result. Device 0 shall clear these bits to zero.
Device 1 shall set these bits as follows:
12 Reserved.
11 0= Device 1 did not assert PDIAG-.
1= Device 1 asserted PDIAG-.
10-9 These bits indicate how Device 1 determined the device number:
00=Reserved.
01=a jumper was used.
10=the CSEL signal was used.
11=some other method was used or the method is unknown.
8 Shall be set to one.
7-0 Device 0 hardware reset result. Device 1 shall clear these bits to zero.
Device 0 shall set these bits as follows:
7 Reserved.
6 0= Device 0 does not respond when Device 1 is selected.
1= Device 0 responds when Device 1 is selected.
5 0= Device 0 did not detect the assertion of DASP-.
1= Device 0 detected the assertion of DASP-.
4 0= Device 0 did not detect the assertion of PDIAG-.
1= Device 0 detected the assertion of PDIAG-.
3 0= Device 0 failed diagnostics.
1= Device 0 passed diagnostics.
2-1 These bits indicate how Device 0 determined the device number:
00=Reserved.
01=a jumper was used.
10=the CSEL signal was used.
11=some other method was used or the method is unknown.
0 Shall be set to one.
*/
  u16 reserved4[33];
  u16 removable_media_status_notification_feature_set_support;
/*

1-0 00=Removable Media Status Notification feature set not supported
    01=Removable Media Status Notification feature supported
    10=Reserved
    11=Reserved
*/
  u16 security_status;
/*
8 Security level 0=High, 1=Maximum
5 1=Enhanced security erase supported
4 1=Security count expired
3 1=Security frozen
2 1=Security locked
1 1=Security enabled
0 1=Security supported
*/
  u16 vendor_specific[31];
  u16 cfa_power_mode_1;
/*
15 Word 160 supported
13 CFA power mode 1 is required for one or more commands implemented by
the device
12 CFA power mode 1 disabled
11-0 Maximum current in ma
*/
  u16 reserved5[94];
  u16 integrity_word;
/*
15-8 Checksum
7-0 Signature
*/
} ata_identify_drive_type;

typedef struct
{
  unsigned int base_port;
  unsigned int irq;
  bool master_slave;

  unsigned int device_type;
  char model_number[41];
  char serial_number[21];
  bool lba;
  bool dma;
  u32 number_of_sectors;
  u32 number_of_heads;
  u32 sectors_per_track;
  u32 number_of_cylinders;
} ata_drive_type;

typedef struct
{
  unsigned int base_port;
  unsigned int irq;
  bool master_slave;
} ata_probe_type;

enum 
{
  ATA_HARD_DRIVE, 
  ATA_CDROM,
  ATA_UNKNOWN,  
};

extern bool select_device (ata_probe_type *ata_probe);