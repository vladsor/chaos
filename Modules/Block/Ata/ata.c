                                                                /* ata.c
******************************************************************************
        ata.c - ATA ("IDE") hard drive and ATAPI CD-ROM demo code
        Christopher Giese <geezer@netwurx.net>

        Release date 12/6/98. Distribute freely. ABSOLUTELY NO WARRANTY.

        Compile with Borland C or DJGPP:
                gcc -g -O2 -o ata.exe -fpack-struct ata.c
        *** USE -fpack-struct OPTION! ***

Sources:
        Linux ide.c, ide.h, hdreg.h
        (C) 1994-1996 Linus Torvalds, et al.
        Mark Lord <mlord@pobox.com>, Gadi Oxman <gadio@netvision.net.il>

        Linux ide-cd.c
        (C) 1994-1996 scott snyder <snyder@fnald0.fnal.gov>

        Linux cdrom.h
        (C) 1992 David Giller <rafetmad@oxy.edu>
                1994, 1995 Eberhard Moenkeberg <emoenke@gwdg.de>

        ide_spec.txt - Integrated Drive Electronics (IDE)
        Harwdare Reference & Information Document. Ver 1.00
        Compiled Jan 19th, 1994, by <cyborg@kauri.vuw.ac.nz>

        atadrvr.zip - ATA and ATAPI demo code
        No copyright - Hale Landis <landis@sugs.tware.com>

        sff8020.ps - ATAPI spec

        Table 0575 (format of partition record) from Ralf Brown's
        interrupt list (INTERRUP.D; listed under INT 19).

Fixes/changes:
        - CD-ROM now works properly after ATAPI 'identify'.

Bugs/to do:
        - Write a new ataXfer() that
          * allows reads to start in the middle of an ATA or ATAPI sector
                (no odd writes until a buffer cache system is added)
                (change Blk field of drivecmd [sectors] to Offset [bytes])
          * allows odd-length Count in drivecmd

        - Buffer cache

        - Queued drive operations

        - TEST drives on 2nd interface (0x170, IRQ15).

        - Still some arbitrary timeout values.

        - atapiCmd2() reads only 2048 bytes at a time. Is this normal?

        - False detection of slave ATA drive with Seagate ST3144A master
          (it's jumpered properly, and Linux and the BIOS work OK).

        - Lots of blocking delays. This code is only partially interrupt-
          driven, and not yet suitable for a high-performance OS.

        - Code needs more error checking and error-recovery.
*****************************************************************************/
#include <enviroment.h>

#include "ata.h"
#include "interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>


/*////////////////////////////////////////////////////////////////////////////
                LOW LEVEL FUNCTIONS AND BASIC DEFINTIONS
////////////////////////////////////////////////////////////////////////////*/
/* delay() inp() inpw() outp() outpw() */

#define delay(ms) timer_sleep_milli (ms)
static void msleep(int x)
{
    timer_sleep_milli (x);
}

#define inp(port) port_uint8_in (port)
#define outp(port,data) port_uint8_out (port,data)

#define inpw(port) port_uint16_in (port)
#define outpw(port,data) port_uint16_out (port,data)


#define         outb            outp
#define         outw            outpw
#define         inb             inp
#define         inw             inpw
#define min(a,b)    (((a) < (b)) ? (a) : (b))


/*****************************************************************************
        name:   nsleep
        action: precision delay for Count nanoseconds
                (not yet implemented)
*****************************************************************************/
void nsleep (unsigned Count)
{
    delay (1);
}

/*****************************************************************************
        name:   insw
        action: reads Count words (16-bit) from I/O port Adr to
                memory location Data
*****************************************************************************/
/*
void insw (unsigned Adr, uint16_t *Data, unsigned Count)
{
    for(; Count; Count--)
    {
        *Data++=inw(Adr);
    }
}
*/
#define insw port_uint16_in_string

/*****************************************************************************
        name:   outsw
        action: writes Count words (16-bit) from memory location Data
                to I/O port Adr
*****************************************************************************/
/*
void outsw (unsigned Adr, uint16_t *Data, unsigned Count)
{
    for(; Count; Count--)
    {
        outw(Adr, *Data++); 
    }
}
*/
#define outsw port_uint16_out_string

/*****************************************************************************
        name:   dump
        action: hexadecimal memory dump of Count bytes at Data
*****************************************************************************/

#define         BPERL           16      /* byte/line for dump */
/*
void dump (uint8_t *Data, unsigned Count)
{
    unsigned Byte1, Byte2;

    while(Count)
    {
        for(Byte1=0; Byte1 < BPERL; Byte1++, Count--)
        {
            if(Count == 0)
            {
                break;
            }
            
            printf("%02X ", Data[Byte1]);
        }

        printf("\t");
        
        for(Byte2=0; Byte2 < Byte1; Byte2++)
        {
            printf("%c", Data[Byte2] < ' ' ? '.' : Data[Byte2]);
        }
        
        printf("\n");
        Data += BPERL; 
    }
}
*/
/*****************************************************************************
        name:   awaitInterrupt
        action: waits with Timeout (mS) until interrupt(s) given by bitmask
                IRQMask occur
        returns:nonzero Mask value if interrupt occured, zero if timeout
*****************************************************************************/
int InterruptOccured;

int awaitInterrupt (uint16_t IRQMask, unsigned Timeout)
{
    uint16_t Intr = 0;
    
//    printf ("Waiting for %X (%X), timeout: %u.", InterruptOccured, IRQMask, Timeout);

    for(; Timeout; Timeout--)
    {
        Intr = InterruptOccured & IRQMask;
        if(Intr)
        {
            break;
        }
        msleep(1); 
    } /* XXX - blocking delay - fix */

    if(Timeout == 0)
    {
//        printf ("Waiting for %X, timeouted\n", IRQMask);
        return(0);
    }
    
//    printf ("Wait result: %X.\n", Intr);
    
    InterruptOccured &= ~Intr;
    
    return(Intr);
}

drive Drive[4];

/*****************************************************************************
        name:   ataProbe2
*****************************************************************************/
void ata_probe2 (unsigned WhichDrive)
{
    unsigned Temp1, Temp2;
    unsigned IOAdr, Temp;
    ataid DriveInfo;

    IOAdr = Drive[WhichDrive].IOAdr;
    Temp1 = inb (IOAdr + ATA_REG_CNT);
    Temp2 = inb (IOAdr + ATA_REG_SECT);
    
    if((Temp1 != 0x01) || (Temp2 != 0x01))
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, "nothing there\n");
//NO_DRIVE:
        Drive[WhichDrive].IOAdr = 0;
        
        return;
    }
    
    Temp1 = inb (IOAdr + ATA_REG_LOCYL);
    Temp2 = inb (IOAdr + ATA_REG_HICYL);
    Temp  = inb (IOAdr + ATA_REG_STAT);
    InterruptOccured = 0;

    if ((Temp1 == 0x14) && (Temp2 == 0xEB))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ATAPI CD-ROM, ");
        Drive[WhichDrive].Flags |= ATA_FLG_ATAPI;
        
/* issue ATAPI 'identify drive' command */
        Temp1 = ATA_CMD_PID;
        outb (IOAdr + ATA_REG_CMD, Temp1);
        Temp = WAIT_PID;
    }
    else if (Temp1 == 0 && Temp2 == 0 && Temp)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ATA hard drive, ");
        
/* issue ATA 'identify drive' command */
        Temp1 = ATA_CMD_ID;
        outb (IOAdr + ATA_REG_CMD, Temp1);
        Temp = WAIT_ID;
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, "unknown drive type\n");
        
//        goto NO_DRIVE;
        Drive[WhichDrive].IOAdr = 0;
        return;
    }
    
/* ATA or ATAPI: get results of of identify */
    nsleep(400);
    
    if(awaitInterrupt (0xC000, Temp) == 0)
/* XXX - could be old drive that doesn't support 'identify'.
Read geometry from partition table? Use (* gag *) CMOS? */
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "'identify' failed\n");
        
//        goto NO_DRIVE;
        Drive[WhichDrive].IOAdr = 0;
        return;
    }
    
/* grab info returned by 'identify' */
    (void) inb (IOAdr + ATA_REG_STAT);
    
/* for ATAPI CD-ROM, you MUST read 512 bytes here, or
drive will go comatose */
    insw (IOAdr + ATA_REG_DATA, (uint16_t *)&DriveInfo, sizeof(DriveInfo) / 2);
    Temp2 = 1;
    
    if(Temp1 == ATA_CMD_PID)
/* model name is not byte swapped for NEC, Mitsumi, and Pioneer drives */
    {
        if ((DriveInfo.Model[0] == 'N' && DriveInfo.Model[1] == 'E') ||
            (DriveInfo.Model[0] == 'F' && DriveInfo.Model[1] == 'X') ||
            (DriveInfo.Model[0] == 'P' && DriveInfo.Model[1] == 'i'))
        {
            Temp2 = 0;
        }
    }

    for(Temp=0; Temp < 40; Temp += 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%c", DriveInfo.Model[Temp ^ Temp2]);
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%c", DriveInfo.Model[Temp ^ Temp2 ^ 1]);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "\n""                CHS=%u:%u:%u, ",
        DriveInfo.PhysCyls, DriveInfo.PhysHeads, DriveInfo.PhysSects);
            
    Drive[WhichDrive].Sects = DriveInfo.PhysSects;
    Drive[WhichDrive].Heads = DriveInfo.PhysHeads;
    Drive[WhichDrive].Cyls = DriveInfo.PhysCyls;
        
    if(DriveInfo.Capability & 1)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "DMA, ");
        Drive[WhichDrive].Flags |= ATA_FLG_DMA;
    }
        
    if(DriveInfo.Capability & 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "LBA, ");
        Drive[WhichDrive].Flags |= ATA_FLG_LBA; 
    }
/* By Dobbs, I'll figure this out yet. Linux ide.c requires
        (DriveInfo.MultSectValid & 1) && DriveInfo.MultSect
The magic value then comes from DriveInfo.MaxMult

QUANTUM FIREBALL ST2.1A
        MaxMult=16      MultSect=16     MultSectValid=1
Conner Peripherals 850MB - CFS850A
        MaxMult=16      MultSect=0      MultSectValid=1
(Seagate) st3144AT
        MaxMult=0       MultSect=0      MultSectValid=0 */
        
    if((DriveInfo.MultSectValid & 1) && DriveInfo.MultSect)
    {
        Temp = DriveInfo.MaxMult;
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "MaxMult=%u, ", Temp);
    }
    else
    {
        Temp=1;
    }

    Drive[WhichDrive].MultSect = Temp;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%uK cache\n", DriveInfo.BufSize >> 1);

#if 0
printf("\n""Config=0x%X, PhysCyls=%u, Res2=%u, PhysHeads=%u, "
"UnfBytesPerTrack=%u\n""PhysSects=%u, Vendor0=%u, Vendor1=%u, "
"Vendor2=%u\n",
DriveInfo.Config, DriveInfo.PhysCyls, DriveInfo.Res2, DriveInfo.PhysHeads,
DriveInfo.UnfBytesPerTrack, DriveInfo.PhysSects, DriveInfo.Vendor0,
DriveInfo.Vendor1, DriveInfo.Vendor2);

printf("\n""BufType=%u, BufSize=%u, ECCBytes=%u, MaxMult=%u, Vendor3=%u, "
"DwordIO=%u\n""Vendor4=%u, Capability=0x%X\n",
DriveInfo.BufType, DriveInfo.BufSize, DriveInfo.ECCBytes, DriveInfo.MaxMult,
DriveInfo.Vendor3, DriveInfo.DwordIO, DriveInfo.Vendor4, DriveInfo.Capability);

printf("\n""Res50=%u, Vendor5=%u, PIOMode=%u, Vendor6=%u, DMAMode=%u, "
"LogValid=%u, LogCyls=%u\n""LogHeads=%u, LogSects=%u, ",
DriveInfo.Res50, DriveInfo.Vendor5, DriveInfo.PIOMode, DriveInfo.Vendor6,
DriveInfo.DMAMode, DriveInfo.LogValid, DriveInfo.LogCyls, DriveInfo.LogHeads,
DriveInfo.LogSects);

printf("TotalSects=%lu, MultSect=%u\n",
DriveInfo.TotalSects, DriveInfo.MultSect);

printf("MultSectValid=%u\n""LBASects=%lu\n",
DriveInfo.MultSectValid, DriveInfo.LBASects);

printf("\n""DMAInfoSingle=%u, DMAInfoMult=%u, EIDEPIOModes=%u, EIDEDMAMin=%u"
"\n""EIDEDMATime=%u, EIDEPIO=%u, EIDEPIOIORdy=%u\n" "\n",
DriveInfo.DMAInfoSingle, DriveInfo.DMAInfoMult, DriveInfo.EIDEPIOModes,
DriveInfo.EIDEDMAMin, DriveInfo.EIDEDMATime, DriveInfo.EIDEPIO,
DriveInfo.EIDEPIOIORdy);
#endif

    ata_block_create (WhichDrive, WhichDrive);
}

/*****************************************************************************
        name:   ataSelect
*****************************************************************************/
int ata_select (unsigned IOAdr, unsigned Sel)
{
    unsigned Temp;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s (%x, %x)\n",
	__FILE__, __FUNCTION__,
	IOAdr, Sel);

    Temp = inb (IOAdr + ATA_REG_DRVHD);
    
    if (((Temp ^ Sel) & 0x10) == 0)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "%s: Already selected.\n", 
	    __FUNCTION__);
	
        return (0);
    }
    
    outb (IOAdr + ATA_REG_DRVHD, Sel);
    nsleep(400);
    
    for (Temp = WAIT_READY; Temp; Temp--)
    {
        if ((inb(IOAdr + ATA_REG_STAT) & 0x80) == 0) 
        {
            break;
        }
        msleep(1);
    }    /* this _must_ be polled, I guess (sigh) */
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: Returns %u.\n", 
        __FUNCTION__, Temp);
    
    return (Temp == 0);
}

/*****************************************************************************
        name:   ataProbe
*****************************************************************************/
void ata_probe (void)
{
    unsigned Temp1, Temp2, WhichDrive;
    unsigned IOAdr, Temp;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ata_probe:\n");

/* set initial values */
    Drive[0].DrvSel = Drive[2].DrvSel = 0xA0;
    Drive[1].DrvSel = Drive[3].DrvSel = 0xB0;
    Drive[0].IOAdr  = Drive[1].IOAdr  = 0x1F0;
    Drive[2].IOAdr  = Drive[3].IOAdr  = 0x170;
        
    for (WhichDrive=0; WhichDrive < 4; WhichDrive += 2)
    {
        IOAdr = Drive[WhichDrive].IOAdr;
/* poke at the interface to see if anything's there */

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "ata_probe: poking interface 0x%03X\n", IOAdr);

        if (ata_select (IOAdr, 0xA0))
        {
            if (ata_select (IOAdr, 0xB0))
            {
//                goto NO_DRIVES;
                Drive[WhichDrive + 1].IOAdr = Drive[WhichDrive].IOAdr = 0;
                continue; 
            }
        }
            
        outb (IOAdr + ATA_REG_CNT, 0x55);
        outb (IOAdr + ATA_REG_SECT, 0xAA);
        Temp1 = inb (IOAdr + ATA_REG_CNT);
        Temp2 = inb (IOAdr + ATA_REG_SECT);

        if ((Temp1 != 0x55) || (Temp2 != 0xAA))
/* no master: clobber both master and slave */
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "ataProbe: no master on I/F 0x%03X\n", IOAdr);
//NO_DRIVES:            
            Drive[WhichDrive + 1].IOAdr = Drive[WhichDrive].IOAdr=0;
            continue; 
        }
        
/* soft reset both drives on this I/F (selects master) */
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "ataProbe: found something on I/F 0x%03X, doing soft reset...\n", 
            IOAdr);

        outb (IOAdr + ATA_REG_SLCT, 0x0E);
        nsleep (400);

/* release soft reset AND enable interrupts from drive */
        outb (IOAdr + ATA_REG_SLCT, 0x08);
        nsleep (400);
        
/* wait for master */
        for (Temp = 5000; Temp; Temp--)    /* XXX - why 2000? */
        {
            if ((inb (IOAdr + ATA_REG_STAT) & 0x80) == 0) 
            {
                break;
            }
            msleep(1); 
        }    /* XXX - blocking delay */
             
        if (Temp == 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "ataProbe: no master on I/F 0x%03X\n", 
                IOAdr);
//            goto NO_DRIVES; 
            Drive[WhichDrive + 1].IOAdr = Drive[WhichDrive].IOAdr=0;
            continue; 
        }

	/* identify master */
        ata_select (IOAdr, 0xA0);
	
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "  hd%1u (0x%03X, master): ", 
            WhichDrive, IOAdr);
        ata_probe2 (WhichDrive);
             
	/* select slave */
        if (ata_select (IOAdr, 0xB0))
	/* no response from slave: re-select master and continue */
        {
            ata_select (IOAdr, 0xA0);
            Drive[WhichDrive + 1].IOAdr=0;
            
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "ataProbe: no slave on I/F 0x%03X\n", 
                IOAdr);
            continue; 
        }
	
	/* identify slave */
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "  hd%1u (0x%03X,  slave): ", 
            WhichDrive + 1, IOAdr);
        
        ata_probe2 (WhichDrive + 1); 
    }
}

/*****************************************************************************
        name:   ataCmd2
*****************************************************************************/
void ata_cmd2 (drivecmd *Cmd, uint8_t Count, uint8_t CmdByte)
{
    uint8_t Sect, DrvHd;
    uint16_t Cyl, IOAdr;
    uint32_t Temp;

    IOAdr = Drive[Cmd->Dev].IOAdr;

    /* compute CHS or LBA register values */
    Temp = Cmd->Blk;

    if(Drive[Cmd->Dev].Flags & ATA_FLG_LBA)
    {
        Sect = Temp;              /* 28-bit sector adr: low byte */
        Cyl = Temp >> 8;          /* middle bytes */
        DrvHd = Temp >> 24;       /* high nybble */
        DrvHd = (DrvHd & 0x0F) | 0x40;/* b6 enables LBA */
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "ataCmd2: LBA=%lu\n", 
            Temp);
    }
    else
    {
        Sect = Temp % Drive[Cmd->Dev].Sects + 1;
        Temp /= Drive[Cmd->Dev].Sects;
        DrvHd = Temp % Drive[Cmd->Dev].Heads;
        Cyl = Temp / Drive[Cmd->Dev].Heads;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "ataCmd2: CHS=%u:%u:%u\n",
            Cyl, DrvHd, Sect);
    }
    
    DrvHd |= Drive[Cmd->Dev].DrvSel;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "ataCmd2: writing register file\n");
        
    outb (IOAdr + ATA_REG_CNT, Count);
    outb (IOAdr + ATA_REG_SECT, Sect);
    outb (IOAdr + ATA_REG_LOCYL, Cyl);
    Cyl >>= 8; /* compiler bug work-around */
    outb (IOAdr + ATA_REG_HICYL, Cyl);// >> 8);
    outb (IOAdr + ATA_REG_DRVHD, DrvHd);
        
    InterruptOccured=0;
    outb (IOAdr + ATA_REG_CMD, CmdByte);
    nsleep (400);
}

/*****************************************************************************
        name:   ataCmd
        action: ATA hard drive block read/write
        returns: 0 if OK
                -1 if drive could not be selected
                -2 if unsupported command
                -3 if command timed out
                -4 if bad/questionable drive status after command
*****************************************************************************/
int ata_cmd (drivecmd *Cmd)
{
    uint8_t Stat, CmdByte;
    uint32_t Count, Temp;
    uint16_t IOAdr;

    IOAdr = Drive[Cmd->Dev].IOAdr;

/* select the drive */
    if (ata_select (IOAdr, Drive[Cmd->Dev].DrvSel))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "ataCmd: could not select drive\n");
        
        return(-1);
    }
    
    if (Cmd->Cmd == DRV_CMD_RD)
/* convert general block device command code into ATA command byte:
ATA_CMD_RDMUL if drive supports multi-sector reads, ATA_CMD_RD if not */
    {
        if (Drive[Cmd->Dev].MultSect < 2) 
        {
            CmdByte = ATA_CMD_RD;
        }
        else 
        {
            CmdByte = ATA_CMD_RDMUL;
        }

        while (Cmd->Count)
/* if drive supports multisector read/write, transfer as many sectors as
possible (fewer interrupts). We rely on MultSect to limit Temp (the
sector count) to < 256 */
        {
            Temp = (Cmd->Count + ATA_SECTSIZE - 1) >> ATA_LG_SECTSIZE;
            Count = min(Temp, Drive[Cmd->Dev].MultSect);
            
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "ataCmd: ready to read %lu sector(s) of %lu\n", 
                Count, Temp);

/* compute CHS or LBA register values and write them, along with CmdByte */
            ata_cmd2 (Cmd, Count, CmdByte);

/* await read interrupt */
            if (awaitInterrupt(0xC000, WAIT_CMD) == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, "ataCmd: read timed out\n");
		
                (void) inb (IOAdr + ATA_REG_STAT);
		
                return(-3);
            }
            
/* check status */
            Stat = inb (IOAdr + ATA_REG_STAT);
	    
            if ((Stat & (0x81 | 0x58)) != 0x58)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		    "ataCmd: bad status (0x%02X) during read\n", 
		    Stat);
		    
                return(-4);
            }
            
/* advance pointers, read data */
            Cmd->Blk += Count;
            Count <<= ATA_LG_SECTSIZE;
            insw (IOAdr + ATA_REG_DATA, (uint16_t *)Cmd->Data, Count >> 1);
            Cmd->Data += Count;

/* XXX - Cmd->Count had better be a multiple of 512... */
            Cmd->Count -= Count;
        }
        
        return(0);
    }
    else if (Cmd->Cmd == DRV_CMD_WR)
/* convert general block device command code into ATA command byte:
ATA_CMD_WRMUL if drive supports multi-sector reads, ATA_CMD_WR if not */
    {
        if (Drive[Cmd->Dev].MultSect < 2)
        { 
            CmdByte=ATA_CMD_WR;
        }
        else 
        {
            CmdByte=ATA_CMD_WRMUL;
        }

        while(Cmd->Count)
/* if drive supports multisector read/write, transfer as many sectors as
possible (fewer interrupts). We rely on MultSect to limit Count
(the sector count) to < 256 */
        {
            Temp = (Cmd->Count + ATA_SECTSIZE - 1) >> ATA_LG_SECTSIZE;
            Count = min (Temp, Drive[Cmd->Dev].MultSect);
	    
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "ataCmd: ready to write %lu sector(s) of %lu\n", 
                Count, Temp);

/* compute CHS or LBA register values and write them, along with CmdByte */
            ata_cmd2 (Cmd, Count, CmdByte);

/* await DRQ */
            for (Temp = WAIT_DRQ; Temp; Temp--)
            {
                if (inb (IOAdr + ATA_REG_ALTST) & 0x08)
                {
                    break;
                }
            
                msleep (1); 
            }    /* XXX - blocking delay */
            
            if (Temp == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "ataCmd: no DRQ during write\n");
                
                (void) inb (IOAdr + ATA_REG_STAT);
                
                return (-3); 
            }
            
/* advance pointer, write data */
            Cmd->Blk += Count;
            Count <<= ATA_LG_SECTSIZE;
            outsw (IOAdr + ATA_REG_DATA, (uint16_t *)Cmd->Data, Count >> 1);

/* await write interrupt */
            Temp = awaitInterrupt(0xC000, WAIT_CMD);

            if (Temp == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "ataCmd: write timed out\n");
                
                (void) inb (IOAdr + ATA_REG_STAT);
                
                return(-3); 
            }
            
/* check status */
            Stat = inb (IOAdr + ATA_REG_STAT);
            if ((Stat & (0xA1 | 0x50)) != 0x50)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "ataCmd: bad status (0x%02X) during write\n", 
                    Stat);
                    
                return(-4); 
            }
            
/* advance pointers */
            Cmd->Data += Count;
            
/* XXX - Cmd->Count had better be a multiple of 512... */
            Cmd->Count -= Count; 
        }
	
        return (0); 
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "ataCmd: bad cmd (%u)\n", 
            Cmd->Cmd);
        
        return (-2);
    }
}

/*////////////////////////////////////////////////////////////////////////////
                                ATAPI-ONLY STUFF
////////////////////////////////////////////////////////////////////////////*/

/*****************************************************************************
        name:   atapiCmd2
        action: writes ATA register file including packet command byte,
                busy-waits until drive ready, then writes 12-byte ATAPI
                command packet, and services interrupts
        returns:0  if success
                -1 if drive could not be selected
                -3 timeout after writing pkt cmd byte (0xA0)
                -4 timeout after writing cmd pkt
                -5 data shortage (premature ATAPI_PH_DONE)
                -6 drive aborted command
                -7 bad drive phase
*****************************************************************************/
/* ATA_REG_STAT & 0x08 (DRQ)    ATA_REG_REASON          "phase"
        0                               0               ATAPI_PH_ABORT
        0                               1               bad
        0                               2               bad
        0                               3               ATAPI_PH_DONE
        8                               0               ATAPI_PH_DATAOUT
        8                               1               ATAPI_PH_CMDOUT
        8                               2               ATAPI_PH_DATAIN
        8                               3               bad
b0 of ATA_REG_REASON is C/nD (0=data, 1=command)
b1 of ATA_REG_REASON is IO (0=out to drive, 1=in from drive) */

int atapi_cmd2 (drivecmd *Cmd, uint8_t *Pkt)
{
    uint16_t IOAdr, Got;
    uint8_t  Phase;
    uint32_t Temp;

    IOAdr = Drive[Cmd->Dev].IOAdr;

    if (ata_select(IOAdr, Drive[Cmd->Dev].DrvSel))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "atapiCmd2: could not select drive\n");
        
        return (-1); 
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "atapiCmd2: writing register file\n");
    
    outb (IOAdr + ATA_REG_FEAT, 0);  /* irrelevant? */
    outb (IOAdr + ATA_REG_REASON, 0);/* irrelevant? */
    outb (IOAdr + ATA_REG_SECT, 0);  /* irrelevant? */
    outb (IOAdr + ATA_REG_LOCNT, 32768ul);
    outb (IOAdr + ATA_REG_HICNT, 32768ul >> 8);
    outb (IOAdr + ATA_REG_CMD, ATA_CMD_PKT);
    nsleep (400);
    
    for (Temp = 500; Temp; Temp--)     /* XXX - why 500? */
    {
        if ((inb (IOAdr + ATA_REG_STAT) & 0x88) == 0x08)
        {
            break;
        }
        
        msleep (1); 
    }    /* this _must_ be polled, I guess */
    
    if (Temp == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "atapiCmd2: drive did not accept pkt cmd byte\n");
        
        return (-3);
    }
    
    InterruptOccured = 0;
    outsw (IOAdr + ATA_REG_DATA, (uint16_t *)Pkt, 6);
    
    while(1)
    {
        if (awaitInterrupt(0xC000, WAIT_CMD) == 0)
        {
            (void) inb(IOAdr + ATA_REG_STAT);
            
            DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                "atapiCmd2: pkt cmd timed out\n");
            
            return(-4);
        }
        
        Phase = inb(IOAdr + ATA_REG_STAT) & 0x08;
        Phase |= (inb(IOAdr + ATA_REG_REASON) & 3);

        if (Phase == ATAPI_PH_DONE)
        {
            if(Cmd->Count)
            {
                /* could mean no CD or audio CD */
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "atapiCmd2: data shortage\n");

                return(-5); 
            }
            
            return(0);
        }
        else if(Phase == ATAPI_PH_ABORT)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "atapiCmd2: cmd aborted\n");
            
            return(-6);
        }
        else if(Phase != ATAPI_PH_DATAIN)
        /* ATAPI_PH_DATAOUT or ATAPI_PH_CMDOUT or something completely bogus */
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                "atapiCmd2: bad phase %u\n", 
                Phase);
            
            return (-7);
        }
        
        Got = inb (IOAdr + ATA_REG_HICNT);
        Got = (Got << 8) | inb(IOAdr + ATA_REG_LOCNT);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "<%5u bytes>   ", Got);
        
/* Cmd->Count=how many bytes we want to transfer
    Got=how many bytes are available for transfer
    Temp=smaller of these two 
*/
        Temp=min(Cmd->Count, Got);

/* read data. XXX - what if Temp odd?
XXX - allow read from middle of one sector to middle of another? */
        insw (IOAdr + ATA_REG_DATA, (uint16_t *)Cmd->Data, Temp >> 1);
        
/* read and discard surplus data */
        for (Got -= Temp; Got > 1; Got -= 2)
        { 
            inw(IOAdr + ATA_REG_DATA);
        }
        
        if(Got)
        {
            inb(IOAdr + ATA_REG_DATA);
        }
        
/* advance pointers */
        Cmd->Data += Temp;
        Cmd->Count -= Temp;
        Temp >>= ATAPI_LG_SECTSIZE;
        Cmd->Blk += Temp; 
    }
}

/*****************************************************************************
        name:   atapiCmd
        action: ATAPI device block read (and later, write)
        returns:0  if success
        returns: 0 if OK
                -1 if drive could not be selected
                -2 if unsupported command
                -3 timeout after writing pkt cmd byte (0xA0)
                -4 timeout after writing cmd pkt
                -5 data shortage (premature ATAPI_PH_DONE)
                -6 drive aborted command
                -7 bad drive phase
*****************************************************************************/
int atapi_cmd (drivecmd *Cmd)
{
    uint8_t Pkt[12];
    uint32_t Count;

/* convert general block device command code into ATAPI packet commands */
    if (Cmd->Cmd == DRV_CMD_RD)
    {
        Pkt[0] = ATAPI_CMD_READ10;
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "atapiCmd: bad cmd\n");
        
        return(-2);
    }
    
    Pkt[1] = 0;
    Pkt[2] = Cmd->Blk >> 24;
    Pkt[3] = Cmd->Blk >> 16;
    Pkt[4] = Cmd->Blk >> 8;
    Pkt[5] = Cmd->Blk;
    Count = Cmd->Count >> ATAPI_LG_SECTSIZE;
    Pkt[6] = Count >> 16;
    Pkt[7] = Count >> 8;
    Pkt[8] = Count;
    Pkt[9] = Pkt[10]=Pkt[11]=0;
    
    return (atapi_cmd2 (Cmd, Pkt)); 
}

/*****************************************************************************
        name:   atapiEject
        action: loads (Load == 0) or ejects (Load != 0) CD-ROM
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_eject (unsigned Load, unsigned WhichDrive)
{
    char Pkt[12] = {
        ATAPI_CMD_START_STOP,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };
    drivecmd Cmd;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "atapiEject\n");
    
    Cmd.Blk = 0;
    Cmd.Count = 0;
    Cmd.Dev = WhichDrive;
    Cmd.Cmd = 0;
    Cmd.Data = NULL;

    Pkt[4]=2 + (Load != 0);
    
    return (atapi_cmd2 (&Cmd, Pkt)); 
}

/*****************************************************************************
        name:   atapiPlay
        action: plays audio from time index Start to End (units of 1/75 sec)
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_play (unsigned WhichDrive, uint32_t Start, uint32_t End)
{
    char Pkt[12] = {
        ATAPI_CMD_PLAY,
        0, 0,
        0, 0, 0,        /* starting minute:second:frame */
        0, 0, 0,        /* ending M:S:F (frame=1/75 sec) */
        0, 0, 0 };
    drivecmd Cmd;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "atapiPlay\n");
    
    Cmd.Blk = 0;
    Cmd.Count = 0;
    Cmd.Dev = WhichDrive;
    Cmd.Cmd = 0;
    Cmd.Data = NULL;

    Pkt[5] = Start % 75;
    Start /= 75;
    Pkt[4] = Start % 60;
    Start /= 60;
    Pkt[3] = Start;

    Pkt[8] = End % 75;
    End /= 75;
    Pkt[7] = End % 60;
    End /= 60;
    Pkt[6] = End;

    return (atapi_cmd2 (&Cmd, Pkt));
}

/*****************************************************************************
        name:   atapiTOCEnt
        action: reads one or more table-of-contents entries from audio CD
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_TOCEnt(atapitoc *Contents, unsigned Count, unsigned WhichDrive)
{
    char Pkt[12]= {
        ATAPI_CMD_READTOC,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };
    drivecmd Cmd;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "atapiTOCEnt\n");
    
    Cmd.Blk = 0;
    Cmd.Count = Count;
    Cmd.Dev = WhichDrive;
    Cmd.Cmd = 0;
    Cmd.Data = (uint8_t *)Contents;

    Pkt[1] = 2;
    Pkt[6] = 0;
    Pkt[7] = Count >> 8;
    Pkt[8] = Count;
    Pkt[9] = 0;
    
    return (atapi_cmd2 (&Cmd, Pkt)); 
}

/*****************************************************************************
        name:   atapiTOC
        action: reads table of contents of audio CD and prints starting
                time of each track
        returns:whatever atapiCmd2() returns
*****************************************************************************/
#define MAX_TRACKS              32

atapimsf Track[MAX_TRACKS];
unsigned NumTracks;

int atapi_TOC (unsigned WhichDrive)
{
    atapitoc Contents;
    int Temp;

/* read just the header at first */
    Temp = sizeof (atapitocheader);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "atapiTOC: calling atapiTOCEnt with Count=%u\n", 
        Temp);
    
    Temp = atapi_TOCEnt (&Contents, Temp, WhichDrive);
    
    if (Temp)
    {
        return (Temp);
    }
    
    NumTracks = Contents.Hdr.LastTrk - Contents.Hdr.FirstTrk + 1;
    
    if (NumTracks <= 0 || NumTracks > 99)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "atapiTOC: bad number of tracks %d\n", 
            NumTracks);
        
        return (-1);
    }
    
    if (NumTracks > MAX_TRACKS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Too many tracks (%u); reducing to %u.\n",
            NumTracks, MAX_TRACKS);
            
        NumTracks = MAX_TRACKS; 
    }
    
    Temp = sizeof (atapitocheader) + (NumTracks + 1) * sizeof (atapitocentry);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "atapiTOC: calling atapiTOCEnt with Count=%u\n", 
        Temp);
    
    Temp = atapi_TOCEnt (&Contents, Temp, WhichDrive);

    if (Temp)
    {
        return (Temp);
    }
    
    for (Temp = 0; Temp <= NumTracks; Temp++)
    {
        Track[Temp].Min = Contents.Ent[Temp].Where.Time.Min;
        Track[Temp].Sec = Contents.Ent[Temp].Where.Time.Sec;
        Track[Temp].Frame = Contents.Ent[Temp].Where.Time.Frame;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%02u:%02u:%02u  ",
            Contents.Ent[Temp].Where.Time.Min,
            Contents.Ent[Temp].Where.Time.Sec,
            Contents.Ent[Temp].Where.Time.Frame);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
    
    return (0); 
}

/*****************************************************************************
        name:   atapiPause
        action: pauses (Play == 0) or continues (Play != 0) audio CD
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_pause (unsigned Play, unsigned WhichDrive)
{
    char Pkt[12]={
        ATAPI_CMD_PAUSE,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };
    drivecmd Cmd;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "atapiPause\n");
    
    Cmd.Blk = 0;
    Cmd.Count = 0;
    Cmd.Dev = WhichDrive;
    Cmd.Cmd = 0;
    Cmd.Data = NULL;

    Pkt[8] = (Play != 0);
    
    return (atapi_cmd2 (&Cmd, Pkt)); 
}
#if 0
/*////////////////////////////////////////////////////////////////////////////
                        GENERAL PARTITION STUFF
////////////////////////////////////////////////////////////////////////////*/
/*****************************************************************************
        name:   partProbe
        action: analyzes partitions on ATA drives
*****************************************************************************/
void partProbe(void)
{
    uint8_t Buffer[512], WhichDrive, WhichPart;
    unsigned HiHead, Scale, LHeads, Heads, Sects;
    long int Temp, Track;
    unsigned Offset, Cyls;
    drivecmd Cmd;

    printf("partProbe:\n");
    for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
    {
        if(Drive[WhichDrive].IOAdr == 0)
        {
            continue;
        }
            
        if(Drive[WhichDrive].Flags & ATA_FLG_ATAPI)
        {
            continue;
        }
/* load sector 0 (the partition table) */
                Cmd.Blk=0;
                Cmd.Count=512;
                Cmd.Dev=WhichDrive;
                Cmd.Cmd=DRV_CMD_RD;
                Cmd.Data=Buffer;
                Temp=ataCmd(&Cmd);
                if(Temp < 0) continue;
/* see if it's valid */
                if(Buffer[0x1FE] != 0x55 || Buffer[0x1FF] != 0xAA)
                {       printf("  hd%1u: invalid partition table\n",
                                WhichDrive);
                        continue; }
/* check all four primary partitions for highest Heads value */
                HiHead=0;
                for(WhichPart=0; WhichPart < 4; WhichPart++)
                {       Offset=0x1BE + 16 * WhichPart;
                        if(Buffer[Offset + 1] > HiHead)
                                HiHead=Buffer[Offset + 1];
                        if(Buffer[Offset + 5] > HiHead)
                                HiHead=Buffer[Offset + 5]; }
/* compare highest head value with heads/cylinder value from 'identify'.
Check for LARGE mode and determine Scale. This test will fail unless
partitions end on a cylinder boundary (hopefully, they do). */
                HiHead++;
                LHeads=Drive[WhichDrive].Heads;
                if(HiHead > LHeads)
                {       Scale=HiHead / LHeads;
                        printf("  hd%1u: LARGE mode, N=", WhichDrive);
                        if(Scale * LHeads == HiHead)
                        {       LHeads *= Scale;
                                printf("%u, new CHS=%u:%u:%u\n", Scale,
                                        Drive[WhichDrive].Cyls / Scale,
                                        LHeads,
                                        Drive[WhichDrive].Sects);  }
/* HiHead / Drive[WhichDrive].Heads is not an integer. */
                        else printf("??? (UNKNOWN !!!)\n"); }
/* now print geometry info for all primary partitions. CHS values in each
partition record may be faked for the benefit of MS-DOS/Win, so we ignore
them and use the 32-bit size-of-partition and sectors-preceding-partition
fields to compute CHS */
                for(WhichPart=0; WhichPart < 4; WhichPart++)
                {       Offset=0x1BE + 16 * WhichPart;
/* get 32-bit sectors-preceding-partition; skip if undefined partition */
                        Temp=*(uint32_t *)(Buffer + Offset + 8);
                        if(Temp == 0) continue;
/* convert to CHS, using LARGE mode value of Heads if necessary */
                        Sects=Temp % Drive[WhichDrive].Sects + 1;
                        Track=Temp / Drive[WhichDrive].Sects;
                        Heads=Track % LHeads;
                        Cyls=Track / LHeads;
                        printf("  hd%1u%c: start LBA=%8lu, start CHS=%4u:"
                                "%2u:%2u, ", WhichDrive, 'a' + WhichPart,
                                Temp, Cyls, Heads, Sects);
/* get 32-bit partition size */
                        Temp=*(uint32_t *)(Buffer + Offset + 12);
                        printf("%lu sectors\n", Temp); 
        }
    }
}
#endif

/*////////////////////////////////////////////////////////////////////////////
                        IRQ, DEMO, AND MAIN ROUTINES
////////////////////////////////////////////////////////////////////////////*/
#define         IRQ14_VECTOR            118
#define         IRQ15_VECTOR            119

#define         CHAIN_INTS

//#define               BUFF_SIZE               49152u
#define         BUFF_SIZE               16384

drivecmd Cmd;
char Buffer[BUFF_SIZE];

/*****************************************************************************
        name:   irq14
        action: IRQ 14 handler
*****************************************************************************/
void irq14 (void)
{
    InterruptOccured |= 0x4000;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\nIRQ14\n");
//        outb(0xA0, 0x20);
//        nsleep(1000);
//        outb(0x20, 0x20); 
}

/*****************************************************************************
        name:   irq15
        action: IRQ 15 handler
*****************************************************************************/
void irq15 (void)
{
    InterruptOccured |= 0x8000;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\nIRQ15\n");
//        outb(0xA0, 0x20);
//        nsleep(1000);
//        outb(0x20, 0x20); 
}

/*****************************************************************************
        name:   irqStart
        action: saves old interrupt vectors, installs new handlers
*****************************************************************************/
void irqStart(void)
{
    irq_register (14, irq14);
    irq_register (15, irq15); 
}
/*****************************************************************************
        name:   irqEnd
        action: restores old IRQ handlers
*****************************************************************************/
void irqEnd(void)
{
    irq_unregister (14);
    irq_unregister (15);
}

#if 0
/*****************************************************************************
        name:   demo
        action: loads interesting sectors from ATA and ATAPI drives
                and dumps them in hex
*****************************************************************************/
void demo(void)
{
    unsigned Count, WhichDrive;

        for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
        {       if(Drive[WhichDrive].IOAdr == 0) continue;
                Cmd.Dev=WhichDrive;
                Cmd.Cmd=DRV_CMD_RD;
                Cmd.Data=Buffer;
                if(Drive[WhichDrive].Flags & ATA_FLG_ATAPI)
/* CD-ROM has it's root directory at logical block #16. According to
ISO-9660, the first 16 blocks (2048 bytes each) are all zeroes. (These
blocks might now be used for El Torrito boot-from-CD.) */
                {       Count=17;
                        Cmd.Blk=17 - Count;
                        Cmd.Count=Count << ATAPI_LG_SECTSIZE;
                        printf("atapiCmd() returned %d\n", atapiCmd(&Cmd));
                        dump(Buffer + ATAPI_SECTSIZE * (Count - 1), 96); }
                else
/* load first sector of first partition, plus the MultSect sectors before it,
to demonstrate multisector read (if supported) */
                {       Count=Drive[WhichDrive].MultSect + 1;
                        Cmd.Blk=Drive[WhichDrive].Sects + 1 - Count;
                        Cmd.Count=Count << ATA_LG_SECTSIZE;
                        printf("ataCmd() returned %d\n", ataCmd(&Cmd));
                        dump(Buffer + ATA_SECTSIZE * (Count - 1), 96);
        }
    }
}

#ifdef MAIN_TEST

/*****************************************************************************
        name:   main
*****************************************************************************/
int ata_main(void)
{       unsigned Data, WhichDrive, Temp;
        long Blk, Count;

        irqStart();
/* enable IRQ14 and IRQ15 at the 2nd 8259 PIC chip */
//        outb(0xA1, inb(0xA1) & ~0xC0);

        ataProbe();
	goto BAIL;
	
        partProbe();
#if 0
/* atapiCmd demonstrates data CDs */
        demo();
//#else
/* atapiTOC and atapiPlay demonstrate audio CDs */
        for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
        {       if(Drive[WhichDrive].IOAdr &&
                        (Drive[WhichDrive].Flags & ATA_FLG_ATAPI)) break; }
        if(WhichDrive == 4)
        {       printf("No ATAPI devices detected.\n");
                goto BAIL; }
        printf("\n");
        atapiTOC(WhichDrive);
        for(Count=3; Count; Count--)
/* play from 13:11:32 to 18:01:00 -- Zeppelin */
        {
            Temp=atapiPlay(WhichDrive, (13ul * 60 + 11) * 75 + 32, (18ul * 60 + 1) * 75 + 0);
            if(Temp)
            {
                printf("atapiPlay returned error %d, retrying...\n", Temp);
            }
            else
            {
                break;
            }
        }
#endif

#if 0
#define         START_BLK               2048ul
#define         NUM_BLKS                8192ul
        printf( "\n""********************************************************\n"
                "***                      DANGER!                     ***\n"
                "********************************************************\n"
                "THIS OPERATION WILL ERASE PORTIONS OF YOUR HARD DRIVE!!!\n" "\n"
                "Press 'y' to continue.\n""\x07\x07\x07");
        Temp=getch();
        if(Temp != 'y' && Temp !='Y') goto BAIL;
        printf( "\n""********************************************************\n"
                "***                 SECOND WARNING!                  ***\n"
                "********************************************************\n"
                "Are you sure you want to ERASE YOUR HARD DRIVE?\n" "\n"
                "Press 'p' to proceed.\n""\x07");
        Temp=getch();
        if(Temp != 'p' && Temp != 'P') goto BAIL;
        Cmd.Dev=0;
        srand(2);
        Cmd.Cmd=DRV_CMD_WR;
/* write NUM_BLKS of pseudorandom data to beginning of drive. Skips
START_BLK sectors, which may or may not leave the FAT, DOS kernel files,
and COMMAND.COM intact. THIS ERASES DATA ON THE DRIVE!!! */
        for(Blk=START_BLK; Blk < START_BLK + NUM_BLKS; )
        {       for(Temp=0; Temp < BUFF_SIZE; Temp++) Buffer[Temp]=rand();
                printf("writing Blk %lu\r", Blk);
                Cmd.Data=Buffer;
                Cmd.Blk=Blk;
                Count=min(BUFF_SIZE >> 9, START_BLK + NUM_BLKS - Blk);
                Cmd.Count=Count << 9;
                Temp=ataCmd(&Cmd);
                if(Temp)
                {       printf("\n""ataCmd(write) returned %d\n", Temp);
                        break; }
                Blk += Count; }
        printf("\n");
        srand(2);
        Cmd.Cmd=DRV_CMD_RD;
/* read NUM_BLKS of data from beginning of drive, verify against same
pseudorandom sequence that was written */
        for(Blk=START_BLK; Blk < START_BLK + NUM_BLKS; )
        {       printf("reading Blk %lu\r", Blk);
                Cmd.Data=Buffer;
                Cmd.Blk=Blk;
                Count=min(BUFF_SIZE >> 9, START_BLK + NUM_BLKS - Blk);
                Cmd.Count=Count << 9;
                Temp=ataCmd(&Cmd);
                if(Temp)
                {       printf("\n""ataCmd(read) returned %d\n", Temp);
                        break; }
                for(Temp=0; Temp < min(BUFF_SIZE,
                        (START_BLK + NUM_BLKS - Blk) << 9); Temp++)
                {       Data=rand();
                        if(Buffer[Temp] != Data)
                        {       printf("\n""verify failed, Blk %lu, offset "
                                        "%u (wanted %u, got %u)\n", Blk,
                                        Temp,   Data, Buffer[Temp]);
                                break; }}
                Blk += Count; }
#endif
BAIL:   printf("\n");
        irqEnd();
        return 0;
}

#endif
#endif

