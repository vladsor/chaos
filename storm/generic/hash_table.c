
/* Define this as TRUE if you are debugging this module. */

#define DEBUG           FALSE


#include <storm/generic/hash_table.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>


/*
  FUNCTION:     get_hash_value
  DESCRIPTION:  calculate hash key for given identifier
  ARGUMENTS:    hash_table - pointer to hash table, id - given identifier
  RETURN VALUE: hash key
*/

static inline unsigned int get_hash_value (hash_table_type *hash_table, 
                                           id_type id)
{
  /* hash-function simply the rest of division on number of entries */
  return (id % hash_table->limit_entries);
}


/*
  FUNCTION:     hash_table_create
  DESCRIPTION:  create new hash table with given number of entries
  ARGUMENTS:    hash_table - pointer to hash table,
                limit_hash_entries - number of entries
  RETURN VALUE: none
*/

void hash_table_create (hash_table_type **hash_table, 
                        unsigned int limit_hash_entries)
{
  /* allocate memory for hash table. */
  *hash_table = (hash_table_type *) memory_global_allocate
    (sizeof (hash_element_type *) * limit_hash_entries + 
     sizeof (unsigned int));

  /* initialising hash table */
  (*hash_table)->limit_entries = limit_hash_entries;

  /* number of elements is zero */
  (*hash_table)->number_of_elements = 0;

  /* mark all entries as empty (e.g. NULL = 0). */
  memory_set_u8 ((u8 *) (*hash_table)->hash_elements, 0,
    sizeof (hash_element_type *) * limit_hash_entries);
}


/*
  FUNCTION:     hash_table_destroy
  DESCRIPTION:  destroy diven hash table
  ARGUMENTS:    hash_table - pointer to hash table,
  RETURN VALUE: none
*/

void hash_table_destroy (hash_table_type *hash_table)
{
  hash_element_type *current_element, *temporary_element;
  unsigned int index;

  /* clearing hash table */
  /* for earch entry */
  for (index = 0 ; index < hash_table->limit_entries ; index++)
  {
    current_element = (hash_element_type *) hash_table->hash_elements[index];

    while (current_element != NULL)
    {
      temporary_element = current_element;
      current_element = (hash_element_type *) current_element->next;

      memory_global_deallocate (temporary_element);
    }
  }

  /* dealocate memory under hash table. */
  memory_global_deallocate (hash_table);
}


/*
  FUNCTION:     hash_table_search_element
  DESCRIPTION:  search in hash table for element with given identifier
  ARGUMENTS:    hash_table - pointer to hash table, id - given identifier
  RETURN VALUE: if found then pointer to found element, else NULL
*/

hash_element_type *hash_table_search_element (hash_table_type *hash_table,
                                              id_type id)
{
  hash_element_type *node;

  /* searching entry in hash table */
  node = (hash_element_type *) hash_table->hash_elements
                               [get_hash_value (hash_table, id)];

  while (node != NULL && node->id != id)
  {
    node = (hash_element_type *) node->next;
  }

  /* returning or found element or NULL */
  return node;
}


/*
  FUNCTION:     hash_table_add_element
  DESCRIPTION:  add given element to hash table
  ARGUMENTS:    hash_table - pointer to hash table,
                new_hash_element - added element
  RETURN VALUE: TRUE - if successful, FALSE - otherwise
*/

bool hash_table_add_element (hash_table_type *hash_table,
                             hash_element_type *new_hash_element)
{
  unsigned int index;

  /* search hash key for added element */
  index = get_hash_value (hash_table, new_hash_element->id);

  /* adding new element at the begin of entry */
  (hash_element_type *)
 new_hash_element->next = 
      hash_table->hash_elements[index];
			       
  hash_table->hash_elements[index] = new_hash_element;

  /* number of elements is increased */
  hash_table->number_of_elements++;

  return TRUE;
}

/*
  FUNCTION:     hash_table_delete_element
  DESCRIPTION:  delete from hash table element with given identifier
  ARGUMENTS:    hash_table - pointer to hash table, id - given identifier
  RETURN VALUE: TRUE - if successful, FALSE - otherwise
*/

bool hash_table_delete_element (hash_table_type *hash_table,
			        id_type id)
{
  unsigned int index;
  hash_element_type *hash_element, *previous_hash_element;

  /* search hash key for given identifier */
  index = get_hash_value (hash_table, id);

  /* search entry for hash table */
  hash_element = hash_table->hash_elements[index];

  /* if entry empty */
  if (hash_element == NULL)
  {
    /* then return failure */
    return FALSE;
  }

  /* if our element first in entry */
  if (hash_element->id == id)
  {
    /* then changing entry and deleting element */
    hash_table->hash_elements[index] = (hash_element_type *) hash_element->next;
    memory_global_deallocate (hash_element);

    /* number of elements is decreased */
    hash_table->number_of_elements--;

    return TRUE;
  }

  /* searching equal element */
  do 
  {
    previous_hash_element = hash_element;
    hash_element = (hash_element_type *) hash_element->next;
  } while (hash_element != NULL && hash_element->id != id);

  /* if not found */
  if (hash_element == NULL)
  {
    /* then return failure */
    return FALSE;
  }

  /* changing previous element and deleting found */
  previous_hash_element->next = hash_element->next;
  memory_global_deallocate (hash_element);

  /* number of elements is decreased */
  hash_table->number_of_elements--;

  return TRUE;
}

