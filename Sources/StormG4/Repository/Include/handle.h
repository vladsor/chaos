
#ifdef REPOSITORY_NOT_INLINE

extern p_handle_t handle_create_static_internal (p_handle_t handle, 
     sequence_t parameters, uint32_t options);

extern void handle_destroy_static_internal (p_handle_t handle);

extern void handle_clone_static_internal (p_handle_t handle, 
    p_handle_t new_handle, uint32_t options);

extern p_handle_t handle_create_internal (p_object_t object, 
    interface_id_t interface_id, sequence_t parameters, uint32_t options);

extern void handle_destroy_internal (p_handle_t handle);
     
extern p_handle_t handle_clone_internal (p_handle_t handle, 
    uint32_t options);

extern void handle_invoke_method_internal (p_handle_t handle, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters);

#else

#include "../Handle/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

