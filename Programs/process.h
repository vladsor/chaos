#ifndef __INTERFACE_PROCESS_H__
#define __INTERFACE_PROCESS_H__

#define IID_GENERIC_PROCESS 0x00005001

enum
{
};

#define process$create(handle,image)
{
    repository_create_object (handle, image);
}

enum
{
    MID_PROCESS_START,
    MID_PROCESS_STOP,
    
    MID_PROCESS_PAUSE,
    MID_PROCESS_RESUME,

    MID_PROCESS_NAME_GET,
    MID_PROCESS_NAME_SET,
    
    MID_PROCESS_EXIT_CODE_GET,
    MID_PROCESS_EXIT_CODE_SET,
    
    MID_PROCESS_PARAMETERS_GET,
    MID_PROCESS_PARAMETERS_SET
};

typedef struct
{
    thread_create_function_t *create;
} generic_process_interface_t;

#endif /* !__INTERFACE_PROCESS_H__ */

