/* Abstract: Sources of hash table library functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2001 chaos development. */

#include <enviroment.h>

#include <string.h>

#include "hash_table.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/**
 * @brief       Converting string to hash. 
 *
 * The hashcode for a string calculated from next formula:
 * s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
 * using int arithmetic, where s[i] is the i-th character of the string,
 * n is the length of the string, and ^ indicates exponentiation. 
 * (The hash value of the empty string is zero.)
 *
 * @param key       pointer to string
 * @return      hash
 */

unsigned int string_to_hash (void *key)
{
    unsigned int hash = 0;
    unsigned int i;
    char *string = (char *) key;
    unsigned int acc = 1;

    for (i = 0 ; i < string_length (string) ; i++)
    {
        hash = acc * string[i];
        acc *= 31;
    }

    return hash;
}

/**
 * @brief       Converting hash to entry of hash table
 *
 * @param hash_table    pointer to hash table
 * @param hash      converted hash
 *
 * @return      entry of hash table
 */

static inline unsigned int hash_to_entry (hash_table_t *hash_table, 
    unsigned int hash)
{
    /* hash-function simply the rest of division on number of entries */
    return (hash % hash_table->limit_entries);
}

static bool hash_table_iterator_has_next (hash_table_iterator_t *iterator)
{
    return iterator->current_element == NULL;
}

static hash_element_t * hash_table_iterator_get_next (
    hash_table_iterator_t *iterator)
{
    hash_element_t *current_element;
    
    current_element = iterator->current_element;
    
    if (current_element != NULL)
    {
        if (current_element->next != NULL)
        {
            iterator->current_element = (hash_element_t *) 
                current_element->next;
        }
        else
        {
            unsigned int entry;
            
            iterator->current_element = NULL;
    
            for (entry = 0; 
                entry < ((hash_table_t *) iterator->hash_table)->limit_entries; 
                entry++)
            {
                if (((hash_table_t *) iterator->hash_table)->
                    hash_elements[entry] != NULL)
                {
                    iterator->current_element = 
                        ((hash_table_t *) iterator->hash_table)->
                            hash_elements[entry];
                    break;
                }
            }
        
        }
    }
    
    return current_element;
}

/**
 * @brief       Create hash table.
 *
 * Create new hash table with given number of entries.
 *
 * @param hash_table    pointer to hash table
 * @param limit_hash_entries 
 *          number of entries
 */

void hash_table_create (hash_table_t *hash_table, 
    unsigned int limit_hash_entries, key_to_hash_function_t key_to_hash,
    compare_function_t key_compare)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: %s (%p, %u, %p, %p)\n",
        __FUNCTION__, hash_table, limit_hash_entries, key_to_hash, key_compare);

    /* initialising hash table */
    hash_table->limit_entries = limit_hash_entries;

    hash_table->key_to_hash = key_to_hash;
    hash_table->key_compare = key_compare;

    /* number of elements is zero */
    hash_table->number_of_elements = 0;

    /* mark all entries as empty (e.g. NULL = 0). */
    memory_set_uint8 ((uint8_t *) hash_table->hash_elements, 0, 
        sizeof (hash_element_t *) * limit_hash_entries);

    hash_table->iterator.current_element = NULL;
    hash_table->iterator.entry = 0;
    hash_table->iterator.hash_table = (struct hash_table_t *) hash_table;
    
    hash_table->iterator.has_next = (hash_table_iterator_has_next_function_t *) 
        &hash_table_iterator_has_next;
    hash_table->iterator.get_next = (hash_table_iterator_get_next_function_t *) 
        &hash_table_iterator_get_next;
}

/**
 * @brief       Destroy hash table.
 *
 * Unconditional destroy diven hash table.
 *
 * @param hash_table    pointer to hash table
 *
 * @todo Please implement this function.
 */

void hash_table_destroy (hash_table_t *hash_table, 
    hash_element_destroy_function_t destroy)
{
    unsigned int entry;
    hash_element_t *element;
    hash_element_t *previous_element;

    for (entry = 0; entry < hash_table->limit_entries; entry++)
    {
        previous_element = hash_table->hash_elements[entry];

        while (previous_element != NULL)
        {
            element = (hash_element_t *) previous_element->next;
            destroy (previous_element);
            previous_element = element;
        }
    }
}

/**
 * @brief       Search element in hash table.
 *
 * Search in hash table for element with given key.
 *
 * @param hash_table    pointer to hash table
 * @param key       given key
 *
 * @return      pointer to element of hash table if found, else NULL.
 */

hash_element_t *hash_table_search_element (hash_table_t *hash_table, void *key)
{
    hash_element_t *node;
    unsigned int hash;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: %s (%p, %p)\n",
        __FUNCTION__, hash_table, key);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable::%s KeyToHash: %p, KeysCompare: %p\n",
        __FUNCTION__, hash_table->key_to_hash, hash_table->key_compare);

    hash = hash_table->key_to_hash (key);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: Hash = %u, Entry = %u\n",
        hash, hash_to_entry (hash_table, hash));

    /* searching entry in hash table */
    node = (hash_element_t *) hash_table->hash_elements[
        hash_to_entry (hash_table, hash)];


    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: Testing node: %p\n", node);
	
    while ((node != NULL) && 
        (hash_table->key_compare (node->key_n_data, key) != CONDITION_EQUAL))
    {
        node = (hash_element_t *) node->next;
	
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "Hashtable: Testing node: %p\n", node);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: %s DONE\n",
        __FUNCTION__);

    /* returning or found element or NULL */
    return node;
}


/**
 * @brief       Add element into hash table.
 *
 * Add given element into hash table.
 *
 * @param hash_table    pointer to hash table
 * @param new_hash_element 
 *          added element
 *               
 *  @return         TRUE - if successful, FALSE - otherwise
 */

bool hash_table_add_element (hash_table_t *hash_table, 
    hash_element_t *new_hash_element)
{
    unsigned int entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: %s (%p, %p)\n",
        __FUNCTION__, hash_table, new_hash_element);

    new_hash_element->hash = hash_table->key_to_hash (
	new_hash_element->key_n_data);

    /* calculate entry for added element */
    entry = hash_to_entry (hash_table, new_hash_element->hash);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: Hash = %u, Entry = %u\n",
        new_hash_element->hash, entry);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: Next element: %p\n",
        hash_table->hash_elements[entry]);

    /* adding new element at the begin of entry */
    (hash_element_t *) new_hash_element->next = 
        hash_table->hash_elements[entry];
                               
    hash_table->hash_elements[entry] = new_hash_element;

    /* increasing number of elements */
    hash_table->number_of_elements++;

    return TRUE;
}

/**
 * @brief       Delete element from hash table.
 *
 * Delete from hash table element with given key.
 *
 * @param hash_table    pointer to hash table 
 * @param key       given key
 *
 * @return      pointer of deleted hash element, if found, else NULL.
 */

hash_element_t *hash_table_delete_element (hash_table_t *hash_table,
    void *key)
{
    unsigned int entry, hash;
    hash_element_t *hash_element, *previous_hash_element;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "Hashtable: %s (%p, %p)\n",
        __FUNCTION__, hash_table, key);

    /* get hash for given key */
    hash = hash_table->key_to_hash (key);

    /* get entry for hash */
    entry = hash_to_entry (hash_table, hash);

    /* search element in this entry */

    hash_element = hash_table->hash_elements[entry];

    /* if entry empty */
    if (hash_element == NULL)
    {
        /* then return failure */
        return NULL;
    }

    /* if our element first in entry */
    if (hash_table->key_compare (hash_element->key_n_data, key) == 
        CONDITION_EQUAL)
    {
        /* then changing entry and deleting element */
        hash_table->hash_elements[entry] = 
            (hash_element_t *) hash_element->next;

        /* Decreasing number of elements */
        hash_table->number_of_elements--;

        return hash_element;
    }

    /* searching equal element */
    do 
    {
        previous_hash_element = hash_element;
        hash_element = (hash_element_t *) hash_element->next;
    } while ((hash_element != NULL) && 
        (hash_table->key_compare (hash_element->key_n_data, key) != 
	    CONDITION_EQUAL));

    /* if not found */
    if (hash_element == NULL)
    {
        /* then return failure */
        return NULL;
    }

    /* changing previous element and deleting found */
    previous_hash_element->next = hash_element->next;

    /* number of elements is decreased */
    hash_table->number_of_elements--;

    return hash_element;
}

hash_table_iterator_t * hash_table_get_iterator (hash_table_t *hash_table)
{
    unsigned int entry;
    
    for (entry = 0; entry < hash_table->limit_entries; entry++)
    {
        if (hash_table->hash_elements[entry] != NULL)
        {
            break;
        }
    }
    
    if (entry == hash_table->limit_entries)
    {
        hash_table->iterator.entry = 0;
        hash_table->iterator.current_element = NULL;
    }
    else
    {
        hash_table->iterator.entry = entry;
        hash_table->iterator.current_element = hash_table->hash_elements[entry];
    }
    
    return &(hash_table->iterator);
}


