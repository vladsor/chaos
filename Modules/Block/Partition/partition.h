/* $Id: partition.h,v 1.1 2001/02/10 22:58:21 jojo Exp $ */
/* Abstract: Partitioning stuff. */
/* Author: Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */


#ifndef __PARTITION_PARTITION_H__
#define __PARTITION_PARTITION_H__


/* A partition table entry. */

typedef struct
{
  /* Active flag. */

  uint8_t : 7;
  uint8_t active : 1;

  uint8_t starting_head;
  uint16_t starting_sector : 6;
  uint16_t starting_cylinder : 10;

  /* Type of the partition. */

  uint8_t type;

  uint8_t ending_head;
  uint16_t ending_sector : 6;
  uint16_t ending_cylinder : 10;

  /* The partition descibed in a 'correct' way. */

  uint32_t lba_starting_sector_number;
  uint32_t lba_number_of_sectors;
} PACKED partition_entry_t;

typedef struct
{
    uint8_t type;
    uint8_t partition_type;
    char *name;
} partition_record_t;

#define PARTITION_TYPE_NORMAL                   0x00
#define PARTITION_TYPE_EXTENDED                 0x01

#define PARTITION_TYPE_EXTENDED_DOS             0x05
#define PARTITION_TYPE_EXTENDED_LINUX           0x85
#define PARTITION_TYPE_EXTENDED_WINDOWS         0x0F

extern return_t scan_for_partitions (handle_t *generic, char *name);

#endif /* !__PARTITION_PARTITION_H__ */
