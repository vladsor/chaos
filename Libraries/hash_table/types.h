/* Abstract: Hash table library types. */
/* Author: Vladimir Sorokin */

/* Copyright 2001 chaos development. */


#ifndef __LIBRARY_HASH_TABLE_TYPES_H__
#define __LIBRARY_HASH_TABLE_TYPES_H__

/**
 * @brief
 */
typedef unsigned int (* key_to_hash_function_t) (void *key);

/**
 * @brief       struct of hash element
 */
typedef struct
{
    /**
     * @brief       pointer to next element in entry 
     */
    struct hash_element_t *next;
                                  
    /**
     * @brief       value of hash 
     */
    unsigned int hash;
    
    /**
     * @brief       next is key and some data 
     */
    uint8_t key_n_data[0];

} hash_element_t;

struct hash_table_iterator_t;
struct hash_table_t;

typedef bool (hash_table_iterator_has_next_function_t) (
    struct hash_table_iterator_t *iterator);
typedef hash_element_t * (hash_table_iterator_get_next_function_t) (
    struct hash_table_iterator_t *iterator);

typedef struct
{
    hash_table_iterator_has_next_function_t *has_next;
    hash_table_iterator_get_next_function_t *get_next;
    
    hash_element_t *current_element;
    unsigned int entry;
    struct hash_table_t *hash_table;
} hash_table_iterator_t;

/**
 * @brief       struct of hash table
 */
typedef struct
{
    /**
     * @brief       number of entries in hash table
     */
    unsigned int limit_entries;

    /**
     * @brief       number of hash-elements
     */
    unsigned int number_of_elements;
  
    /**
     * @brief       pointer to function of convertion element's key to hash
     */
    key_to_hash_function_t key_to_hash;

    /**
     * @brief       pointer to function of comparing keys of two elements
     */
    compare_function_t key_compare;

    hash_table_iterator_t iterator;
      
    /**
     *  array of entries
     */
    hash_element_t *hash_elements[0];

} hash_table_t;

typedef return_t (* hash_element_destroy_function_t) (hash_element_t *);

#endif /* !__LIBRARY_HASH_TABLE_TYPES_H__ */
