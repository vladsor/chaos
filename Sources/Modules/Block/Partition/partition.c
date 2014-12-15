#include <enviroment.h>

#include <Interfaces/block.h>

#include "Include/interface.h"
#include "Include/partition.h"

#define DEBUG_MODULE_NAME L"Partition"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (partition_debug_supplier)
#endif

#include <debug/macros.h>

#define _STATIC

partition_record_t partition_record[] = 
{
  { 0x00, PARTITION_TYPE_NORMAL,
    "Empty" },

  { 0x01, PARTITION_TYPE_NORMAL,
    "DOS 12-bit FAT" },

  { 0x02, PARTITION_TYPE_NORMAL,
    "XENIX /" },

  { 0x03, PARTITION_TYPE_NORMAL,
    "XENIX /usr" },

  { 0x04, PARTITION_TYPE_NORMAL,
    "DOS 16-bit FAT <32M" },

  { 0x05, PARTITION_TYPE_EXTENDED,
    "DOS Extended" },

  { 0x06, PARTITION_TYPE_NORMAL,
    "DOS 16-bit FAT >=32M" },

  { 0x07, PARTITION_TYPE_NORMAL,
    "HPFS / NTFS" },

  { 0x08, PARTITION_TYPE_NORMAL,
    "AIX boot or SplitDrive" },

  { 0x09, PARTITION_TYPE_NORMAL,
    "AIX data or Coherent" },
  { 0x0A, PARTITION_TYPE_NORMAL,
    "OS/2 Boot Manager" },

  { 0x0B, PARTITION_TYPE_NORMAL,
    "Windows95 FAT32" },
    
  { 0x0C, PARTITION_TYPE_NORMAL,
    "Windows95 FAT32 (LBA)" },
    
  { 0x0E, PARTITION_TYPE_NORMAL,
    "Windows95 FAT16 (LBA)" },
    
  { 0x0F, PARTITION_TYPE_EXTENDED,
    "Windows95 Extended (LBA)" },
    
  { 0x10, PARTITION_TYPE_NORMAL,
    "OPUS" },
    
  { 0x11, PARTITION_TYPE_NORMAL,
    "Hidden DOS FAT12" },
    
  { 0x12, PARTITION_TYPE_NORMAL,
    "Compaq diagnostics" },
    
  { 0x14, PARTITION_TYPE_NORMAL,
    "Hidden DOS FAT16" },
    
  { 0x16, PARTITION_TYPE_NORMAL,
    "Hidden DOS FAT16 (big)" },
    
  { 0x17, PARTITION_TYPE_NORMAL,
    "Hidden HPFS/NTFS" },
    
  { 0x18, PARTITION_TYPE_NORMAL,
    "AST Windows swapfile" },
    
  { 0x24, PARTITION_TYPE_NORMAL,
    "NEC DOS" },
    
  { 0x3C, PARTITION_TYPE_NORMAL,
    "PartitionMagic recovery" },
    
  { 0x40, PARTITION_TYPE_NORMAL,
    "Venix 80286" },
    
  { 0x41, PARTITION_TYPE_NORMAL,
    "Linux/MINIX (sharing disk with DRDOS)" },
    
  { 0x42, PARTITION_TYPE_NORMAL,
    "SFS or Linux swap (sharing disk with DRDOS)" },
    
  { 0x43, PARTITION_TYPE_NORMAL,
    "Linux native (sharing disk with DRDOS)" },
    
  { 0x50, PARTITION_TYPE_NORMAL,
    "DM (disk manager)" },
    
  { 0x51, PARTITION_TYPE_NORMAL,
    "DM6 Aux1 (or Novell)" },
    
  { 0x52, PARTITION_TYPE_NORMAL,
    "CP/M or Microsoft SysV/AT" },
    
  { 0x53, PARTITION_TYPE_NORMAL,
    "DM6 Aux3" },
    
  { 0x54, PARTITION_TYPE_NORMAL,
    "DM6" },
    
  { 0x55, PARTITION_TYPE_NORMAL,
    "EZ-Drive (disk manager)" },
    
  { 0x56, PARTITION_TYPE_NORMAL,
    "Golden Bow (disk manager)" },
    
  { 0x5C, PARTITION_TYPE_NORMAL,
    "Priam Edisk (disk manager)" },
    
  { 0x61, PARTITION_TYPE_NORMAL,
    "SpeedStor" },
    
  { 0x63, PARTITION_TYPE_NORMAL,
    "GNU Hurd or Mach or Sys V/386 (such as ISC UNIX)" },
    
  { 0x64, PARTITION_TYPE_NORMAL,
    "Novell Netware 286" },
    
  { 0x65, PARTITION_TYPE_NORMAL,
    "Novell Netware 386" },
    
  { 0x70, PARTITION_TYPE_NORMAL,
    "DiskSecure Multi-Boot" },
    
  { 0x75, PARTITION_TYPE_NORMAL,
    "PC/IX" },
    
  { 0x77, PARTITION_TYPE_NORMAL,
    "QNX4.x" },
    
  { 0x78, PARTITION_TYPE_NORMAL,
    "QNX4.x 2nd part" },
    
  { 0x79, PARTITION_TYPE_NORMAL,
    "QNX4.x 3rd part" },
    
  { 0x80, PARTITION_TYPE_NORMAL,
    "MINIX until 1.4a" },
    
  { 0x81, PARTITION_TYPE_NORMAL,
    "MINIX / old Linux" },
    
  { 0x82, PARTITION_TYPE_NORMAL,
    "Linux swap" },
     
  { 0x83, PARTITION_TYPE_NORMAL,
    "Linux native" },
    
  { 0x84, PARTITION_TYPE_NORMAL,
    "OS/2 hidden C: drive" },
    
  { 0x85, PARTITION_TYPE_EXTENDED,
    "Linux extended" },
    
  { 0x86, PARTITION_TYPE_NORMAL,
    "NTFS volume set" },
    
  { 0x87, PARTITION_TYPE_NORMAL,
    "NTFS volume set" },
    
  { 0x93, PARTITION_TYPE_NORMAL,
    "Amoeba" },
    
  { 0x94, PARTITION_TYPE_NORMAL,
    "Amoeba BBT" },
    
  { 0xA0, PARTITION_TYPE_NORMAL,
    "IBM Thinkpad hibernation" },
    
  { 0xA5, PARTITION_TYPE_NORMAL,
    "BSD/386" },
    
  { 0xA7, PARTITION_TYPE_NORMAL,
    "NeXTSTEP 486" },
    
  { 0xB7, PARTITION_TYPE_NORMAL,
    "BSDI fs" },
    
  { 0xB8, PARTITION_TYPE_NORMAL,
    "BSDI swap" },
    
  { 0xC1, PARTITION_TYPE_NORMAL,
    "DRDOS/sec (FAT-12)" },
    
  { 0xC4, PARTITION_TYPE_NORMAL,
    "DRDOS/sec (FAT-16, < 32M)" },
    
  { 0xC6, PARTITION_TYPE_NORMAL,
    "DRDOS/sec (FAT-16, >= 32M)" },
    
  { 0xC7, PARTITION_TYPE_NORMAL,
    "Syrinx" },
    
  { 0xDB, PARTITION_TYPE_NORMAL,
    "CP/M or Concurrent CP/M or Concurrent DOS or CTOS" },
    
  { 0xE1, PARTITION_TYPE_NORMAL,
    "DOS access or SpeedStor 12-bit FAT extended partition" },
    
  { 0xE3, PARTITION_TYPE_NORMAL,
    "DOS R/O or SpeedStor" },
    
  { 0xE4, PARTITION_TYPE_NORMAL,
    "SpeedStor 16-bit FAT extended partition < 1024 cyl." },
    
  { 0xF1, PARTITION_TYPE_NORMAL,
    "SpeedStor" },
    
  { 0xF2, PARTITION_TYPE_NORMAL,
    "DOS 3.3+ secondary" },
    
  { 0xF4, PARTITION_TYPE_NORMAL,
    "SpeedStor large partition" },
    
  { 0xFE, PARTITION_TYPE_NORMAL,
    "SpeedStor >1024 cyl. or LANstep" },
    
  { 0xFF, PARTITION_TYPE_NORMAL, 
    "Xenix Bad Block Table" },
};

#define number_of_partition_records (sizeof (partition_record) / \
                                     sizeof (partition_record_t))

static const char * search_partition_name (uint8_t type)
{
    uint8_t i;

    for (i = 0 ; i < number_of_partition_records ; i++)
    {
        if (type == partition_record[i].type)
        {
            return partition_record[i].name;
        }
    }
  
    return "Unknown paritition";
}

static uint8_t search_partition_type (uint8_t type)
{
    uint8_t i;

    for (i = 0 ; i < number_of_partition_records ; i++)
    {
        if (type == partition_record[i].type)
        {
            return partition_record[i].partition_type;
        }
    }
  
    return PARTITION_TYPE_NORMAL;
}

static return_t check_extended (
    handle_reference_t generic, 
    wchar_t *name,
    unsigned int number_of_partition,
    uint32_t start_sector,
    uint32_t offset)
{
    uint8_t *sector_buffer;
    partition_entry_t *partition;
    int index;
    uint8_t partition_type;
    sequence_t data;

#ifndef _STATIC
    memory_allocate ((void **) &sector_buffer, 512);
    
    if (sector_buffer == NULL)
    {
        return FALSE;
    }
#else
    uint8_t blocks[512];
    sector_buffer = blocks;
#endif

    /* Now, read the sector of the disk containing the partition table. */

    data.data = sector_buffer;
    data.count = 512;
    
    if (block$read (generic, data, start_sector + offset) != 512)
    {
        return FALSE;
    }    

    if ((sector_buffer[511] != 0xAA) || (sector_buffer[510] != 0x55))
    {
        return FALSE;
    }

    /* Parse the partition table. */

    partition = (partition_entry_t *) &sector_buffer[446];

    for (index = 0; index < 4 ; index++)
    {
        /* Partition table ends. */

        if (partition[index].type == 0)
        {
            break;
        }

        partition_type = search_partition_type (partition[index].type);

        if (partition_type == PARTITION_TYPE_NORMAL)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                L"%S:  LP: %s(Type 0x%02X), [%u, %uMB]\n",
                DEBUG_MODULE_NAME,
                search_partition_name (partition[index].type),
                partition[index].type,
                partition[index].lba_starting_sector_number,
                (uint32_t) (((uint64_t) partition[index].lba_number_of_sectors)
                    * 512L / MIB));

            /* Create a block object of this partition. */

            partition_block_create (generic, name, number_of_partition,
                start_sector + offset + 
                    partition[index].lba_starting_sector_number,
                partition[index].lba_number_of_sectors);
        }
        else if (partition_type == PARTITION_TYPE_EXTENDED)
        {
            /* Extended partition. */

            if (!check_extended (generic, name, number_of_partition + 1, 
                start_sector, 
                partition[index].lba_starting_sector_number))
            {
                return FALSE;
            }
        }
    }

#ifndef _STATIC
    memory_deallocate ((void **) &sector_buffer);
#endif  
  
    return STORM_RETURN_SUCCESS;
}


return_t scan_for_partitions (handle_reference_t generic, wchar_t *name)
{
    uint8_t *sector_buffer;
    partition_entry_t *partition;
    int index;
    uint8_t partition_type;
    sequence_t data;

#ifndef _STATIC
    memory_allocate ((void **) &sector_buffer, 512);
    
    if (sector_buffer == NULL)
    {
        return FALSE;
    }
#else
    static uint8_t blocks[512];
    sector_buffer = blocks;
#endif

    /* Now, read the sector of the disk containing the partition table. */

    data.data = sector_buffer;
    data.count = 512;
    
    if (block$read (generic, data, 0) != 512)
    {
        return FALSE;
    }    

    if ((sector_buffer[511] != 0xAA) || (sector_buffer[510] != 0x55))
    {
        return FALSE;
    }

    /* Parse the partition table. */

    partition = (partition_entry_t *) &sector_buffer[446];

    for (index = 0; index < 4 ; index++)
    {
        /* Partition table ends. */
   
        if (partition[index].type == 0)
        {
            break;
        }

        partition_type = search_partition_type (partition[index].type);

        if (partition_type == PARTITION_TYPE_NORMAL)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                L"%S: PP: %s(Type 0x%02X), [%u, %uMB]%s\n",
                DEBUG_MODULE_NAME,
                search_partition_name (partition[index].type),
                partition[index].type,
                partition[index].lba_starting_sector_number,
                (uint32_t) (((uint64_t) partition[index].lba_number_of_sectors)
                    * 512L / MIB),
                (partition[index].active == 1) ? "(Active)" : "");

            /* Create a block object for this partition. */
      
            partition_block_create (generic, name, 0,
                partition[index].lba_starting_sector_number,
                partition[index].lba_number_of_sectors);
        }
        else if (partition_type == PARTITION_TYPE_EXTENDED)
        {
            /* Extended partition. */

            if (check_extended (generic, name, 1, 
                partition[index].lba_starting_sector_number, 0) 
                    != STORM_RETURN_SUCCESS)
            {
                return FALSE;
            }
        }
    }

#ifndef _STATIC
    memory_deallocate ((void **) &sector_buffer);
#endif  
  
    return TRUE;
}

