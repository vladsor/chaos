#include <enviroment.h>
#include <avl.h>

#include "id_pool.h"

#define DEBUG_MODULE_NAME "RangePool"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

// FIXME: add checks for ranges

static int range_compare_by_length (void *key1, void *key2)
{
#define range1 ((range_t *) key1)
#define range2 ((range_t *) key2)
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s: length1=%u {%p}, length2=%u {%p}.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        range1->length, key1, range2->length, key2);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
        "%s: %s: Return %i.\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        range2->length - range1->length);

    return (range2->length - range1->length);
#undef range1
#undef range2
}

static int range_compare_by_index (void *key1, void *key2)
{
#define range1 ((range_t *) key1)
#define range2 ((range_t *) key2)
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
        "%s: %s: {%p}:[%u][%u], {%p}[%u][%u].\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        key1, range1->start, range1->length,
        key2, range2->start, range2->length);

    if (range1->start < range2->start)
    {
        if ((range1->start + range1->length) <= range2->start)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
                "%s: %s: Return %i.\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                range2->start - (range1->start + range1->length) + 1);
        
            return range2->start - (range1->start + range1->length) + 1;
        }

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
            "%s: %s: Return 0.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return 0;
    }

    if (range1->start >= range2->start + range2->length)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
            "%s: %s: Return %i.\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            range2->start + range2->length - range1->start - 1);
        
        return range2->start + range2->length - range1->start - 1;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
        "%s: %s: Return 0.\n",
    DEBUG_MODULE_NAME, __FUNCTION__);

    return 0;
#undef range1
#undef range2
}

static inline bool add_range (pool_t *pool, range_t range)
{
    range_node_t *node_by_index;
    range_node_t *node_by_length;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: with range %u-%u.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        range.start, range.start + range.length - 1);
  
    node_by_index = (range_node_t *) 
        (*((raw_memory_t *) pool->memory)->allocate) (pool->memory);
    
    if (node_by_index == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Internal allocation fails.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);
            
        return FALSE;
    }
    
    node_by_length = (range_node_t *) 
        (*((raw_memory_t *) pool->memory)->allocate) (pool->memory);
    
    if (node_by_index == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Internal allocation fails.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);
            
        return FALSE;
    }
  
    node_by_index->key = range;
    node_by_index->left = node_by_index->right = 
        node_by_index->parent = NULL;
    node_by_index->level = 1;

    node_by_length->key = range;
    node_by_length->left = node_by_length->right = 
        node_by_length->parent = NULL;
    node_by_length->level = 1;
    
    (range_node_t *) node_by_index->opposite = node_by_length;
    (range_node_t *) node_by_length->opposite = node_by_index;

    avl_tree_add_node ((avl_tree_t *) &pool->free_by_index, 
        (avl_node_t *) node_by_index);

    avl_tree_add_node ((avl_tree_t *) &pool->free_by_length, 
        (avl_node_t *) node_by_length);
        
    return TRUE;
}

static inline bool is_node_empty (range_node_t *node)
{
    return (node->key.length == 0);
}

void pool_init (p_pool_t pool, range_t range, p_raw_memory_t memory)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s with range %u-%u.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        range.start, range.start + range.length - 1);

     /* create AVL-tree. */
    avl_tree_create ((avl_tree_t *) &pool->free_by_length, 
        range_compare_by_length);

    avl_tree_create ((avl_tree_t *) &pool->free_by_index, 
        range_compare_by_index);

    /* store range. */
    pool->range = range;
    pool->free_count = range.length;
    
    pool->memory = memory;

    /* at first time store is full. */
    add_range (pool, range);
}

return_t pool_allocate (pool_t *pool, range_t *range)
{
    range_node_t *current_node;
    range_node_t *current_node2;
    unsigned int condition;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (pool: %p, range: %p, length: %u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        pool, range, range->length);

    if (range == NULL || range->start != 0 || range->length == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Invalid arguments.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return -1;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Index root: %p, Length root: %p\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        pool->free_by_index.root,
        pool->free_by_length.root);
  
    /* if store is empty, */
    if (pool_is_empty (pool))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s::%s Store is empty.\n", 
            __FILE__, __FUNCTION__);
        
        /* than fail. */
        return -1;
    }

    condition = CONDITION_MORE;
    current_node = (range_node_t *) avl_tree_search_nearest_node (
        &pool->free_by_length, (void *) range, &condition);

    if (current_node == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Not enougth storage space.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return -1;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Length node {%p} is %u-%u.\n", 
        __FILE__, __FUNCTION__, current_node,
        current_node->key.start, current_node->key.start + 
        current_node->key.length - 1);

    current_node2 = (range_node_t *) current_node->opposite;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Index node {%p} is %u-%u.\n", 
        __FILE__, __FUNCTION__, current_node2,
        current_node2->key.start, current_node2->key.start + 
        current_node2->key.length - 1);

    range->start = current_node->key.start;
    current_node->key.start += range->length; 
    current_node->key.length -= range->length;

    current_node2->key.start += range->length; 
    current_node2->key.length -= range->length;

    if (is_node_empty (current_node))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s Removing empty nodes: %p, %p\n",
            __FILE__, __FUNCTION__, 
            current_node, current_node2);
            
        avl_tree_delete_node ((avl_tree_t *) &pool->free_by_length, 
            (avl_node_t *) current_node);
        
        avl_tree_delete_node ((avl_tree_t *) &pool->free_by_index, 
            (avl_node_t *) current_node2);

        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node);
        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node2);
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s Updating nodes: %p, %p\n",
            __FILE__, __FUNCTION__, 
            current_node, current_node2);

        avl_tree_update_node ((avl_tree_t *) &pool->free_by_length, 
            (avl_node_t *) current_node);
    
        avl_tree_update_node ((avl_tree_t *) &pool->free_by_index, 
            (avl_node_t *) current_node2);
    }
    
    pool->free_count -= range->length;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Index root {%p} range: %u-%u.\n", 
        __FILE__, __FUNCTION__, 
        pool->free_by_index.root,
        ((range_node_t *) pool->free_by_index.root)->key.start, 
        ((range_node_t *) pool->free_by_index.root)->key.start +
        ((range_node_t *) pool->free_by_index.root)->key.length - 1);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Length root {%p} range: %u-%u.\n", 
        __FILE__, __FUNCTION__, 
        pool->free_by_length.root,
        ((range_node_t *) pool->free_by_length.root)->key.start, 
        ((range_node_t *) pool->free_by_length.root)->key.start +
       ((range_node_t *) pool->free_by_length.root)->key.length - 1);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Allocated range is %u-%u.\n", 
        __FILE__, __FUNCTION__, 
        range->start, range->start + range->length - 1);

    return STORM_RETURN_SUCCESS;
}

static bool is_range_cover (range_t *range1, range_t *range2)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%u-%u, %u-%u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        range1->start, range1->length, range2->start, range2->length);

    if ((range1->start <= range2->start) && 
        (range1->start + range1->length >= range2->start + range2->length))
    {
        return TRUE;
    }
    
    return FALSE;
}

return_t pool_reserve (pool_t *pool, range_t range)
{
    range_node_t *current_node;
    range_node_t *current_node2;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (pool: %p, range: %u-%u).\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        pool, range.start, range.start + range.length - 1);
  
    current_node = (range_node_t *) avl_tree_search_node (
        (avl_tree_t *) &pool->free_by_index, (void *) &range, 
        CONDITION_EQUAL);

    if (current_node == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s Already used.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);

        return -1;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Index node {%p} is %u-%u.\n", 
        __FILE__, __FUNCTION__, current_node,
        current_node->key.start, current_node->key.start + 
        current_node->key.length - 1);
        
    if (!is_range_cover (&current_node->key, &range))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Range overlaped.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__);

        return -1;
    }

    current_node2 = (range_node_t *) current_node->opposite;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Length node {%p} is %u-%u.\n", 
        __FILE__, __FUNCTION__, current_node2, 
        current_node2->key.start, current_node2->key.start + 
        current_node2->key.length - 1);
    
    if (range.start == current_node->key.start)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Ranges begin at same position.\n", 
        __FILE__, __FUNCTION__);

        current_node->key.start = range.start + range.length;
        current_node->key.length -= range.length;

        current_node2->key.start = range.start + range.length;
        current_node2->key.length -= range.length;
        
        if (is_node_empty (current_node))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                "%s::%s Node became empty.\n", 
                __FILE__, __FUNCTION__);

            avl_tree_delete_node ((avl_tree_t *) &pool->free_by_index,
 
               (avl_node_t *) current_node);
            
            avl_tree_delete_node ((avl_tree_t *) &pool->free_by_length,
                (avl_node_t *) current_node2);

        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node);
        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node2);
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                "%s::%s Update nodes.\n", 
                __FILE__, __FUNCTION__);

            avl_tree_update_node ((avl_tree_t *) &pool->free_by_index,
                (avl_node_t *) current_node);

            avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
                (avl_node_t *) current_node2);
        }
    }
    else if (range.start + range.length == 
        current_node->key.start + current_node->key.length)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
            "%s::%s Ranges end at same position.\n", 
            __FILE__, __FUNCTION__);

        current_node->key.length -= range.length;
        current_node2->key.length -= range.length;

        avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
           (avl_node_t *) current_node2);
    }
    else
    {
        range_t new_range;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
          "%s::%s Range in middle.\n", 
          __FILE__, __FUNCTION__);

        new_range.start = range.start + range.length;
        new_range.length = current_node->key.start + current_node->key.length - 
        range.start - range.length;
        
        current_node->key.length = range.start - current_node->key.start;
        current_node2->key.length = range.start - current_node2->key.start;

        avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
           (avl_node_t *) current_node2);

        add_range (pool, new_range);
    }  
    
    pool->free_count -= range.length;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Index root {%p} range: %u-%u.\n", 
        __FILE__, __FUNCTION__, 
        pool->free_by_index.root,
        ((range_node_t *) pool->free_by_index.root)->key.start, 
        ((range_node_t *) pool->free_by_index.root)->key.start +
        ((range_node_t *) pool->free_by_index.root)->key.length - 1);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Length root {%p} range: %u-%u.\n", 
        __FILE__, __FUNCTION__, 
        pool->free_by_length.root,
        ((range_node_t *) pool->free_by_length.root)->key.start, 
        ((range_node_t *) pool->free_by_length.root)->key.start +
       ((range_node_t *) pool->free_by_length.root)->key.length - 1);

    return STORM_RETURN_SUCCESS;
}

/*
  FUNCTION:     id_pool_deallocate_id
  DESCRIPTION:  deallocate ID to store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                id - deallocated ID.
  RETURN VALUE: TRUE - if successfull,
                FALSE - otherwise.
*/
return_t pool_deallocate (pool_t *pool, range_t range)
{
    range_node_t *current_node;
    range_node_t *update_node = NULL;
    unsigned int condition;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s::%s range: %u-%u.\n", 
        __FILE__, __FUNCTION__, range.start, range.start + range.length - 1);
  
    condition = CONDITION_LESS;
    current_node = (range_node_t *) avl_tree_search_nearest_node (
        (avl_tree_t *) &pool->free_by_index, (void *) &range, 
        &condition);

    if (condition == CONDITION_EQUAL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s::%s This range not used.\n", 
            __FILE__, __FUNCTION__);
            
        return -1;    
    }
    else if (condition != CONDITION_LESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s::%s Internal error.\n", 
            __FILE__, __FUNCTION__);
            
        return -1;    
    }

    if (current_node != NULL)
    {
    
        if ((current_node->key.start + current_node->key.length) == range.start)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Need to join with previous.\n", 
                __FILE__, __FUNCTION__);
                
            update_node = current_node;
        }
    }

    condition = CONDITION_MORE;
    current_node = (range_node_t *) avl_tree_search_nearest_node (
        (avl_tree_t *) &pool->free_by_index, (void *) &range, 
        &condition);

    if (condition != CONDITION_MORE)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s::%s Internal error.\n", 
            __FILE__, __FUNCTION__);
            
        return -1;    
    }
    
    if ((current_node == NULL) || (range.start + range.length) != (current_node->key.start))
    {
        if (update_node == NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s New node: %u-%u.\n", 
                __FILE__, __FUNCTION__,
                range.start, range.start + range.length - 1);
        
            add_range (pool, range);
        }
        else
        {
            range_node_t *current_node2;
            
            current_node2 = (range_node_t *) update_node->opposite;
            
            update_node->key.length += range.length;
            current_node2->key.length += range.length;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Update node: %u-%u.\n", 
                __FILE__, __FUNCTION__,
                update_node->key.start, update_node->key.start + 
                    update_node->key.length - 1);
            
            avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
                (avl_node_t *) current_node2);
        }
        
        return STORM_RETURN_SUCCESS;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Need to join with next.\n", 
        __FILE__, __FUNCTION__);
    
    if (update_node == NULL)
    {
        range_node_t *current_node2;
            
        current_node2 = (range_node_t *) current_node->opposite;
        
        current_node->key.length += range.length;
        current_node2->key.length += range.length;

        current_node->key.start = range.start;
        current_node2->key.start = range.start;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Update node: %u-%u.\n", 
            __FILE__, __FUNCTION__,
            current_node->key.start, current_node->key.start + 
                current_node->key.length - 1);
        
        avl_tree_update_node ((avl_tree_t *) &pool->free_by_index,
            (avl_node_t *) current_node);
            
        avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
            (avl_node_t *) current_node2);
    }
    else
    {
        range_node_t *current_node2;
        uint32_t new_length;
         
        new_length = update_node->key.length + range.length + 
            current_node->key.length;
        
        current_node2 = (range_node_t *) current_node->opposite;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Delete node: %u-%u.\n", 
            __FILE__, __FUNCTION__,
            current_node->key.start, current_node->key.start + 
                current_node->key.length - 1);
        
        avl_tree_delete_node ((avl_tree_t *) &pool->free_by_index, 
            (avl_node_t *) current_node);
        
        avl_tree_delete_node ((avl_tree_t *) &pool->free_by_length, 
            (avl_node_t *) current_node2);

        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node);
        (*((raw_memory_t *) pool->memory)->deallocate) (pool->memory, 
            current_node2);

        current_node2 = (range_node_t *) update_node->opposite;
        
        update_node->key.length = new_length;
        current_node2->key.length = new_length;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Update node: %u-%u.\n", 
            __FILE__, __FUNCTION__,
            update_node->key.start, update_node->key.start + 
                update_node->key.length - 1);
        
        avl_tree_update_node ((avl_tree_t *) &pool->free_by_length,
            (avl_node_t *) current_node2);
    }

    return STORM_RETURN_SUCCESS;
}

bool pool_is_empty (pool_t *pool)
{
    return (pool->free_by_length.root == NULL);
}

bool pool_is_full (pool_t *pool)
{
    return ((pool->free_by_length.root != NULL) &&
        ( ((range_node_t *) pool->free_by_length.root)->key.start == pool->range.start) &&
        ( ((range_node_t *) pool->free_by_length.root)->key.length == pool->range.length));
}

iterator_t * pool_get_iterator (pool_t *pool)
{
    return (iterator_t *) (avl_tree_get_iterator (
        (avl_tree_t *) &pool->free_by_index));
}

