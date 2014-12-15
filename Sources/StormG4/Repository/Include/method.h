
#ifdef REPOSITORY_NOT_INLINE

extern p_method_t method_create_static_internal (p_method_t method);

extern void method_destroy_static_internal (p_method_t method);

extern p_method_t method_create_internal (
    p_method_description_t method_description, 
    p_method_function_t method_function);

extern void method_destroy_internal (p_method_t method);

extern void method_invoke_internal (p_method_t method, context_t context,
    sequence_t return_value, sequence_t parameters);

extern void method_invoke_static_internal (p_method_t method,
    sequence_t return_value, sequence_t parameters);

extern p_method_t method_get_current_internal (void);
extern p_method_t method_get_current_invoker_internal (void);    

#else

#include "../Method/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

