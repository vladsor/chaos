
#ifdef REPOSITORY_NOT_INLINE

extern p_class_t class_create_static_internal (p_class_t class);

extern void class_destroy_static_internal (p_class_t class);

extern p_class_t class_create_internal (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository);
    
extern void class_destroy_internal (p_class_t class);

extern void class_set_interfaces_internal (p_class_t class, 
    sequence_t class_interfaces);
    
extern sequence_t class_get_interfaces_internal (p_class_t class);

extern p_interface_t class_get_interface_internal (p_class_t class, 
    interface_id_t interface_id);

extern void class_invoke_method_internal (p_class_t class, 
    p_interface_t interface, context_t context, method_id_t method_id, 
    sequence_t parameters, sequence_t return_value);
#else

#include "../Class/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */
