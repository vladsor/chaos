/* $Id: slab.h,v 1.2 2001/02/10 21:26:25 jojo Exp $ */
/* Abstract: Slab structures. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __STORM_GENERIC_SLAB_H__
#define __STORM_GENERIC_SLAB_H__

#define SLAB_MAGIC_COOKIE       0xC0CAC01A

/* Type definitions. */

typedef struct
{
    void *block[0];
} slab_heap_t;

typedef struct
{
    uint32_t magic_number;
    unsigned int buffer_size;
    void *previous_superblock;
    void *next_superblock;
    void *free_list;
    unsigned int free_blocks;
    unsigned int total_blocks;
} slab_superblock_header_t;

typedef struct
{
  void *previous;
  void *next;
} slab_block_t;

typedef struct
{
    slab_superblock_header_t header;
    uint8_t buffer[0];
} slab_superblock_t;

extern const int slab_block_size[];

/* Function prototypes. */

extern bool slab_heap_init (slab_heap_t *heap);
extern bool slab_superblock_init (slab_superblock_t *superblock, 
    slab_heap_t *heap, int index);
extern int slab_heap_index (unsigned int buffer_size);

#endif /* !__STORM_GENERIC_SLAB_H__ */
