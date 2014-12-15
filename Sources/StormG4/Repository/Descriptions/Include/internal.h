
static inline description_reference_t description_reference_acquire_internal (
    description_reference_t reference)
{
    p_description_reference_struct_t reference_struct = 
        (p_description_reference_struct_t) reference;

    reference_struct->number_of_references++;

    return reference;
}
    
static inline void description_reference_release_internal (
    description_reference_t reference)
{
    p_description_reference_struct_t reference_struct = 
        (p_description_reference_struct_t) reference;

    reference_struct->number_of_references--;
}
    
static inline id_t description_reference_get_id_internal (
    description_reference_t reference)
{
    p_description_reference_struct_t reference_struct = 
        (p_description_reference_struct_t) reference;

    return reference_struct->id;
}
    
