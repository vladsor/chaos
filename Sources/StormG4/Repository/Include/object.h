
#ifdef REPOSITORY_NOT_INLINE

extern p_object_t object_create_static_internal (p_object_t object,
    sequence_t parameters, uint32_t options);

extern void object_destroy_static_internal (p_object_t object);

extern p_object_t object_create_internal (p_class_t object_class, 
    sequence_t object_own_interfaces, p_security_t object_security, 
    sequence_t parameters, uint32_t options);

extern void object_destroy_internal (p_object_t object);


extern p_class_t object_get_class_internal (p_object_t object);

extern p_interface_t object_get_interface_internal (p_object_t object,
    interface_id_t interface_id);

extern p_security_t object_get_security_internal (p_object_t object);

extern void object_set_security_internal (p_object_t object, 
    p_security_t security);

extern void object_invoke_method_internal (p_object_t object, 
    p_interface_t interface, context_t context, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters);

extern void object_add_child_internal (p_object_t object, 
    p_reference_struct_t reference);
extern void object_remove_child_internal (p_object_t object, 
    p_reference_struct_t reference);

#else

#include "../Object/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

