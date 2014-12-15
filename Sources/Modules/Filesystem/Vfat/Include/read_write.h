
extern return_t next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    bool extend);

extern return_t offset_to_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster, 
    uint32_t file_offset,
    uint32_t *cluster,
    bool extend);

extern return_t vfat_read_big_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length);

extern return_t vfat_read_small_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length);

extern return_t vfat_read_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length);

extern return_t vfat_read_file (
    p_vfat_file_t file,
    void *buffer, 
    uint32_t length, 
    uint32_t read_offset,
    uint32_t *length_read);

extern return_t vfat_write_big_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend);

extern return_t vfat_write_small_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend);

extern return_t vfat_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend);

extern return_t vfat_write_file (
    p_vfat_file_t file,
    void *buffer, 
    uint32_t length, 
    uint32_t write_offset);
