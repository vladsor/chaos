/* Abstract: Hash table library functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2001 chaos development. */

#ifndef __LIBRARY_HASH_TABLE_FUNCTIONS_H__
#define __LIBRARY_HASH_TABLE_FUNCTIONS_H__

/**
 * @brief       Create new hash table with given number of entries.
 */
extern void hash_table_create (hash_table_t *hash_table, 
    unsigned int limit_hash_entries, key_to_hash_function_t key_to_hash,
    compare_function_t key_compare);

/**
 * @brief       Destroy given hash table
 */
extern void hash_table_destroy (hash_table_t *hash_table, 
    hash_element_destroy_function_t destroy);

/**
 * @brief       Search in hash table for element with given identifier.
 */
extern hash_element_t *hash_table_search_element (hash_table_t *hash_table,
    void *key);

/**
 * @brief       Add to hash table given element.
 */
extern bool hash_table_add_element (hash_table_t *hash_table,
    hash_element_t *new_hash_element);

/**
 * @brief       Delete from hash table element with given identifier.
 */
extern hash_element_t * hash_table_delete_element (hash_table_t *hash_table, 
    void *key);

extern hash_table_iterator_t * hash_table_get_iterator (
    hash_table_t *hash_table);

/**
 * @brief               Get size of hash table.
 * @param limit_hash_entries 
 *                      number of entries in hash table
 */
/*
static inline unsigned int sizeof_hash_table (unsigned int limit_hash_entries)
{
    return (sizeof (hash_table_t) + sizeof (hash_element_t *) * 
        limit_hash_entries);
}
*/
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
unsigned int string_to_hash (void *key);

#endif /* !__LIBRARY_HASH_TABLE_FUNCTIONS_H__ */
