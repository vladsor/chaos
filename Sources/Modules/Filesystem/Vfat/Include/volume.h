
extern return_t vfat_has_file_system (
    handle_reference_t device,
    bool *has_fat);

extern return_t vfat_volume_create_data (
    p_vfat_volume_t vfat_volume,
    handle_reference_t device_to_mount);
  
extern void vfat_volume_add_file_data (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t file);

extern p_vfat_file_t vfat_volume_get_file_data (
    p_vfat_volume_t vfat_volume,
    const wchar_t *file_name);

extern void vfat_volume_remove_file_data (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t file);
