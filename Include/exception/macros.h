
#define TRY \
({ \
    __label__ finaly; \
    exception_context_t context; \
    exception_info_t info; \
    context.state.irq_cpu_registers.eip = (uint32_t) &&finaly;\
    context.state.irq_cpu_registers.esp = cpu_esp_get (); \
    context.info = &info; \
    context.raised = FALSE; \
    exception_add_handler (thread_get_current (), &context);

#define THROW(exception_info) \
do { \
    exception_invoke_handler (thread_get_current (), exception_info); \
} while (0)

#define THROW_SYSTEM(exception_id) \
({ \
    __label__ throw_label; \
    exception_info_t __info; \
throw_label: \
    memory_set_uint8 ((uint8_t *) &__info, 0, sizeof (__info)); \
    __info.type = EXCEPTION_TYPE_SYSTEM; \
    __info.id = exception_id; \
    __info.pc = (uint32_t) &&throw_label; \
    exception_invoke_handler (thread_get_current (), &__info); \
})

#define FINALY

#define CATCH_ALL(name) \
finaly: \
    { \
        p_exception_info_t (name) = &info;\
        if (context.raised)
    
#define END_TRY \
    } \
})

 

