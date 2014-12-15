
extern return_t vfat_read_sectors (
  device_t *device, 
  uint32_t start_sector, 
  uint32_t number_of_sectors,
  void *buffer);

extern return_t vfat_write_sectors (
  device_t *device,
  uint32_t start_sector,
  uint32_t number_of_sectors,
  void *data_buffer);
  