#ifndef __VFAT_FAT_H__
#define __VFAT_FAT_H__

enum fat_t
{
    FAT_12,
    FAT_16,
    FAT_32,
};

#define BLOCK_SIZE 512

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

#endif /* !__VFAT_FAT_H__ */

