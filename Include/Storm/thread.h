#ifndef __STORM_THREAD_H__
#define __STORM_THREAD_H__

#include <Common/thread.h>

extern return_t thread_init (int argc, char *argv[], char **envp);
extern return_t thread_create (thread_t *thread, 
    p_thread_function_t thread_function, p_void_t parameter);

extern thread_t *thread_get_current (void);
extern return_t thread_lock (thread_t *thread);
extern return_t thread_unlock (thread_t *thread);
extern void thread_yield (void);
extern return_t thread_name_set (thread_t *thread, char *name);
extern return_t thread_name_get (thread_t *thread, char *name);

#endif /* !__STORM_THREAD_H__ */
