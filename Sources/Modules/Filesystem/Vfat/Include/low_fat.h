
extern return_t vfat_raw_read_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    void *buffer,
    uint32_t cluster);

extern return_t vfat_raw_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    void *buffer,
    uint32_t cluster);

extern return_t get_next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t current_cluster,
    uint32_t *next_cluster,
    bool extend);

extern return_t get_next_sector (
    p_vfat_volume_t vfat_volume,
    uint32_t current_sector,
    uint32_t *next_sector,
    bool extend);


extern return_t fat12_get_next_cluster (
    p_vfat_volume_t vfat_volume, 
    uint32_t current_cluster,
    uint32_t *next_cluster);
  
extern return_t fat12_find_available_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster);

extern return_t fat12_count_available_clusters (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters);
  
extern return_t fat12_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster_to_write,
    uint32_t new_value);


extern return_t fat16_get_next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t current_cluster,
    uint32_t *next_cluster);

extern return_t fat16_find_available_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster);

extern return_t fat16_count_available_clusters (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters);

extern return_t fat16_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster_to_write,
    uint32_t new_value);


extern return_t fat32_get_next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t current_cluster,
    uint32_t *next_cluster);

extern return_t fat32_find_available_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster);

extern return_t fat32_count_available_clusters (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters);

extern return_t fat32_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster_to_write,
    uint32_t new_value);
  
