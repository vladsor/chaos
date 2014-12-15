/**
 * @brief A FAT directory entry. 
 */
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

} fat_entry_t PACKED;

typedef fat_entry_t * p_fat_entry_t;

typedef struct
{
    /* sequence number for slot */
    uint8_t id;

    /* first 5 characters in name */
    ucs2_t name0_4[5];
  
    /* attribute byte */
    uint8_t attribute;

    /* always 0 */
    uint8_t reserved;

    /* checksum for 8.3 alias */
    uint8_t alias_checksum;

    /* 6 more characters in name */
    ucs2_t name5_10[6];

    /* starting cluster number */
    uint16_t first_cluster_number;

    /* last 2 characters in name */
    ucs2_t name11_12[2];
  
} lfn_fat_entry_t PACKED;

typedef lfn_fat_entry_t * p_lfn_fat_entry_t;

