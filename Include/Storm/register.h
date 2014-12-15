#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <hash_table.h>

typedef uint32_t class_id_t;
typedef uint32_t interface_id_t;
typedef uint32_t method_id_t;

#define CID_POOL_LIMIT 1000
#define IID_POOL_LIMIT 1000

#define CID_NONE 0
#define IID_NONE 0

#define CID_STATIC_NONE  0x80000000
#define CID_STATIC_POOL_LIMIT 100

enum
{
    MID_OBJECT_CREATE,
    MID_OBJECT_DESTROY,
  
    NUMBER_OF_OBJECT_CONTROL_METHODS,
};

enum
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,
    INTERFACE_TYPE_CONTROL,
};

enum
{
    CLASS_TYPE_DYNAMIC,
    CLASS_TYPE_STATIC,
};

typedef struct
{
    uint32_t size;
} parameter_t;

typedef struct
{
    void *object_data;
    void *handle_data;
} context_t;

typedef return_t (object_create_function_t) (context_t *context, 
    void *parameters);
typedef return_t (object_destroy_function_t) (context_t *context);

typedef struct 
{
    object_create_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];
  
} object_create_method_t;

typedef struct 
{
    object_destroy_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];
  
} object_destroy_method_t;

typedef struct
{
    object_create_function_t *create;
    object_destroy_function_t *destroy;
} object_control_t;

typedef return_t (method_function_t) (void);

typedef struct
{
    method_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} method_t;

typedef return_t (interface_open_function_t) (context_t *context);
typedef return_t (interface_close_function_t) (context_t *context);

typedef struct
{
    interface_open_function_t *open;
    interface_close_function_t *close;
} interface_control_t;

typedef struct
{
    HASH_ELEMENT_PART;
    
    interface_id_t real_iid;
    interface_id_t iid;
    
    uint32_t type;

    uint32_t number_of_classes;
    
    interface_control_t *control;

    uint32_t number_of_methods;

    method_t *methods[0];

} interface_t;

typedef struct
{
    HASH_ELEMENT_PART;

    class_id_t real_cid;
    class_id_t cid;
    
    uint32_t type;

    uint32_t number_of_objects;

    object_control_t control;

    uint32_t number_of_interfaces;

    interface_t *interfaces[0];
} class_t;

typedef struct
{
    class_t *class;
    context_t context;
    
//    interface_t *interface;
    method_function_t **functions;

} handle_t;

#define HANDLE_HEADER_EMPTY NULL, {NULL, NULL}
#define HANDLE_HEADER_KERNEL (class_t *) UINT32_MAX, {NULL, NULL}
#define HANDLE_RESET(handle) \
    memory_set_uint8 ((uint8_t *) handle, 0, sizeof (handle_t))

extern return_t register_object_create (handle_t *handle, 
    class_id_t real_class_id, void *data);

extern return_t register_handle_clone (handle_t *handle, handle_t *new_handle,
    uint32_t options);

extern return_t register_object_open (handle_t *handle, 
    interface_id_t interface_id);

extern return_t register_object_reopen (handle_t *handle, 
    interface_id_t interface_id);

extern return_t register_object_close (handle_t *handle);

extern return_t register_interface_register (interface_id_t *real_interface_id,
    interface_id_t interface_id, uint32_t interface_type, 
    uint32_t number_of_methods, method_t *methods[], 
    interface_control_t *control);

extern return_t register_interface_unregister (
    interface_id_t real_interface_id);
    
extern return_t register_class_register (class_id_t *real_class_id, 
    class_id_t class_id, uint32_t class_type, uint32_t number_of_interfaces, 
    interface_id_t interface_ids[], interface_id_t class_control_id);

extern return_t register_class_unregister (class_id_t real_class_id);

extern return_t register_init (int argc, char *argv[]);

#endif /* !__REGISTER_H__ */

