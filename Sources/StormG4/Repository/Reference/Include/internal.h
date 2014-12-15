#ifndef REPOSITORY_REFERENCE_INTERNAL_H
#define REPOSITORY_REFERENCE_INTERNAL_H

extern uint32_t magic_number_table[];

static inline reference_t reference_create_internal (
    p_reference_struct_t reference_struct, unsigned int reference_type)
{
    reference_t reference = (reference_t) reference_struct;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference_struct, reference_type);
    
    spin_init (&reference_struct->lock);
    atomic_uint32_write (&reference_struct->number_of_references, 1);

    reference_struct->type = reference_type;
    reference_struct->magic_number = magic_number_table[reference_type];
    reference_struct->owner = OBJECT_CURRENT;
    
    object_add_child_internal (reference_struct->owner, reference);
    
    return reference;
}

static inline void reference_destroy_internal (reference_t reference)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;

    object_remove_child_internal (reference_struct->owner, reference);
    
    reference_struct->magic_number = REFERENCE_MAGIC_NUMBER_NULL;
}

static inline reference_t reference_acquire_internal (reference_t reference)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;

    atomic_uint32_increment (&reference_struct->number_of_references);
    
    return reference;   
}

static inline void reference_release_internal (reference_t reference)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;
    
    atomic_uint32_decrement (&reference_struct->number_of_references);
    
/*    
    if (reference_struct->number_of_references == 0)
    {
        reference_destroy_internal (reference);
    }
*/
}

static inline uint32_t reference_get_type_internal (reference_t reference UNUSED)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;
    
    return reference_struct->type;
}

static inline object_reference_t reference_get_owner_internal (
    reference_t reference)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;
    
    return reference_struct->owner;
}
    
static inline uint32_t reference_get_number_of_references_internal (
    reference_t reference)
{
    p_reference_struct_t reference_struct = (p_reference_struct_t) reference;
    
    return atomic_uint32_read (&reference_struct->number_of_references);
}    

static inline bool reference_is_nill_internal (reference_t reference)
{
    return reference == REFERENCE_NULL;
}
    
static inline bool reference_is_exists_internal (reference_t reference)
{
    return reference != REFERENCE_NULL;
}
    
static inline bool reference_equals_internal (reference_t reference, 
    reference_t reference2)
{
    return reference == reference2;
}    

#endif /* !REPOSITORY_REFERENCE_INTERNAL_H */

