
extern exception_reference_t exception_create_static_internal (p_exception_t exception);

extern void exception_destroy_static_internal (exception_reference_t exception);

extern exception_reference_t exception_create_internal (
    p_exception_description_t exception_description);

extern void exception_destroy_internal (exception_reference_t exception);

