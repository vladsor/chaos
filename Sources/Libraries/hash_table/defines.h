/* Abstract: Defines used by the hash table library. */
/* Author: Vladimir Sorokin */

/* Copyright 2001 chaos development. */

#ifndef __LIBRARY_HASH_TABLE_DEFINES_H__
#define __LIBRARY_HASH_TABLE_DEFINES_H__

#define HASH_ELEMENT_PART                   \
                                            \
    /* pointer to next element in entry */  \
    struct hash_element_t *next;            \
                                            \
    /* value of hash */                     \
    unsigned int hash;                      

#define SIZEOF_HASH_TABLE(entries)          \
    sizeof (hash_table_t) + sizeof (hash_element_t *) * (entries)

#define DECLARE_HASH_TABLE(name, entries)   \
    union                                   \
    {                                       \
        hash_table_t name;                  \
        uint8_t raw_buffer[SIZEOF_HASH_TABLE(entries)];\
    } name;


#endif /* !__LIBRARY_HASH_TABLE_DEFINES_H__ */
