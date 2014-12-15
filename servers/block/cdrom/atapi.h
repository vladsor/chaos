
typedef u8  byte;
typedef u16 word;
typedef u32 dword;

typedef struct
{
  unsigned int port;
  char irq;
  bool ms;
} ATA_info_type;

typedef struct
{
  char manufacurer[40];
  char product[40];
  u32 revision;
} device_info_type;

typedef struct
{
  word Params1;
  word scsi1;
  byte len;
  word dummy2;
  byte Scsi2;
  char Manuf[8];
  char Prod[0x16];
  char Rev[4];
}Inf12Blk;

typedef struct
{
  word bkllen;
  byte state;
  byte undef[9];
  byte flags1, flags2, flags3, flags4;
  word maxspeed;
  byte undef2;
  byte audiosteps;
  word bufsize;
  word curspeed;
  word dummy[10];
}Cmd5AInfo;

typedef struct
{
  word	st1;
  byte	err0;
  byte  dummy1[9];
  byte	err1;
  byte	err2;
  byte	dummy2[4];
}Inf3Blk;

typedef struct
{
  byte res1;
  byte CA;
  byte number;
  byte res2;
  byte Start[4];
}OneTrk0;

typedef struct
{
  word Len;
  byte BegTrk;
  byte EndTrk;
  OneTrk0	Trk[11];
}TOC10;


extern u16 packet_close_tray[6];
extern u16 packet_eject_tray[6];
extern u16 packet_lock_tray[6];
extern u16 packet_unlock_tray[6];
extern u16 packet_read_sectors[6];
extern u16 packet_read_max_sectors[6];

extern word Info5A2A[6];
extern word Info12[6];
extern word Info3[6];
extern word RdToc[6];
extern word PlaySt[6];

extern Cmd5AInfo Buf5A2A;
extern Inf12Blk Info12Buf;
extern Inf3Blk  Info3Buf;
extern TOC10	TrkBuf;


extern bool init (void);
extern bool exec_ATAPI_command (ATA_info_type *ata_device, int dir, 
  u16 *command_packet, u16 *buffer, unsigned int bufflen);
extern bool read_block (ATA_info_type *cdrom_device, u32 start_block, 
                 u8 *buffer, unsigned int number_of_blocks);

extern ATA_info_type *cdrom_device;
extern unsigned int device_number;
