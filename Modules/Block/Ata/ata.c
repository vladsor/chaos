#include <enviroment.h>

#include "ata.h"
#include "interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>



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
        timer_sleep_milli (1); 
    } /* XXX - blocking delay - fix */

    if (Timeout == 0)
    {
//        printf ("Waiting for %X, timeouted\n", IRQMask);
        return(0);
    }
    
//    printf ("Wait result: %X.\n", Intr);
    
    InterruptOccured &= ~Intr;
    
    return(Intr);
}


/*****************************************************************************
        name:   ataSelect
*****************************************************************************/
bool ata_select (uint16_t io_base, uint8_t command)
{
    unsigned Temp;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%x, %x)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        io_base, command);

    Temp = port_uint8_in (IOAdr + ATA_REG_DRVHD);
    
    if (((Temp ^ command) & 0x10) == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: Already selected.\n", 
            __FUNCTION__);
    
        return TRUE;
    }
    
    port_uint8_out (io_base + ATA_REG_DRVHD, command);

    timer_sleep_milli (400);
    
    for (Temp = WAIT_READY; Temp; Temp--)
    {
        if ((port_uint8_in (io_base + ATA_REG_STAT) & 0x80) == 0) 
        {
            break;
        }
        timer_sleep_milli (1);
    }    /* this _must_ be polled, I guess (sigh) */
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: Returns %u.\n", 
        __FUNCTION__, Temp);
    
    return (Temp != 0);
}

/*****************************************************************************
        name:   ataProbe
*****************************************************************************/
bool ata_probe (void)
{
    unsigned Temp1, Temp2, WhichDrive;
    unsigned IOAdr, Temp;
    drive_t drive[4];

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* set initial values */
    drive[0].drive_select = drive[2].drive_select = 0xA0;
    drive[1].drive_select = drive[3].drive_select = 0xB0;
    drive[0].io_address  = drive[1].io_address  = 0x1F0;
    drive[2].io_address  = drive[3].io_address  = 0x170;
        
    for (WhichDrive = 0; WhichDrive < 4; WhichDrive += 2)
    {
        IOAdr = Drive[WhichDrive].IOAdr;
        /* poke at the interface to see if anything's there */

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s: %s: poking interface 0x%03X\n", 
            DEBUG_MODULE_NAME, __FUNCTION__,
            IOAdr);

        if (!ata_select (IOAdr, 0xA0))
        {
            if (!ata_select (IOAdr, 0xB0))
            {
                continue; 
            }
        }
            
        port_uint8_out (IOAdr + ATA_REG_CNT, 0x55);
        port_uint8_out (IOAdr + ATA_REG_SECT, 0xAA);
        Temp1 = port_uint8_in (IOAdr + ATA_REG_CNT);
        Temp2 = port_uint8_in (IOAdr + ATA_REG_SECT);

        if ((Temp1 != 0x55) || (Temp2 != 0xAA))
        /* no master: clobber both master and slave */
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "%s: %s: no master on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);

            continue; 
        }
        
        /* soft reset both drives on this I/F (selects master) */
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "ataProbe: found something on I/F 0x%03X, doing soft reset...\n", 
            IOAdr);

        port_uint8_out (IOAdr + ATA_REG_SLCT, 0x0E);
        timer_sleep_milli (400);

        /* release soft reset AND enable interrupts from drive */
        port_uint8_out (IOAdr + ATA_REG_SLCT, 0x08);
        timer_sleep_milli (400);
        
        /* wait for master */
        for (Temp = 5000; Temp; Temp--)
        {
            if ((port_uint8_in (IOAdr + ATA_REG_STAT) & 0x80) == 0) 
            {
                break;
            }
            timer_sleep_milli (1); 
        }    /* XXX - blocking delay */
             
        if (Temp == 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "%s: %s: no master on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);

            continue; 
        }

        /* identify master */
        ata_select (IOAdr, 0xA0);
    
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "  hd%1u (0x%03X, master): ", 
            WhichDrive, IOAdr);
            
        if (ata_internal_probe (&drive[WhichDrive])
        {
            handle_t device;
            char name[STRING_MAX_LENGTH];

            device = ata$create (&drive[WhichDrive]);
            string_print (name, "/storm/devices/ata%0", WhichDrive);
            global_namespace_bind (name, device);
        }
             
        /* select slave */
        if (!ata_select (IOAdr, 0xB0))
        /* no response from slave: re-select master and continue */
        {
            ata_select (IOAdr, 0xA0);
            
            DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
                "%s: %s: no slave on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);
            continue; 
        }
    
        /* identify slave */
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "  hd%1u (0x%03X,  slave): ", 
            WhichDrive + 1, IOAdr);
        
        if (ata_internal_probe (&drive[WhichDrive + 1]))
        {
            handle_t device;
            char name[STRING_MAX_LENGTH];

            device = ata$create (&drive[WhichDrive + 1]);
            string_print (name, "/storm/devices/ata%0", WhichDrive + 1);
            global_namespace_bind (name, device);
        }
    }
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
int ata_command (p_drive_t drive, p_drive_command_t command)
{
    uint8_t Stat, CmdByte;
    uint32_t Count, Temp;
    uint16_t IOAdr;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, command);

    IOAdr = drive->io_address;

    /* select the drive */
    if (!ata_select (IOAdr, drive->drive_select))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: could not select drive\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return (-1);
    }
    
    if (command->command == DRIVE_COMMAND_READ)
    /* convert general block device command code into ATA command byte:
       ATA_CMD_RDMUL if drive supports multi-sector reads, ATA_CMD_RD if not */
    {
        if (drive->multi_sectors < 2) 
        {
            CmdByte = ATA_CMD_RD;
        }
        else 
        {
            CmdByte = ATA_CMD_RDMUL;
        }

        while (command->count)
        /* if drive supports multisector read/write, transfer as many sectors
           as possible (fewer interrupts). We rely on MultSect to limit Temp 
           (the sector count) to < 256 */
        {
            Temp = (command->count + ATA_SECTSIZE - 1) >> ATA_LG_SECTSIZE;
            Count = MIN (Temp, drive->multi_sectors);
            
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: %s: ready to read %u sector(s) of %u\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                Count, Temp);

            /* compute CHS or LBA register values and write them, along with
               CmdByte */
            ata_internal_command (drive, command, Count, CmdByte);

            /* await read interrupt */
            if (awaitInterrupt (0xC000, WAIT_CMD) == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, "ataCmd: read timed out\n");
        
                (void) port_uint8_in (IOAdr + ATA_REG_STAT);
        
                return (-3);
            }
            
            /* check status */
            Stat = port_uint8_in (IOAdr + ATA_REG_STAT);
        
            if ((Stat & (0x81 | 0x58)) != 0x58)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "%s: %s: bad status (0x%02X) during read\n", 
                    DEBUG_MODULE_NAME, __FUNCTION__,
                    Stat);
            
                return (-4);
            }
            
            /* advance pointers, read data */
            command->bulk += Count;
            Count <<= ATA_LG_SECTSIZE;
            port_uint16_in_string (IOAdr + ATA_REG_DATA, 
                (uint16_t *) command->data, Count >> 1);
            command->data += Count;

            /* XXX - Cmd->Count had better be a multiple of 512... */
            command->count -= Count;
        }
        
        return (0);
    }
    else if (command->command == DRIVE_COMMAND_WRITE)
    /* convert general block device command code into ATA command byte:
       ATA_CMD_WRMUL if drive supports multi-sector reads, ATA_CMD_WR if not */
    {
        if (drive->multi_sectors < 2)
        { 
            CmdByte = ATA_CMD_WR;
        }
        else 
        {
            CmdByte = ATA_CMD_WRMUL;
        }

        while (command->count)
        /* if drive supports multisector read/write, transfer as many sectors
           as possible (fewer interrupts). We rely on MultSect to limit Count
           (the sector count) to < 256 */
        {
            Temp = (command->count + ATA_SECTSIZE - 1) >> ATA_LG_SECTSIZE;
            Count = MIN (Temp, drive->multi_sectors);
        
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: %s: ready to write %u sector(s) of %u\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                Count, Temp);

            /* compute CHS or LBA register values and write them, along with CmdByte */
            ata_internal_command (drive, command, Count, CmdByte);

            /* await DRQ */
            for (Temp = WAIT_DRQ; Temp; Temp--)
            {
                if (port_uint8_in (IOAdr + ATA_REG_ALTST) & 0x08)
                {
                    break;
                }
            
                timer_sleep_milli (1); 
            }    /* XXX - blocking delay */
            
            if (Temp == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "%s: %s: no DRQ during write\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);
                
                (void) port_uint8_in (IOAdr + ATA_REG_STAT);
                
                return (-3); 
            }
            
            /* advance pointer, write data */
            command->bulk += Count;
            Count <<= ATA_LG_SECTSIZE;
            port_uint16_out_string (IOAdr + ATA_REG_DATA, 
                (uint16_t *) command->data, Count >> 1);

            /* await write interrupt */
            Temp = awaitInterrupt (0xC000, WAIT_CMD);

            if (Temp == 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "ataCmd: write timed out\n");
                
                (void) port_uint8_in (IOAdr + ATA_REG_STAT);
                
                return(-3); 
            }
            
            /* check status */
            Stat = port_uint8_in (IOAdr + ATA_REG_STAT);
            if ((Stat & (0xA1 | 0x50)) != 0x50)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "%s: %s: bad status (0x%02X) during write\n", 
                    DEBUG_MODULE_NAME, __FUNCTION__,
                    Stat);
                    
                return (-4); 
            }
            
            /* advance pointers */
            command->data += Count;
            
            /* XXX - Cmd->Count had better be a multiple of 512... */
            command->count -= Count; 
        }
    
        return (0); 
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: bad cmd (%u)\n", 
            DEBUG_MODULE_NAME, __FUNCTION__,
            command->command);
        
        return (-2);
    }
}


/*****************************************************************************
        name:   irq14
        action: IRQ 14 handler
*****************************************************************************/
void irq14 (void)
{
    InterruptOccured |= 0x4000;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\nIRQ14\n");
}

/*****************************************************************************
        name:   irq15
        action: IRQ 15 handler
*****************************************************************************/
void irq15 (void)
{
    InterruptOccured |= 0x8000;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\nIRQ15\n");
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


