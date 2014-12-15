#include <enviroment.h>

#include "Include/ata.h"
#include "Include/interface.h"

#include <Classes/kernel.h>

#include <Classes/ata_drive.h>

#define DEBUG_MODULE_NAME "ATA"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

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
int atapi_command (p_drive_t drive, p_drive_command_t command)
{
    uint8_t packet[12];
    uint32_t count;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, command);

    /* convert general block device command code into ATAPI packet commands */
    if (command->command == DRIVE_COMMAND_READ)
    {
        packet[0] = ATAPI_COMMAND_READ10;
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: bad cmd: %u\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            command->command);
        
        return (-2);
    }

    packet[1] = 0;
    packet[2] = command->bulk >> 24;
    packet[3] = command->bulk >> 16;
    packet[4] = command->bulk >> 8;
    packet[5] = command->bulk;
    
    count = command->count >> ATAPI_LG_SECTSIZE;
    packet[6] = count >> 16;
    packet[7] = count >> 8;
    packet[8] = count;
    packet[9] = packet[10] = packet[11] = 0;
    
    return (atapi_internal_command (drive, command, packet)); 
}

/*****************************************************************************
        name:   atapiEject
        action: loads (Load == TRUE) or ejects (Load == FALSE) CD-ROM
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_eject (p_drive_t drive, bool load)
{
    uint8_t packet[12] = {
        ATAPI_COMMAND_START_STOP,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };
        
    drive_command_t command;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, load);
    
    command.bulk = 0;
    command.count = 0;
    command.command = 0;
    command.data = NULL;

    packet[4] = 2 + (!load ? 1 : 0);
    
    return (atapi_internal_command (drive, &command, packet)); 
}

/*****************************************************************************
        name:   atapiPlay
        action: plays audio from time index Start to End (units of 1/75 sec)
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_play (p_drive_t drive, uint32_t start, uint32_t end)
{
    uint8_t packet[12] = {
        ATAPI_COMMAND_PLAY,
        0, 0,
        0, 0, 0,        /* starting minute:second:frame */
        0, 0, 0,        /* ending M:S:F (frame=1/75 sec) */
        0, 0, 0 };
        
    drive_command_t command;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, start, end);
    
    command.bulk = 0;
    command.count = 0;
    command.command = 0;
    command.data = NULL;

    packet[5] = start % 75;
    start /= 75;
    packet[4] = start % 60;
    start /= 60;
    packet[3] = start;

    packet[8] = end % 75;
    end /= 75;
    packet[7] = end % 60;
    end /= 60;
    packet[6] = end;

    return (atapi_internal_command (drive, &command, packet));
}

/*****************************************************************************
        name:   atapiTOCEnt
        action: reads one or more table-of-contents entries from audio CD
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_toc_read (p_drive_t drive, p_atapi_toc_t contents, unsigned count)
{
    uint8_t packet[12]= {
        ATAPI_COMMAND_READ_TOC,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };
        
    drive_command_t command;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, contents, count);
    
    command.bulk = 0;
    command.count = count;
    command.command = 0;
    command.data = (uint8_t *) contents;

    packet[1] = 2;
    packet[6] = 0;
    packet[7] = count >> 8;
    packet[8] = count;
    packet[9] = 0;
    
    return (atapi_internal_command (drive, &command, packet)); 
}

/*****************************************************************************
        name:   atapiPause
        action: pauses (Play == 0) or continues (Play != 0) audio CD
        returns:whatever atapiCmd2() returns
*****************************************************************************/
int atapi_pause (p_drive_t drive, bool play)
{
    uint8_t packet[12]={
        ATAPI_COMMAND_PAUSE,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0 };

    drive_command_t command;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        drive, play);
    
    command.bulk = 0;
    command.count = 0;
    command.command = 0;
    command.data = NULL;

    packet[8] = play ? 1 : 0;
    
    return (atapi_internal_command (drive, &command, packet)); 
}

