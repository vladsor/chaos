return_t get_entry_name (
  vfat_volume_t *vfat_volume,
  void *block,
  file_handle_t file_handle,
  uint8_t *name,
  uint32_t *index,
  uint32_t *index2);

return_t read_volume_label (
    vfat_volume_t *vfat_volume);
    
return_t find_file (
    vfat_volume_t *vfat_volume,
    vfat_file_t *fcb,
    vfat_file_t *parent,
    char *file_to_find,
    uint32_t *pDirIndex,
    uint32_t *pDirIndex2);

