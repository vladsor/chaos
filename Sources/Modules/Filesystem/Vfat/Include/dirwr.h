return_t add_entry (
    vfat_volume_t *vfat_volume,
    vfat_file_t *pFileObject, 
    uint32_t requested_options, 
    uint8_t requested_attributes);

return_t update_entry (
    vfat_volume_t *vfat_volume, 
    vfat_file_t *pFileObject);

return_t delete_entry (
    vfat_volume_t *vfat_volume, 
    vfat_file_t *pFileObject);
    
    

