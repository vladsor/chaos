
extern p_vfat_file_t vfat_file_create_data (const wchar_t *file_name);
extern void vfat_file_destroy_data (p_vfat_file_t file);
extern bool vfat_file_is_directory (p_vfat_file_t file);
extern bool vfat_file_is_root (p_vfat_file_t file);

extern void vfat_file_acquire ( 
    p_vfat_file_t file);

extern void vfat_file_release (
    p_vfat_file_t file);

return_t vfat_file_read_region (
    p_vfat_file_t file,
    uint32_t offset,
    p_uint8_t buffer,
    bool extend);

extern p_vfat_file_t vfat_file_open_root (
    p_vfat_volume_t vfat_volume);

extern p_vfat_file_t vfat_file_create_root_data (
    p_vfat_volume_t vfat_volume);

return_t vfat_file_create_data_from_directory_entry (
    p_vfat_file_t directory_file,
    const wchar_t *long_name,
    p_fat_entry_t directory_entry,
    p_vfat_file_t *file_data);

extern return_t vfat_directory_find_file (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t directory_file,
    const wchar_t *file_to_find,
    p_vfat_file_t *found_file);

return_t vfat_file_get_data_for_name (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t *parent_file,
    p_vfat_file_t *file,
    const wchar_t *file_name);
  
#define FILE_ATTRIBUTE_READ_ONLY  0x01
#define FILE_ATTRIBUTE_HIDDEN     0x02
#define FILE_ATTRIBUTE_SYSTEM     0x04
#define FILE_ATTRIBUTE_VOLUME_ID  0x08
#define FILE_ATTRIBUTE_DIRECTORY  0x10
#define FILE_ATTRIBUTE_ARCHIVE    0x20

enum
{
    FILE_OPTION_DIRECTORY = BIT_VALUE (0),
};

