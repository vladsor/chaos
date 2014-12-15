extern uint32_t cluster_to_sector (
  vfat_volume_t *vfat_volume,
  uint32_t cluster);
  
extern void vfat_8_dot_3_to_string (
  uint8_t *base_name,
  uint8_t *extension,
  uint8_t *name);
  
