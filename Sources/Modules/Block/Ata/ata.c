#include <enviroment.h>

#include <string.h>

#include <Classes/kernel.h>
#include <Classes/ata_drive.h>

#include "Include/ata.h"
#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"ATA"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (ata_debug_supplier)
#endif

#include <debug/macros.h>
#include <exception/macros.h>

/*****************************************************************************
        name:   ataSelect
*****************************************************************************/
bool ata_select (uint16_t io_base, uint8_t command)
{
    unsigned int state;
    unsigned int timeout;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s (%x, %x)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        io_base, command);

    state = port_uint8_in (io_base + ATA_REG_DRVHD);
    
    if (((state ^ command) & 0x10) == 0)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L"%S: %s: Already selected.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);
    
        return TRUE;
    }
    
    port_uint8_out (io_base + ATA_REG_DRVHD, command);

//    timer_sleep_milli (400);
    cpu_sleep_milli (CPU_CURRENT, 400);
    
    for (timeout = WAIT_READY; timeout > 0; timeout--)
    {
        if ((port_uint8_in (io_base + ATA_REG_STAT) & 0x80) == 0) 
        {
            break;
        }
//        timer_sleep_milli (1);
        cpu_sleep_milli (CPU_CURRENT, 1);
    }    /* this _must_ be polled, I guess (sigh) */
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: %s: Timeout %u.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        timeout);
    
    return (timeout != 0);
}

static drive_t drive[4];

/*****************************************************************************
        name:   ataProbe
*****************************************************************************/
bool ata_probe (void)
{
    unsigned Temp1, Temp2, WhichDrive;
    unsigned IOAdr;
    uint32_t timeout;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* set initial values */
    drive[0].drive_select = drive[2].drive_select = 0xA0;
    drive[1].drive_select = drive[3].drive_select = 0xB0;
    
    drive[0].io_address  = drive[1].io_address  = 0x1F0;
    drive[2].io_address  = drive[3].io_address  = 0x170;

    drive[0].irq_consumer  = drive[1].irq_consumer  = irq14_consumer;
    drive[2].irq_consumer  = drive[3].irq_consumer  = irq15_consumer;
    
        
    for (WhichDrive = 0; WhichDrive < 4; WhichDrive += 2)
    {
        IOAdr = drive[WhichDrive].io_address;
        /* poke at the interface to see if anything's there */

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"%S: %s: poking interface 0x%03X\n", 
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
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING, 
                L"%S: %s: no master on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);

            continue; 
        }
        
        /* soft reset both drives on this I/F (selects master) */
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"%S: %s: found something on I/F 0x%03X, doing soft reset...\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            IOAdr);

        port_uint8_out (IOAdr + ATA_REG_SLCT, 0x0E);
        
//        timer_sleep_milli (400);
        cpu_sleep_milli (CPU_CURRENT, 400);

        /* release soft reset AND enable interrupts from drive */
        port_uint8_out (IOAdr + ATA_REG_SLCT, 0x08);
        
//        timer_sleep_milli (400);
        cpu_sleep_milli (CPU_CURRENT, 400);
        
        /* wait for master */
        for (timeout = 5000; timeout > 0; timeout--)
        {
            if ((port_uint8_in (IOAdr + ATA_REG_STAT) & 0x80) == 0) 
            {
                break;
            }
//            timer_sleep_milli (1); 
            cpu_sleep_milli (CPU_CURRENT, 400);
        }    /* XXX - blocking delay */
             
        if (timeout == 0)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING, 
                L"%S: %s: no master on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);

            continue; 
        }

        /* identify master */
        ata_select (IOAdr, 0xA0);
    
//        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//            "  hd%1u (0x%03X, master) {%p}: ", 
//            WhichDrive, IOAdr, &drive[WhichDrive]);
            
        if (ata_internal_probe (&drive[WhichDrive]))
        {
            object_reference_t device;
            wchar_t name[STRING_MAX_LENGTH];

            device = ata_drive$object$create (ata_drive_class);
            object_set_data (device, (address_t) &drive[WhichDrive]);
            
            wstring_print (name, L"/devices/hdd/ata%u", WhichDrive);
            namespace$bind (kernel_handle_namespace, name, device);
        }
             
        /* select slave */
        if (!ata_select (IOAdr, 0xB0))
        /* no response from slave: re-select master and continue */
        {
            ata_select (IOAdr, 0xA0);
            
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING, 
                L"%S: %s: no slave on I/F 0x%03X\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                IOAdr);
            continue; 
        }
    
        /* identify slave */
//        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//            "  hd%1u (0x%03X,  slave): ", 
//            WhichDrive + 1, IOAdr);
        
        if (ata_internal_probe (&drive[WhichDrive + 1]))
        {
            object_reference_t device;
            wchar_t name[STRING_MAX_LENGTH];

            device = ata_drive$object$create (ata_drive_class);
            object_set_data (device, (address_t) &drive[WhichDrive + 1]);
            
            wstring_print (name, L"/devices/hdd/ata%u", WhichDrive + 1);
            namespace$bind (kernel_handle_namespace, name, device);
        }
    }
    
    return TRUE;
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
    uint32_t timeout;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, command);

    IOAdr = drive->io_address;

    /* select the drive */
    if (!ata_select (IOAdr, drive->drive_select))
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%s: %s: could not select drive\n",
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
            
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: %s: ready to read %u sector(s) of %u\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                Count, Temp);

            /* compute CHS or LBA register values and write them, along with
               CmdByte */
            ata_internal_command (drive, command, Count, CmdByte);

            /* await read interrupt */
            
//            if (awaitInterrupt (0xC000, WAIT_CMD) == 0)
            quality_set (QUALITY_CURRENT, WAIT_CMD);
            
            EXCEPTION_TRY
            {
                irq$wait (drive->irq_consumer);
                quality_reset (QUALITY_CURRENT);
            }   
            EXCEPTION_CATCH_ALL (e) 
            {
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: read timed out\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);
        
                (void) port_uint8_in (IOAdr + ATA_REG_STAT);
        
                return (-3);
            }
            EXCEPTION_FINALLY
            {
            }
            EXCEPTION_END_TRY;
            
            /* check status */
            Stat = port_uint8_in (IOAdr + ATA_REG_STAT);
        
            if ((Stat & (0x81 | 0x58)) != 0x58)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: bad status (0x%02X) during read\n", 
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
        
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: %s: ready to write %u sector(s) of %u\n", 
                DEBUG_MODULE_NAME, __FUNCTION__,
                Count, Temp);

            /* compute CHS or LBA register values and write them, along with CmdByte */
            ata_internal_command (drive, command, Count, CmdByte);

            /* await DRQ */
            for (timeout = WAIT_DRQ; timeout > 0; timeout--)
            {
                if (port_uint8_in (IOAdr + ATA_REG_ALTST) & 0x08)
                {
                    break;
                }
            
//                timer_sleep_milli (1); 
                cpu_sleep_milli (CPU_CURRENT, 1);
            }    /* XXX - blocking delay */
            
            if (timeout == 0)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: no DRQ during write\n",
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
//            Temp = awaitInterrupt (0xC000, WAIT_CMD);
            quality_set (QUALITY_CURRENT, WAIT_CMD);
            
            EXCEPTION_TRY
            {
                irq$wait (drive->irq_consumer);
                quality_reset (QUALITY_CURRENT);
            }    
            EXCEPTION_CATCH_ALL (e)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: write timed out\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);
                
                (void) port_uint8_in (IOAdr + ATA_REG_STAT);
                
                return(-3); 
            }
            EXCEPTION_FINALLY
            {
            }
            EXCEPTION_END_TRY;
            
            /* check status */
            Stat = port_uint8_in (IOAdr + ATA_REG_STAT);
            if ((Stat & (0xA1 | 0x50)) != 0x50)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: bad status (0x%02X) during write\n", 
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
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: %s: bad cmd (%u)\n", 
            DEBUG_MODULE_NAME, __FUNCTION__,
            command->command);
        
        return (-2);
    }
}



