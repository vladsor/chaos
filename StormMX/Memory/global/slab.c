/* $Id: slab.c,v 1.2 2001/02/10 21:25:53 jojo Exp $ */
/* Abstract: Slab code. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>

#include "slab.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

const int slab_block_size[] = 
{
    8, 16, 32, 64, 128, 256, 512, 1024
};
    
/* Get the index in the heap for the given buffer size. */

int slab_heap_index (unsigned int buffer_size)
{
  unsigned int counter;

  /* Find out which element in this heap we are to use. */

  for (counter = 3; counter <= 10; counter++)
  {
    if (buffer_size <= (unsigned int) (1 << counter))
    {
      return counter - 3;
    }
  }

  /* Larger than 1024? That's not acceptable. */

  return -1;
}

/* Initialise a slab heap. */

bool slab_heap_init (slab_heap_t *heap)
{
  unsigned int counter;

  for (counter = 0; counter < PAGE_SIZE / sizeof (slab_superblock_t *);
       counter++)
  {
    heap->block[counter] = NULL;
  }

  return TRUE;
}

/* This function takes for granted that buffer_size is less than or
   equal to 1024. */ 

bool slab_superblock_init (slab_superblock_t *superblock, slab_heap_t *heap, 
    int index)
{
    unsigned int counter;
    slab_superblock_t *last;
    slab_block_t *slab_block;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, superblock, heap, index);

  /* Make sure we're okay. */

  if (index == -1)
  {
//    DEBUG_MESSAGE (DEBUG, "Failed (index == -1)");
    return FALSE;
  }
  
  superblock->header.magic_number = SLAB_MAGIC_COOKIE;
  superblock->header.buffer_size = slab_block_size[index];

  /* Now, insert this superblock into the heap. We put it at the end
     of the list, so we always know that blocks with free space are in
     the end. This makes allocation more optimised. */

  last = heap->block[index];

  if (last == NULL)
  {
    heap->block[index] = superblock;
    superblock->header.previous_superblock = NULL;
    superblock->header.next_superblock = NULL;
  }
  else
  {
    while (last->header.next_superblock != NULL)
    {
      last = last->header.next_superblock;
    }

    last->header.next_superblock = superblock;
    superblock->header.previous_superblock = last;

    superblock->header.next_superblock = NULL;
  }

  superblock->header.free_blocks = 
    superblock->header.total_blocks = 
    ((PAGE_SIZE - sizeof (slab_superblock_header_t)) /
     slab_block_size[index]);

  /* Set up the linked list of free blocks in this slab block. Start
     with the first one, since it is a little special in that it has
     no 'previous' pointer. */

  slab_block = (slab_block_t *) &superblock->buffer;
  slab_block->previous = NULL;
  slab_block->next = (slab_block_t *)
    ((uint32_t) &superblock->buffer + slab_block_size[index]);
  slab_block = slab_block->next;

  for (counter = 0; counter < superblock->header.total_blocks - 2; counter++)
  {
    slab_block->previous = (slab_block_t *) 
      ((uint32_t) slab_block - slab_block_size[index]);
    slab_block->next = (slab_block_t *)
      ((uint32_t) slab_block + slab_block_size[index]);

    slab_block = slab_block->next;
  }

  /* Also, handle the last block specially, since it has no 'next' pointer. */

  slab_block->previous = (slab_block_t *) 
      ((uint32_t) slab_block - slab_block_size[index]);
  slab_block->next = NULL;

  superblock->header.free_list = (slab_block_t *) &superblock->buffer;

  return TRUE;
}
