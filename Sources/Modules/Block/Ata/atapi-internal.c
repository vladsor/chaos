#include <enviroment.h>

#include "Include/ata.h"
#include "Include/interface.h"

#include <Classes/kernel.h>

#define DEBUG_MODULE_NAME L"ATA"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (ata_debug_supplier)
#endif

#include <debug/macros.h>
#include <exception/macros.h>

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

int atapi_internal_command (p_drive_t drive, p_drive_command_t command, 
    uint8_t *packet)
{
    uint16_t IOAdr, Got;
    uint8_t  phase = ATAPI_PHASE_ABORT;
    uint32_t Temp;
    uint32_t timeout;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s (%p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, command, packet);

    IOAdr = drive->io_address;

    if (!ata_select (IOAdr, drive->drive_select))
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: %s: could not select drive.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return (-1); 
    }
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        "%S: %s: writing register file.\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
    
    port_uint8_out (IOAdr + ATA_REG_FEAT, 0);  /* irrelevant? */
    port_uint8_out (IOAdr + ATA_REG_REASON, 0);/* irrelevant? */
    port_uint8_out (IOAdr + ATA_REG_SECT, 0);  /* irrelevant? */
    port_uint8_out (IOAdr + ATA_REG_LOCNT, (uint8_t) 32768ul);
    port_uint8_out (IOAdr + ATA_REG_HICNT, 32768ul >> 8);
    port_uint8_out (IOAdr + ATA_REG_CMD, ATA_CMD_PKT);

//    timer_sleep_milli (400);
    cpu_sleep_milli (CPU_CURRENT, 400);
    
    for (timeout = 500; timeout > 0; timeout--)     /* XXX - why 500? */
    {
        if ((port_uint8_in (IOAdr + ATA_REG_STAT) & 0x88) == 0x08)
        {
            break;
        }
        
//        timer_sleep_milli (1); 
        cpu_sleep_milli (CPU_CURRENT, 1);
    }    /* this _must_ be polled, I guess */
    
    if (timeout == 0)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: %s: drive did not accept pkt cmd byte\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return (-3);
    }
    
    port_uint16_out_string (IOAdr + ATA_REG_DATA, (uint16_t *) packet, 6);
    
    while (1)
    {

//        if (awaitInterrupt (0xC000, WAIT_CMD) == 0)
        quality_set (QUALITY_CURRENT, WAIT_CMD);
            
        EXCEPTION_TRY
        {
            irq$wait (drive->irq_consumer);
            quality_reset (QUALITY_CURRENT);
        }   
        EXCEPTION_CATCH_ALL (e) 
        {
            (void) port_uint8_in (IOAdr + ATA_REG_STAT);
            
            DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                L"%S: %s: Packet command timed out.\n",
                DEBUG_MODULE_NAME, __FUNCTION__);
            
            return (-4);
        }
        EXCEPTION_FINALLY
        {
        }
        EXCEPTION_END_TRY;
        
        phase = port_uint8_in (IOAdr + ATA_REG_STAT) & 0x08;
        phase |= (port_uint8_in (IOAdr + ATA_REG_REASON) & 3);

        if (phase == ATAPI_PHASE_DONE)
        {
            if (command->count != 0)
            {
                /* could mean no CD or audio CD */
                DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                    L"%S: %s: data shortage\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);

                return (-5); 
            }
            
            return (0);
        }
        else if (phase == ATAPI_PHASE_ABORT)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING, 
                L"%S: %s: cmd aborted\n",
                DEBUG_MODULE_NAME, __FUNCTION__);
            
            return (-6);
        }
        else if (phase != ATAPI_PHASE_DATAIN)
        /* ATAPI_PH_DATAOUT or ATAPI_PH_CMDOUT or something completely bogus */
        {
            DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                L"%S: %s: bad phase %u\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                phase);
            
            return (-7);
        }
        
        Got = port_uint8_in (IOAdr + ATA_REG_HICNT);
        Got = (Got << 8) | port_uint8_in (IOAdr + ATA_REG_LOCNT);
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, L"<%5u bytes>   ", Got);
        
        /* Cmd->Count=how many bytes we want to transfer
           Got=how many bytes are available for transfer
           Temp=smaller of these two */
        Temp = MIN (command->count, Got);

        /* read data. XXX - what if Temp odd?
           XXX - allow read from middle of one sector to middle of another? */
        port_uint16_in_string (IOAdr + ATA_REG_DATA, 
            (uint16_t *) command->data, Temp >> 1);
        
        /* read and discard surplus data */
        for (Got -= Temp; Got > 1; Got -= 2)
        { 
            port_uint16_in (IOAdr + ATA_REG_DATA);
        }
        
        if (Got)
        {
            port_uint8_in (IOAdr + ATA_REG_DATA);
        }
        
        /* advance pointers */
        command->data += Temp;
        command->count -= Temp;
        Temp >>= ATAPI_LG_SECTSIZE;
        command->bulk += Temp; 
    }
}

