#include <hash_table.h>

#define VFAT_MAX_PATH 260

struct vfat_volume_struct;
typedef struct vfat_volume_struct vfat_volume_t;
typedef vfat_volume_t * p_vfat_volume_t;

typedef return_t (vfat_get_next_cluster_t) (
    p_vfat_volume_t vfat_volume, 
    uint32_t current_cluster,
    uint32_t *next_cluster);
typedef vfat_get_next_cluster_t * p_vfat_get_next_cluster_t;
  
typedef return_t (vfat_find_available_cluster_t) (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster);
typedef vfat_find_available_cluster_t * p_vfat_find_available_cluster_t;

typedef return_t (vfat_count_available_clusters_t) (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters);
typedef vfat_count_available_clusters_t * p_vfat_count_available_clusters_t;
  
typedef return_t (vfat_write_cluster_t) (
    p_vfat_volume_t vfat_volume, 
    uint32_t cluster_to_write,
    uint32_t new_value);
typedef vfat_write_cluster_t * p_vfat_write_cluster_t;

struct vfat_volume_struct
{
    handle_reference_t storage_device;

    uint32_t sectors_per_cluster;
    uint32_t bytes_per_sector;
    uint32_t bytes_per_cluster;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;

    uint32_t total_volume_length;

    uint32_t fat_offset;
    uint32_t fat_length;
    uint32_t number_of_fats;

    uint32_t root_offset;
    uint32_t root_length;
    uint32_t number_of_root_entries;
    uint32_t root_cluster;

    uint32_t data_offset;
    uint32_t data_length;

    uint32_t fat_entries_per_sector;
    uint32_t fat_unit;

    unsigned int fat_type;
  
    uint32_t serial_number;
    uint8_t  label[256];

    uint8_t volume_label[256];
    uint32_t volume_label_length;
  
    uint32_t hidden_sectors;

    p_vfat_get_next_cluster_t get_next_cluster;
    p_vfat_find_available_cluster_t find_available_cluster;
    p_vfat_count_available_clusters_t count_available_clusters;
    p_vfat_write_cluster_t write_cluster;
};

struct vfat_file_struct;
typedef struct vfat_file_struct vfat_file_t;
typedef vfat_file_t * p_vfat_file_t;

struct vfat_file_struct
{
    HASH_ELEMENT_PART;

    /* path+filename 260 max */
    wchar_t path_name[VFAT_MAX_PATH];
  
    uint32_t mode;

    p_vfat_volume_t volume;

    p_vfat_file_t parent_file;

    fat_entry_t entry;

    /* point on filename (250 chars max) in PathName */
    wchar_t *object_name;

    uint32_t ref_count;

    uint32_t flags;
};
