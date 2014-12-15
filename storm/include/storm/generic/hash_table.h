#ifndef __STORM_GENERIC_HASH_TABLE_H__
#define __STORM_GENERIC_HASH_TABLE_H__

#include <storm/types.h>

/* struct of hash element */
typedef struct
{
  /* pointer to next element in entry */
  struct hash_element_type *next;

  /* value of identifier */
  id_type id;
  
  /* ... */

} hash_element_type;

/* struct of hash table */
typedef struct
{
  /* number of entries */
  unsigned int limit_entries;

  /* number of hash-elements */
  unsigned int number_of_elements;

  /* array of entries */
  hash_element_type *hash_elements[0];
} hash_table_type;


#define HASH_ELEMENT_PART \
  hash_element_type *next; \
  id_type id 

/* create new hash table with given number of entries */
extern void hash_table_create (hash_table_type **hash_table, 
                               unsigned int limit_hash_entries);

/* destroy given hash table */
extern void hash_table_destroy (hash_table_type *hash_table);

/* search in hash table for element with given identifier */
extern hash_element_type *hash_table_search_element (
    hash_table_type *hash_table, id_type id);

/* add in hash table given element */
extern bool hash_table_add_element (hash_table_type *hash_table,
                                    hash_element_type *new_hash_element);

/* delete from hash table element with given identifier */
extern bool hash_table_delete_element (hash_table_type *hash_table, 
                                       id_type id);

#endif /* __STORM_GENERIC_HASH_TABLE_H__ */

