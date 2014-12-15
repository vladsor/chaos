
extern uint32_t vfat_dir_entry_get_first_cluster (
  vfat_volume_t *vfat_volume,
  fat_entry_t *fat_entry);
  
extern bool fat_entry_is_deleted (
  fat_entry_t *fat_entry);

extern bool vfat_is_directory_entry_end_marker (
  fat_entry_t *fat_entry);

extern bool vfat_is_directory_entry_long_name (
  fat_entry_t *fat_entry);

extern bool vfat_is_directory_entry_volume (
  fat_entry_t *fat_entry);

extern void vfat_get_directory_entry_name (
  fat_entry_t *fat_entry,
  char *entry_name);

extern return_t vfat_get_next_directory_entry (
  vfat_volume_t *vfat_volume,
  vfat_file_t *directory_fcb, 
  uint32_t *directory_index,
  uint8_t *long_file_name,
  fat_entry_t *directory_entry);
