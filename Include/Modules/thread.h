#include <Common/thread.h>
#include <Interfaces/thread.h>

extern handle_t handle_thread;

static inline return_t thread_create (thread_t *thread, 
    p_thread_function_t thread_function, p_void_t parameter)
{
    return thread$create (&handle_thread, thread, thread_function, parameter);
}
