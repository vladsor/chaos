#include <Common/exception.h>
#include <Interfaces/exception.h>

extern handle_t handle_exception;

static inline void exception_add_handler (thread_t *thread, 
    p_exception_context_t exception_context)
{
    exception$add_handler (&handle_exception, thread, exception_context);
}

static inline void exception_remove_handler (thread_t *thread)
{
    exception$remove_handler (handle_exception, thread);
}

static inline void exception_invoke_handler (thread_t *thread,
    p_exception_info_t exception_info) NORETURN
{
    exception$invoke_handler (handle_exception, thread, exception_info);
}
