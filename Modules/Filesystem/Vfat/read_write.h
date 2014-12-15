
extern return_t next_cluster (
  vfat_volume_t *vfat_volume,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  bool extend);

extern return_t offset_to_cluster (
  vfat_volume_t *vfat_volume,
  uint32_t first_cluster, 
  uint32_t file_offset,
  uint32_t *cluster,
  bool extend);

extern return_t vfat_read_big_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length);

extern return_t vfat_read_small_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb UNUSED,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length);

extern return_t vfat_read_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length);

extern return_t vfat_read_file (
  vfat_volume_t *vfat_volume, 
  vfat_file_t *fcb,
  void *buffer, 
  uint32_t length, 
  uint32_t read_offset,
  uint32_t *length_read, 
  uint32_t no_cache);

extern return_t vfat_write_big_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend);

extern return_t vfat_write_small_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend);

extern return_t vfat_write_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend);

extern return_t vfat_write_file (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  void *buffer, 
  uint32_t length, 
  uint32_t write_offset,
  uint32_t no_cache);
