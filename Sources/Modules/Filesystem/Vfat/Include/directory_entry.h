
#define ENTRIES_PER_SECTOR (BLOCK_SIZE / sizeof (fat_entry_t))

#define FAT_ENTRY_DELETED(entry)	\
    ((entry)->file_name[0] == 0xe5)
    
#define FAT_ENTRY_END(entry)	\
    ((entry)->file_name[0] == 0)
    
#define FAT_ENTRY_LONG(entry)	\
    (((entry)->attribute & 0x3f) == 0x0f)
    
#define FAT_ENTRY_VOLUME(entry)	\
    (((entry)->attribute & 0x1f) == 0x08)


extern uint32_t vfat_directory_entry_get_first_cluster (
    p_vfat_volume_t vfat_volume,
    p_fat_entry_t fat_entry);
  
extern bool vfat_directory_entry_is_deleted (
    p_fat_entry_t fat_entry);

extern bool vfat_directory_entry_is_end_marker (
    p_fat_entry_t fat_entry);

extern bool vfat_directory_entry_is_long_name (
    p_fat_entry_t fat_entry);

extern bool vfat_directory_entry_is_volume (
    p_fat_entry_t fat_entry);

extern void vfat_directory_entry_get_name (
    p_fat_entry_t fat_entry,
    wchar_t *entry_name);

extern return_t vfat_directory_entry_get_next (
    p_vfat_file_t directory_file,
    uint32_t *directory_index,
    wchar_t *long_file_name,
    p_fat_entry_t directory_entry);
