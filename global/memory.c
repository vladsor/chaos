/* $Id: memory.c,v 1.2 2001/02/10 21:23:00 jojo Exp $ */
/* Abstract: Memory library. */
/* Authors: Anders Ohrt <doa@chaosdev.org> 
            Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#include <enviroment.h>

#include <avl.h>

#include "slab.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//#define SLAB

/* The memory_structure must be defined by the process if it wants to
   link to this library. This is done by our default stub. (startup.c) */

typedef struct
{
    volatile bool initialised;
    volatile bool locked;
//extern mutex_type memory_mutex;
  
    slab_heap_t *slab_heap;
    
//    avl_tree_t used_pages;
} memory_structure_t;

typedef struct
{
    page_number_t start;
    uint32_t length;

} pages_range_t;

typedef struct
{
    AVL_NODE_PART (pages_range_t);
} memory_pages_t;

memory_structure_t memory_structure = {FALSE, FALSE, NULL};


/* FIXME: This is a little ugly... Any better ideas? Having an extra
   parameter to memory_allocate () would be totally gross. */

/* Initialise the slab system. */

return_t global_memory_init (int argc UNUSED, char *argv[] UNUSED)
{
    page_number_t page;
    physical_memory_allocate (&page, 1);
    memory_structure.slab_heap = (void *) (page * PAGE_SIZE);
    
    memory_structure.locked = FALSE;
    slab_heap_init (memory_structure.slab_heap);
    memory_structure.initialised = TRUE;
    
    return 0;
}

/* Allocate memory. */

sequence_t global_memory_allocate (size_t length)
{
#ifdef SLAB
    int index;
    slab_block_t *block;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, pointer, bytes);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, (*pointer));

    if (!memory_structure.initialised)
    {
        global_memory_init (0, NULL);
    }
    
    index = slab_heap_index (bytes);
/*
    while (memory_structure.locked)
    {
        system_sleep (100);
    }
*/
    memory_structure.locked = TRUE;

    /* If index now is -1, it means we tried to allocate more than 1024
       byte, and in this system, that gets rounded to the closest upper
       page boundary. */

    if (index == -1)
    {
        page_number_t page;
        /* FIXME: Check return value. */

        physical_memory_allocate (&page, SIZE_IN_PAGES (bytes));
        (*pointer) = (void *) (page * PAGE_SIZE);
        
        /*
        new memory_pages;
        avl_tree_add_node (memory_structure.used_pages, memory_pages);
        */

        memory_structure.locked = FALSE;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Return: %p\n",
            __FILE__, __FUNCTION__, (*pointer));
    
        return MEMORY_RETURN_SUCCESS;
    }
    else
    {
        slab_superblock_t *superblock;
        slab_block_t *next;

        /* Now, we know which entry in the slab heap to use. Check if
           there is already a slab superblock we can use. Otherwise, we
           will have to create one. */

        superblock = memory_structure.slab_heap->block[index];

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Superblock is: %p\n",
            __FILE__, __FUNCTION__, superblock);

        /* Walk the list of slab superblocks with free blocks. */

        while (superblock != NULL && (superblock->header.free_blocks == 0 ||
            superblock->header.free_list == NULL))
        {
            superblock = superblock->header.next_superblock;
        }

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Free superblock is: %p\n",
            __FILE__, __FUNCTION__, superblock);
    
        /* No, we were out of luck. */

        if (superblock == NULL)
        {
            page_number_t page;
            /* FIXME: Check return value. */

            physical_memory_allocate (&page, 1);
            superblock = (void *) (page * PAGE_SIZE);

        /*
        new memory_pages;
        avl_tree_add_node (memory_structure.used_pages, memory_pages);
        */

            /* Initialise this newly created slab superblock. */

            slab_superblock_init (superblock, memory_structure.slab_heap, index);
            memory_structure.slab_heap->block[index] = superblock;
        }

        /* Make sure the magic cookie has the right value. */

        if (superblock->header.magic_number != SLAB_MAGIC_COOKIE)
        {
            memory_structure.locked = FALSE;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s::%s Invalid superblock: %X\n",
                __FILE__, __FUNCTION__, superblock->header.magic_number);
                
            return MEMORY_RETURN_SLAB_BROKEN;
        }

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Free superblocks: %u\n",
            __FILE__, __FUNCTION__, superblock->header.free_blocks);
    
        /* Now, we have our superblock. Get the block we want, and update
           the structures. */

        block = superblock->header.free_list;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Block: %p\n",
            __FILE__, __FUNCTION__, block);
            
        next = block->next;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Next is: %p\n",
            __FILE__, __FUNCTION__, next);
            
        if (next != NULL)
        {
            next->previous = NULL;
        }
    
        superblock->header.free_list = next;
        superblock->header.free_blocks--;

        (*pointer) = block;
    }

    memory_structure.locked = FALSE;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Return: %p\n",
        __FILE__, __FUNCTION__, (*pointer));

    return MEMORY_RETURN_SUCCESS;
#else
    return_t return_value;
    page_number_t page;
    sequence_t data;
    
    return_value = physical_memory_allocate (&page, SIZE_IN_PAGES (length));
    
    if (return_value != 0)
    {
        THROW_SYSTEM (EXCEPTION_NOT_ENOUGH_RESOURCES);
    }
    
    data.data = (void *) (page * PAGE_SIZE);
    data.length = SIZE_IN_PAGES (length) * PAGE_SIZE;
    
    return data;
#endif    
}

sequence_t global_memory_reallocate (sequence_t data, size_t new_length)
{
    if (SIZE_IN_PAGE (new_length) == data.length / PAGE_SIZE)
    {
        return data;
    }
    else
    {
        sequence_t new_data;
        
        new_data = global_memory_allocate (new_length);
        memory_copy (new_data.data, data.data, MIN (new_length, data.length));
        
        return new_data;
    }
}

/* Deallocate a previously allocated memory buffer. */

void global_memory_deallocate (sequence_t data)
{
#ifdef SLAB
    slab_superblock_t *superblock = 
        (slab_superblock_t *) ((uint32_t) pointer & 0xFFFFF000);

    slab_block_t *block = (slab_block_t *) pointer;
    int index = slab_heap_index (superblock->header.buffer_size);

    if (!memory_structure.initialised)
    {
        global_memory_init (0, NULL);
    }

//    while (memory_structure.locked)
//    {
//        system_sleep (100);
//    }

    memory_structure.locked = TRUE;

    /* If the data address is page aligned, it is not a slab block, so
       handle it specially. */

    if (pointer == superblock)
    {
        /*
        start_page = (uint32_t) pointer / PAGE_SIZE;
        memory_pages = avl_tree_search_node (memory_structure.used_pages, 
            &start_page);
        deallocate (memory_pages.start, memory_pages.length);
        */
        physical_memory_deallocate ((uint32_t) pointer / PAGE_SIZE, 1);

        memory_structure.locked = FALSE;

        return MEMORY_RETURN_SUCCESS;
    }
    else
    {
        slab_block_t *free_list;

        /* Make sure our magic cookie has the correct value. */

        if (superblock->header.magic_number != SLAB_MAGIC_COOKIE)
        {
            memory_structure.locked = FALSE;
            return MEMORY_RETURN_SLAB_BROKEN;
        }

        /* Add this block to the free list. */
    
        free_list = superblock->header.free_list;
        block->previous = NULL;
        block->next = free_list;

        if (free_list != NULL)
        {
            free_list->previous = block;
        }

        superblock->header.free_list = block;
        superblock->header.free_blocks++;

        if (superblock->header.free_blocks == 1)
        {
            /* This superblock was all-allocated, so add it into the
               heap. We put it last, since that's probably the most
               optimised thing to do. */

            slab_superblock_t *new_superblock = 
                memory_structure.slab_heap->block[index];
      
            while (new_superblock->header.next_superblock != NULL)
            {
                new_superblock = new_superblock->header.next_superblock;
            }

            new_superblock->header.next_superblock = superblock;
            superblock->header.previous_superblock = new_superblock;
      
            superblock->header.next_superblock = NULL;
        }

    /* FIXME: This code will make things a little more optimised, but
       it is not yet finished. */

    else if (superblock->header.free_blocks ==
             superblock->header.total_blocks)
    {
      /* Move this superblock from its current location to the end of
         the heap. We want it in the end, so for this, we'll have to
         traverse the list some... */

      slab_superblock_t *new_superblock;

      new_superblock = memory_structure.slab_heap->block[index]; 
      while (new_superblock->header.next_superblock != NULL)
      {
        new_superblock = new_superblock->header.next_superblock;
      }

      new_superblock->header.next_superblock = superblock;
      superblock->header.previous_superblock = new_superblock;

      superblock->header.next_superblock = NULL;
    }

        memory_structure.locked = FALSE;
//        (*pointer) = NULL;

        return MEMORY_RETURN_SUCCESS;
    }
#else
    return_t return_value;
    page_number_t page;
    
    page = (uint32_t) data.data / PAGE_SIZE;
    
    return_value = physical_memory_deallocate (page, SIZE_IN_PAGES (data.length));
    
    if (return_value != 0)
    {
        THROW_SYSTEM (EXCEPTION_INTERNAL_ERROR);
    }
#endif    
}