/*////////////////////////////////////////////////////////////////////////////
                                ATA/ATAPI STUFF
////////////////////////////////////////////////////////////////////////////*/
/* Delays from Linux ide.h (milliseconds) */
#define WAIT_READY      30      /* RDY asserted, use 5000 for notebook/APM */
#define WAIT_ID         30000   /* ATA device responds to 'identify' */
#define WAIT_PID        3       /* ATAPI device responds to 'identify' */
#define WAIT_CMD        10000   /* IRQ occurs in response to command */
#define WAIT_DRQ        20      /* DRQ asserted after ATA_CMD_WR(MUL) */

/* 'Cmd' field of 'drivecmd' structure */
#define DRV_CMD_RD      1
#define DRV_CMD_WR      2

/* ATA or ATAPI command structure */
typedef struct
{
    uint32_t Blk;        /* in SECTORS */
    uint32_t Count;      /* in BYTES */
    uint8_t Dev, Cmd, *Data;
} drivecmd;

/* ATA sector size */
#define ATA_LG_SECTSIZE         9       /* 512 byte ATA drive sectors */
#define ATA_SECTSIZE            (1 << (ATA_LG_SECTSIZE))

/* ATAPI sector size */
#define ATAPI_LG_SECTSIZE       11      /* 2K CD-ROM sectors */
#define ATAPI_SECTSIZE          (1 << (ATAPI_LG_SECTSIZE))

/* ATA drive command bytes */
#define ATA_CMD_RD      0x20            /* read one sector */
#define ATA_CMD_WR      0x30            /* write one sector */
#define ATA_CMD_PKT     0xA0            /* ATAPI packet cmd */
#define ATA_CMD_PID     0xA1            /* ATAPI identify */
#define ATA_CMD_RDMUL   0xC4            /* read multiple sectors */
#define ATA_CMD_WRMUL   0xC5            /* write multiple sectors */
#define ATA_CMD_ID      0xEC            /* ATA identify */

/* ATA drive flags */
#define ATA_FLG_ATAPI   0x0001          /* ATAPI drive */
#define ATA_FLG_LBA     0x0002          /* LBA-capable */
#define ATA_FLG_DMA     0x0004          /* DMA-capable */

/* ATA/ATAPI drive register file */
#define ATA_REG_DATA    0               /* data (16-bit) */
#define ATA_REG_FEAT    1               /* write: feature reg */
#define ATA_REG_ERR     ATA_REG_FEAT    /* read: error */
#define ATA_REG_CNT     2               /* ATA: sector count */
#define ATA_REG_REASON  ATA_REG_CNT     /* ATAPI: interrupt reason */
#define ATA_REG_SECT    3               /* sector */
#define ATA_REG_LOCYL   4               /* ATA: LSB of cylinder */
#define ATA_REG_LOCNT   ATA_REG_LOCYL   /* ATAPI: LSB of transfer count */
#define ATA_REG_HICYL   5               /* ATA: MSB of cylinder */
#define ATA_REG_HICNT   ATA_REG_HICYL   /* ATAPI: MSB of transfer count */
#define ATA_REG_DRVHD   6               /* drive select; head */
#define ATA_REG_CMD     7               /* write: drive command */
#define ATA_REG_STAT    7               /* read: status and error flags */
#define ATA_REG_SLCT    0x206           /* write: device control */
#define ATA_REG_ALTST   0x206           /* read: alternate status/error */

typedef struct /* 'identify' structure, as per ANSI ATA2 rev.2f spec */
{
    uint16_t Config, PhysCyls, Res2, PhysHeads, UnfBytesPerTrack;
    uint16_t UnfBytesPerSect, PhysSects, Vendor0, Vendor1, Vendor2;
    uint8_t  SerialNum[20];
    uint16_t BufType, BufSize, ECCBytes;
    uint8_t  FirmwareRev[8], Model[40], MaxMult, Vendor3;
    uint16_t DwordIO;
    uint8_t  Vendor4, Capability;
    uint16_t Res50;
    uint8_t  Vendor5, PIOMode, Vendor6, DMAMode;
    uint16_t LogValid, LogCyls, LogHeads, LogSects;
    uint32_t TotalSects;
    uint8_t  MultSect, MultSectValid;
    uint32_t LBASects;
    uint16_t DMAInfoSingle, DMAInfoMult, EIDEPIOModes;
    uint16_t EIDEDMAMin, EIDEDMATime, EIDEPIO, EIDEPIOIORdy;
/* This fixed the drive-goes-north-after-ATAPI-identify bug
        u16 Res69, Res70; } ataid; */
    uint16_t Res[187];
} ataid;

/* generalized drive info structure */
typedef struct
{
    uint16_t Flags;
    uint8_t  DrvSel;              /* ATA, ATAPI only (LUN for SCSI?) */
    uint8_t  MultSect;            /* ATA only */
    uint16_t Sects, Heads, Cyls;/* CHS ATA only */
    uint16_t IOAdr;
} drive;

/* ATAPI packet command bytes */
#define ATAPI_CMD_START_STOP    0x1B    /* eject/load */
#define ATAPI_CMD_READ10        0x28    /* read data sector(s) */
#define ATAPI_CMD_READTOC       0x43    /* read audio table-of-contents */
#define ATAPI_CMD_PLAY          0x47    /* play audio */
#define ATAPI_CMD_PAUSE         0x4B    /* pause/continue audio */

/* ATAPI data/command transfer 'phases' */
#define ATAPI_PH_ABORT          0       /* other possible phases (1, 2, */
#define ATAPI_PH_DONE           3       /* and 11) are invalid */
#define ATAPI_PH_DATAOUT        8
#define ATAPI_PH_CMDOUT         9
#define ATAPI_PH_DATAIN         10

typedef struct                  /* 4 bytes */
{
    uint8_t Res0, Min, Sec, Frame;
} atapimsf;

typedef struct                  /* 4 bytes */
{
    uint16_t TocLen;
    uint8_t FirstTrk;
    uint8_t LastTrk;
} atapitocheader;

typedef struct                  /* 8 bytes */
{
    uint8_t Res0;
/* In Linux ide.h, the next field was 'unsigned control : 4'
I thought "hey, unsigned is 32 bits under GNU"... and that led
to great confusion. The size of this structure _IS_ 8 bytes. */
    uint8_t Ctrl : 4;
    uint8_t Adr : 4;
    uint8_t Trk;
    uint8_t Res1;

    union
    {
        uint32_t Block;
        atapimsf Time;
    } Where;
} atapitocentry;

typedef struct
{
    atapitocheader Hdr;
    atapitocentry Ent[100];
} atapitoc;

