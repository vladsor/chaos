#include <hash_table.h>

#define MAX_PATH 256

typedef struct
{
  HASH_ELEMENT_PART;
  
  file_handle_t handle;
  
  uint32_t mode;

  vfat_volume_t *volume;

  struct vfat_file_t *parent_file;

  fat_entry_t entry;

  /* point on filename (250 chars max) in PathName */
  char *object_name;

  /* path+filename 260 max */
  char path_name[MAX_PATH];

  uint32_t ref_count;

  uint32_t flags;

} vfat_file_t;

extern vfat_file_t * vfat_new_fcb (char *file_name);

extern void vfat_destroy_fcb (vfat_file_t *fcb);

extern bool vfat_fcb_is_directory (vfat_file_t *fcb);

extern bool vfat_fcb_is_root (vfat_file_t *fcb);

extern void vfat_grab_fcb (
  vfat_volume_t *vfat_volume, 
  vfat_file_t *fcb);

extern void vfat_release_fcb (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb);

extern void vfat_add_fcb_to_table (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb);

extern vfat_file_t * vfat_grab_fcb_from_table (
  vfat_volume_t *vfat_volume,
  uint8_t *file_name);

extern return_t vfat_request_and_validate_region (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t offset,
  void **buffer,
  cache_segment_t **cache_segment,
  bool extend);
  
extern return_t vfat_release_region (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  cache_segment_t *cache_segment);


extern vfat_file_t * vfat_open_root_fcb (
  vfat_volume_t *vfat_volume);

extern vfat_file_t * vfat_make_root_fcb (
  vfat_volume_t *vfat_volume);

extern return_t vfat_make_fcb_from_dir_entry (
  vfat_volume_t *vfat_volume,
  vfat_file_t *directory_fcb,
  uint8_t *long_name,
  fat_entry_t *dir_entry,
  vfat_file_t **file_fcb);

extern return_t vfat_dir_find_file (
  vfat_volume_t *vfat_volume,
  vfat_file_t *directory_fcb,
  uint8_t *file_to_find,
  vfat_file_t **found_fcb);

extern return_t vfat_get_fcb_for_file (
  vfat_volume_t *vfat_volume,
  vfat_file_t **parent_fcb,
  vfat_file_t **fcb, 
  uint8_t *file_name);
  
#define FILE_ATTRIBUTE_READ_ONLY  0x01
#define FILE_ATTRIBUTE_HIDDEN     0x02
#define FILE_ATTRIBUTE_SYSTEM     0x04
#define FILE_ATTRIBUTE_VOLUME_ID  0x08
#define FILE_ATTRIBUTE_DIRECTORY  0x10
#define FILE_ATTRIBUTE_ARCHIVE    0x20

enum
{
    FILE_OPTION_DIRECTORY,
};

