/* $Id: fat.h,v 1.2 2001/02/10 21:24:26 jojo Exp $ */
/* Abstract: Data structures used by the FAT server. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#ifndef __FAT_H__
#define __FAT_H__

#include <interface.h>
#include <ipool.h>

enum fat_t
{
    FAT_12,
    FAT_16,
    FAT_32,
};

#define MAX_PATH_NAME_LENGTH    (1024 - 100)
#define MAX_FILE_NAME_LENGTH    256

enum
{
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_FILE,
    FILE_TYPE_SOFT_LINK,
    FILE_TYPE_HARD_LINK,
};

typedef uint32_t file_handle_t;
typedef uint64_t time_t;

typedef struct
{
    file_handle_t file_handle;

    uint8_t name[MAX_FILE_NAME_LENGTH];

    uint32_t file_type;
    bool last_file_in_list;

    uint32_t file_size;

    time_t creation_time;
    time_t modification_time;
    time_t access_time;

} file_info_t;

/* The time format used by FAT. */

typedef struct
{
    uint16_t hours : 5;
    uint16_t minutes : 6;
  
  /* The seconds are specified as the real value divided by two, so
     the range is really 0-29. */
  
    uint16_t seconds : 5;
} fat_time_t PACKED;

/* The date format used by FAT. */

typedef struct
{
    /* 1980 is added to the year, so the range is 1980-2107. */
  
    uint16_t year : 7;

    /* 1 = January, valid range 1-12. */

    uint16_t month : 4;

    /* Valid range 1-31. */
  
    uint16_t day : 5;
} fat_date_t PACKED;

typedef struct
{
    object_t *generic;
} device_t;

struct vfat_volume_t;

typedef struct
{
    device_t storage_device;

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

  return_t (*get_next_cluster) (
    struct vfat_volume_t *vfat_volume, 
    uint32_t current_cluster,
    uint32_t *next_cluster);
  
  return_t (* find_available_cluster) (
    struct vfat_volume_t *vfat_volume,
    uint32_t *cluster);

  return_t (* count_available_clusters) (
    struct vfat_volume_t *vfat_volume,
    uint32_t *number_of_clusters);
  
  return_t (* write_cluster) (
    struct vfat_volume_t *vfat_volume, 
    uint32_t cluster_to_write,
    uint32_t new_value);

} vfat_volume_t;

typedef struct
{
  /* A 'file handle', in the VFS namespace. */

  file_handle_t file_handle;

  /* The starting cluster number for this file. */

  uint32_t start_cluster_number;

  /* The current cluster number that we are accessing. */

  uint32_t current_cluster_number;

  /* The current file position in bytes. */

  uint32_t file_position;

  /* The total size of this file in bytes. */

  uint32_t file_size;
} fat_open_file_t;

/* FAT types. */

typedef uint8_t fat12_t;
typedef uint16_t fat16_t;
typedef uint32_t fat32_t;

#define FAT12_READ_ENTRY(fat,index) (index % 2 == 0 ? \
      *((uint16_t *) &fat[(index * 3) / 2]) & 0xFFF : \
      *((uint16_t *) &fat[(index * 3) / 2]) >> 4)

#define FAT12_END_OF_CLUSTER_CHAIN      0xFF8
#define FAT12_BAD_CLUSTER               0xFF7

#define FAT16_END_OF_CLUSTER_CHAIN      0xFFF8

#define FAT32_END_OF_CLUSTER_CHAIN      0xFFFFFFF8

#define FAT_MAX_OPEN_FILES              16

extern return_t vfat_interface_init (void);

extern return_t vfat_file_list_read (
  file_handle_t file_handle,
  file_info_t *file_info,
  uint32_t first_entry,
  uint32_t *number_of_entries);

extern return_t vfat_file_open (
  vfat_volume_t *vfat_volume, 
  file_handle_t *file_handle,
  uint8_t *file_name,
  uint32_t mode,
  file_info_t *file_info);

extern return_t vfat_file_close (
  vfat_volume_t *vfat_volume, 
  file_handle_t file_handle);

extern return_t vfat_file_read (
  vfat_volume_t *vfat_volume, 
  file_handle_t file_handle,
  void *read_buffer, 
  uint32_t offset,
  uint32_t bytes,
  uint32_t *read_bytes);

extern return_t vfat_file_write (
  vfat_volume_t *vfat_volume, 
  file_handle_t file_handle,
  void *write_buffer, 
  uint32_t offset,
  uint32_t bytes);

extern return_t vfat_file_delete (
    vfat_volume_t *vfat_volume, 
    uint8_t *file_name);

#endif /* !__FAT_H__ */

