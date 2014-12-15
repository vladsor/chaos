#ifndef __INTERFACE_THREAD_H__
#define __INTERFACE_THREAD_H__

#include "Common/thread.h"

#define IID_THREAD 0x00005001

enum
{
    MID_THREAD_CREATE,
    MID_THREAD_NAME_GET,
    MID_THREAD_NAME_SET
};

typedef return_t (thread_create_function_t) (thread_t *thread, 
    p_thread_function_t thread_function, p_void_t parameter);

typedef struct
{
    thread_create_function_t *create;
} thread_interface_t;

#define thread$create(handle,thread,function,parameter) \
    ((thread_interface_t *) ((handle)->functions))->create (\
        (thread), (function), (parameter))

#endif /* !__INTERFACE_THREAD_H__ */

