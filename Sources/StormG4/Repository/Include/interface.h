
#ifdef REPOSITORY_NOT_INLINE

extern p_interface_t interface_create_static_internal (p_interface_t interface);

extern void interface_destroy_static_internal (p_interface_t interface);

extern p_interface_t interface_create_internal (
    p_interface_description_t interface_description, 
    sequence_t interface_methods);
    
extern void interface_destroy_internal (p_interface_t interface);

extern void interface_invoke_method_internal (p_interface_t interface, 
    context_t context, method_id_t method_id, sequence_t return_value, 
    sequence_t parameters);

extern p_interface_t interface_get_current (void);

#else

#include "../Interface/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

