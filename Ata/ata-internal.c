/*****************************************************************************
        name:   ataProbe2
*****************************************************************************/
bool ata_internal_probe (p_drive_t drive)
{
    unsigned Temp1, Temp2;
    unsigned IOAdr, Temp;
    ata_id_t drive_info;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive);

    IOAdr = drive->io_address;
    Temp1 = port_uint8_in (IOAdr + ATA_REG_CNT);
    Temp2 = port_uint8_in (IOAdr + ATA_REG_SECT);
    
    if ((Temp1 != 0x01) || (Temp2 != 0x01))
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, "nothing there\n");
     
        return FALSE;
    }
    
    Temp1 = port_uint8_in (IOAdr + ATA_REG_LOCYL);
    Temp2 = port_uint8_in (IOAdr + ATA_REG_HICYL);
    Temp  = port_uint8_in (IOAdr + ATA_REG_STAT);
    InterruptOccured = 0;

    if ((Temp1 == 0x14) && (Temp2 == 0xEB))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ATAPI CD-ROM, ");
        drive->flags |= ATA_FLG_ATAPI;
        
        /* issue ATAPI 'identify drive' command */
        Temp1 = ATA_CMD_PID;
        port_uint8_out (IOAdr + ATA_REG_CMD, Temp1);
        Temp = WAIT_PID;
    }
    else if (Temp1 == 0 && Temp2 == 0 && Temp)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ATA hard drive, ");
        
        /* issue ATA 'identify drive' command */
        Temp1 = ATA_CMD_ID;
        port_uint8_out (IOAdr + ATA_REG_CMD, Temp1);
        Temp = WAIT_ID;
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, "unknown drive type\n");
        
        return FALSE;
    }
    
    /* ATA or ATAPI: get results of of identify */
    timer_sleep_milli (400);
    
    if (awaitInterrupt (0xC000, Temp) == 0)
    /* XXX - could be old drive that doesn't support 'identify'.
       Read geometry from partition table? Use (* gag *) CMOS? */
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "'identify' failed\n");
        
        return FALSE;
    }
    
    /* grab info returned by 'identify' */
    (void) port_uint8_in (IOAdr + ATA_REG_STAT);
    
    /* for ATAPI CD-ROM, you MUST read 512 bytes here, or
       drive will go comatose */
    port_uint16_in_string (IOAdr + ATA_REG_DATA, (uint16_t *) &drive_info,
        sizeof (drive_info) / 2);
    Temp2 = 1;
    
    if (Temp1 == ATA_CMD_PID)
    /* model name is not byte swapped for NEC, Mitsumi, and Pioneer drives */
    {
        if ((drive_info.Model[0] == 'N' && drive_info.Model[1] == 'E') ||
            (drive_info.Model[0] == 'F' && drive_info.Model[1] == 'X') ||
            (drive_info.Model[0] == 'P' && drive_info.Model[1] == 'i'))
        {
            Temp2 = 0;
        }
    }

    for (Temp = 0; Temp < 40; Temp += 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%c", drive_info.Model[Temp ^ Temp2]);
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%c", drive_info.Model[Temp ^ Temp2 ^ 1]);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "\n""                CHS=%u:%u:%u, ",
        drive_info.PhysCyls, drive_info.PhysHeads, drive_info.PhysSects);
            
    drive->sectors = drive_info.PhysSects;
    drive->heads = drive_info.PhysHeads;
    drive->cylinders = drive_info.PhysCyls;
        
    if (drive_info.Capability & 1)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "DMA, ");
        drive->flags |= ATA_FLG_DMA;
    }
        
    if (drive_info.Capability & 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "LBA, ");
        drive->flags |= ATA_FLG_LBA; 
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
        
    if ((drive_info.MultSectValid & 1) && drive_info.MultSect)
    {
        Temp = drive_info.MaxMult;
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "MaxMult=%u, ", Temp);
    }
    else
    {
        Temp = 1;
    }

    drive->multi_sectors = Temp;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%uK cache\n", 
        drive_info.BufSize >> 1);

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
 
    return TRUE;
}

/*****************************************************************************
        name:   ataCmd2
*****************************************************************************/
void ata_internal_command (p_drive_t drive, p_drive_command_t command, 
    uint8_t count, uint8_t command_byte)
{
    uint8_t sectors;
    uint8_t heads;
    uint16_t cylinder;
    uint16_t io_base;
    uint32_t Temp;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %u, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, command, count, command_byte);
    
    io_base = drive->io_address;

    /* compute CHS or LBA register values */
    Temp = command->bulk;

    if (drive->flags & ATA_FLG_LBA)
    {
        sector = Temp;              /* 28-bit sector adr: low byte */
        cylinder = Temp >> 8;          /* middle bytes */
        head = Temp >> 24;       /* high nybble */
        head = (head & 0x0F) | 0x40;/* b6 enables LBA */
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: %s: LBA = %u\n", 
            DEBUG_MODULE_NAME, __FUNCTION__,
            Temp);
    }
    else
    {
        sector = Temp % drive->sectors + 1;
        Temp /= drive->sectors;
        head = Temp % drive->heads;
        cylinder = Temp / drive->heads;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: %s: CHS = %u:%u:%u\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            cylinder, head, sector);
    }
    
    head |= drive->drive_select;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: writing register file\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    port_uint8_out (io_base + ATA_REG_CNT, count);
    port_uint8_out (io_base + ATA_REG_SECT, sector);
    port_uint8_out (io_base + ATA_REG_LOCYL, cylinder);
    port_uint8_out (io_base + ATA_REG_HICYL, cylinder >> 8);
    port_uint8_out (io_base + ATA_REG_DRVHD, head);
        
    InterruptOccured = 0;
    port_uint8_out (IOAdr + ATA_REG_CMD, command_byte);

    timer_sleep_milli (400);
}

