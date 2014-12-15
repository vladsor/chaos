
extern return_t vfat_has_file_system (
  device_t *device,
  bool *has_fat);
  
extern return_t vfat_mount_device (
  device_t *device_to_mount,
  vfat_volume_t *vfat_volume);
  