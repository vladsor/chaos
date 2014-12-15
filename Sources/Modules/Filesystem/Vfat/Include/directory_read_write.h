
return_t vfat_entry_add (
    p_vfat_file_t directory_file,
    const wchar_t *name, 
    p_vfat_file_t *new_file,
    uint32_t requested_options, 
    uint8_t requested_attributes);

return_t vfat_entry_update (
    vfat_volume_t *vfat_volume, 
    vfat_file_t *pFileObject);

return_t vfat_entry_delete (
    p_vfat_file_t vfat_directory, 
    const wchar_t *name);
    
return_t vfat_entry_find (
    p_vfat_file_t directory_file, 
    const wchar_t *name,
    uint32_t *start_index, 
    uint32_t *end_index);

