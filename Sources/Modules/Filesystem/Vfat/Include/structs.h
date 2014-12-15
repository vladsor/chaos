
#include <unicode.h>

/* Much of this information can be found in the "FAT: General Overview
   of On-Disk Format" Hardware White Paper published by Microsoft. */

typedef struct
{
  /* jmp_boot has two valid ways to look like in a FAT BPB. Either
     0xEB, 0x??, 0x90 or 0xE9, 0x??, 0x??. */

  uint8_t jmp_boot[3];

  /* Creator system of the fat-drive. Usually looks like
     "MSWIN4.x". We write "chaos" here. */

  uint8_t oem_name[8];

  /* Can be 512, 1024, 2048 or 4096. Should be 512 if you don't want
     any trouble. At least, that's what Microsoft says. */

  uint16_t bytes_per_sector;
 
  /* Must be a power of two. The result of bytes_per_sector *
     sectors_per_cluster may not greater than 32K. If it is, many
     aplications will stop working. ;-) */

  uint8_t sectors_per_cluster;

  /* Number of reserved sectors in the reserved region of the volume
     starting at the first sector of the volume. Must be 1 for
     FAT12/16. Usually 32 for FAT32. */

  uint16_t reserved_sectors;

  /* Number of FAT structures. This value should always be 2. */

  uint8_t number_of_fats;

  /* For FAT12 and FAT16, this field contains the number of 32-byte
     directory entries in the root directory. It must also result in
     an even multiple of bytes_per_sector when multiplied by 32. For
     FAT32, this field must be set to zero. */

  uint16_t number_of_root_entries;

  /* This is the total number of sectors on the volume. If zero, the
     real value can be found in total_sectors_32. */
  
  uint16_t total_sectors_16;

  /* 0xF8 is the standard value for fixed media. For removable media,
     0xF0 is normally used. Legal values are 0xF0 and
     0xF8-0xFF. Whatever is put here must also be put into the low
     byte of the FAT[0] entry. Other than that, it's only here for
     compataibility. (It was used in DOS 1.x) */

  uint8_t media;

  /* The size of one FAT in 16-bit mode. In FAT32 this must be
     zero. */

  uint16_t fat_size_16;

  /* Sectors per track used on this media. This field isn't used by
     chaos. */

  uint16_t sectors_per_track;

  /* Number of heads used on this media. This field isn't used by
     chaos. */

  uint16_t number_of_heads;

  /* Number of hidden sectors. This field isn't used by chaos. */

  uint32_t hidden_sectors;

  /* Number of total sectors. If zero, the value in total_sectors_16
     is used. For FAT32 volumes, this must be specified. */

  uint32_t total_sectors_32;

  /* Drive number for BIOS. Isn't used by chaos. */

  uint8_t drive_number;

  /* Reserved for Windows NT. Should always be set to 0. */

  uint8_t reserved;

  /* Extended boot signature. If this is 0x29, the following three
     fields are present. */

  uint8_t boot_signature;

  /* Volume serial number. Should be fairly randomized. */

  uint32_t volume_id;

  /* Volume label. This field must be updated when the volume label in
     the root direcotry is updated. */

  uint8_t volume_label[11];

  /* One of the strings "FAT12 ", "FAT16 " or "FAT ". This can not be
     used to detemine the type of the FAT, but it should be updated
     when creating file systems. */

  uint8_t filesystem_type[8];
  
  uint8_t reserved2[450];
} PACKED boot_sector_t;

//PACKED;
/*
#define BOOT_SIZE sizeof (boot_sector_t)
#if (BOOT_SIZE) != 512
#error "Invalid boot sector size."
#endif
*/
/* FAT32 specific data. */

typedef struct
{
  /* jmp_boot has two valid ways to look like in a FAT BPB. Either
     0xEB, 0x??, 0x90 or 0xE9, 0x??, 0x??. */

  uint8_t jmp_boot[3];

  /* Creator system of the fat-drive. Usually looks like
     "MSWIN4.x". We write "chaos" here. */

  uint8_t oem_name[8];

  /* Can be 512, 1024, 2048 or 4096. Should be 512 if you don't want
     any trouble. At least, that's what Microsoft says. */

  uint16_t bytes_per_sector;
 
  /* Must be a power of two. The result of bytes_per_sector *
     sectors_per_cluster may not greater than 32K. If it is, many
     aplications will stop working. ;-) */

  uint8_t sectors_per_cluster;

  /* Number of reserved sectors in the reserved region of the volume
     starting at the first sector of the volume. Must be 1 for
     FAT12/16. Usually 32 for FAT32. */

  uint16_t reserved_sectors;

  /* Number of FAT structures. This value should always be 2. */

  uint8_t number_of_fats;

  /* For FAT12 and FAT16, this field contains the number of 32-byte
     directory entries in the root directory. It must also result in
     an even multiple of bytes_per_sector when multiplied by 32. For
     FAT32, this field must be set to zero. */

  uint16_t number_of_root_entries;

  /* This is the total number of sectors on the volume. If zero, the
     real value can be found in total_sectors_32. */
  
  uint16_t total_sectors_16;

  /* 0xF8 is the standard value for fixed media. For removable media,
     0xF0 is normally used. Legal values are 0xF0 and
     0xF8-0xFF. Whatever is put here must also be put into the low
     byte of the FAT[0] entry. Other than that, it's only here for
     compataibility. (It was used in DOS 1.x) */

  uint8_t media;

  /* The size of one FAT in 16-bit mode. In FAT32 this must be
     zero. */

  uint16_t fat_size_16;

  /* Sectors per track used on this media. This field isn't used by
     chaos. */

  uint16_t sectors_per_track;

  /* Number of heads used on this media. This field isn't used by
     chaos. */

  uint16_t number_of_heads;

  /* Number of hidden sectors. This field isn't used by chaos. */

  uint32_t hidden_sectors;

  /* Number of total sectors. If zero, the value in total_sectors_16
     is used. For FAT32 volumes, this must be specified. */

  uint32_t total_sectors_32;

  /* This is the number of sectors for one FAT. */

  uint32_t fat_size_32;

  /* Extended FAT32 flags follow. */
  
  uint16_t : 8;
  
  /* If this bit is clear, the FAT is mirrored at runtime into all
     FATs. If it set, only the one specified in the following field is
     active. */

  uint16_t mirroring : 1; 

  uint16_t : 3;

  /* This specifies the "active" FAT mentioned previously. */

  uint16_t active_fat : 4;
  
  /* This specifies the file system version. High byte is major
     number, low byte is minor. The current version is 0.0. */

  uint16_t filesystem_version;
  
  /* This is set to the cluster number of the first cluster of the
     root directory. Usually 2, but not required. */

  uint32_t root_cluster;

  /* This specifies the sector number of the 'FSINFO' structure in the
     reserved area. */

  uint16_t filesystem_info;

  /* If zero, this specifies where the backup of the boot record can be
     found. Usually 6. No value other than 6 is recommended by
     Microsoft. */

  uint32_t backup_boot_record;

  /* The following area should always be set to zero when the volume
     is initialised. */

  uint8_t reserved3[10];

  /* Drive number for BIOS. Isn't used by chaos. */

  uint8_t drive_number;

  /* Reserved for Windows NT. Should always be set to 0. */

  uint8_t reserved4;

  /* Extended boot signature. If this is 0x29, the following three
     fields are present. */

  uint8_t boot_signature;

  /* Volume serial number. Should be fairly randomized. */

  uint32_t volume_id;

  /* Volume label. This field must be updated when the volume label in
     the root direcotry is updated. */

  uint8_t volume_label[11];

  /* One of the strings "FAT12 ", "FAT16 " or "FAT ". This can not be
     used to determine the type of the FAT, but it should be updated
     when creating file systems. */

  uint8_t filesystem_type[8];
  
  uint8_t reserved5[418];
  uint32_t signature1;
} PACKED boot_sector_32_t;
/*
#if sizeof (boot_sector_32_t) != 512
#error "Invalid boot sector 32 size."
#endif
*/
/* A FAT directory entry. */

typedef struct
{
  /* The file name. If name[0] == 0xE5, this entry is free. If name[0]
     == 0x00, the rest of this directory is free. If name[0] == 0x05,
     the real value for this byte is 0xE5. This is because 0xE5 is
     used in the KANJI character set... */
  
  uint8_t file_name[8];
  uint8_t extension[3];
  
  /* File attributes. */
/*
  u8 read_only : 1;
  u8 hidden : 1;
  u8 system : 1;
  u8 volume_id : 1;
  u8 directory : 1;
  u8 archive : 1;
  u8 reserved : 2;
*/
  uint8_t attribute;
    
  /* Reserved for Windows NT. Set to zero when creating, and never
     rely upon. */

  uint8_t nt_reserved;
  
  /* Time stamp the file was created. */

  uint8_t creation_hundreds;

  fat_time_t creation_time;
  fat_date_t creation_date;

  /* Last access date. Updated when the file is read from or written
     to. */

  fat_date_t access_date;

  /* High word of this entry's first cluster number. This should be
     zero for FAT12 or FAT16. */
  
  uint16_t first_cluster_number_high;

  /* Time for last update. */

  fat_time_t update_time;
  fat_date_t update_date;

  /* Low word of this entry's first cluster number. */

  uint16_t first_cluster_number_low;

  /* File size in bytes. */

  uint32_t file_size;

} PACKED fat_entry_t;

typedef struct
{
  /* sequence number for slot */
  uint8_t id;

  /* first 5 characters in name */
  ucs2_t name0_4[5];
  
  /* attribute byte */
  uint8_t attribute;

  /* always 0 */
  uint8_t reserved;

  /* checksum for 8.3 alias */
  uint8_t alias_checksum;

  /* 6 more characters in name */
  ucs2_t name5_10[6];

  /* starting cluster number */
  uint16_t first_cluster_number;

  /* last 2 characters in name */
  ucs2_t name11_12[2];
  
} PACKED lfn_fat_entry_t;

typedef struct
{
  uint32_t extended_boot_signature2;                 /* 0   */
  uint8_t  reserved6[480];                           /* 4   */
  uint32_t file_system_info_signature;               /* 484 */
  uint32_t free_cluster;                             /* 488 */
  uint32_t next_cluster;                             /* 492 */
  uint8_t  reserved7[12];                            /* 496 */
  uint32_t signature2;                               /* 508 */
} PACKED boot_backup_sector_t;

#define BLOCK_SIZE 512
#define ENTRIES_PER_SECTOR (BLOCK_SIZE / sizeof (fat_entry_t))

#define FAT_ENTRY_DELETED(entry)	\
    ((entry)->file_name[0] == 0xe5)
    
#define FAT_ENTRY_END(entry)	\
    ((entry)->file_name[0] == 0)
    
#define FAT_ENTRY_LONG(entry)	\
    (((entry)->attribute & 0x3f) == 0x0f)
    
#define FAT_ENTRY_VOLUME(entry)	\
    (((entry)->attribute & 0x1f) == 0x08)

