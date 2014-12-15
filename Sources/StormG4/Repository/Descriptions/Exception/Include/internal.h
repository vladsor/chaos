
extern p_exception_t exception_create_static_internal (p_exception_t exception);

extern void exception_destroy_static_internal (p_exception_t exception);

extern p_exception_t exception_create_internal (
    p_exception_description_t exception_description);

extern void exception_destroy_internal (p_exception_t exception);

