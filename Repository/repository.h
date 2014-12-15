#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <hash_table.h>

typedef uint32_t class_id_t;
typedef class_id_t *p_class_id_t;

typedef uint32_t interface_id_t;
typedef interface_id_t *p_interface_id_t;

typedef uint32_t method_id_t;
typedef method_id_t *p_method_id_t;

typedef uint32_t exception_id_t;
typedef exception_id_t *p_exception_id_t;

#define CID_POOL_LIMIT          (1000)
#define CID_POOL_ENTRIES        (100)

#define IID_POOL_LIMIT          (1000)
#define IID_POOL_ENTRIES        (100)

#define EID_POOL_LIMIT          (1000)
#define EID_POOL_ENTRIES        (100)

#define CID_NONE                (0)
#define CID_EMPTY               (1)
#define IID_NONE                (0)


typedef void *p_void_t;

typedef struct
{
    uint32_t length;
    
    p_void_t data;
} sequence_t;

typedef sequence_t *p_sequence_t;

enum
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,
    INTERFACE_TYPE_REPOSITORY,
};

enum
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

typedef struct
{
    p_void_t object_data;
    p_void_t handle_data;
} context_t;

typedef context_t *p_context_t;

typedef return_t (method_function_t) (void);

typedef struct
{
    uint32_t type;
    uint32_t size;
    uint32_t attribute;
} parameter_t;

enum parameter_type_t
{
    PARAMETER_TYPE_BASE,
    PARAMETER_TYPE_SEQUENCE,
    PARAMETER_TYPE_OBJECT,
    PARAMETER_TYPE_INTERFACE,
};

enum parameter_attribute_t
{
    PARAMETER_ATTRIBUTE_IN,
    PARAMETER_ATTRIBUTE_OUT,
    PARAMETER_ATTRIBUTE_INOUT,
};

typedef struct
{
    HASH_ELEMENT_PART;

    exception_id_t id;

    char name[STRING_MAX_LENGTH];

    uint32_t type;

    uint32_t number_of_references;

} exception_t;

typedef exception_t *p_exception_t;

typedef struct
{
    p_method_function_t function;
    method_id_t id;
    
    char name[STRING_MAX_LENGTH];

    uint32_t number_of_references;
    
    parameter_t return_type;

    uint32_t number_of_parameters;
    p_parameter_t parameters;
    
    uint32_t number_of_exceptions;

    p_exception_t exceptions[0];

} method_t;

typedef method_t *p_method_t;

typedef struct
{
    HASH_ELEMENT_PART;
    
    interface_id_t real_id;
    interface_id_t id;

    char name[STRING_MAX_LENGTH];
    
    uint32_t type;

    uint32_t number_of_references;
    
    p_interface_control_t control;
    
    p_void_t object_data;
    p_void_t handle_data;

    uint32_t number_of_methods;

    p_method_t methods[0];

} interface_t;

typedef interface_t *p_interface_t;

typedef struct
{
    HASH_ELEMENT_PART;

    class_id_t real_id;
    class_id_t id;
    
    char name[STRING_MAX_LENGTH];

    uint32_t type;

    uint32_t number_of_references;

    handle_t repository;

    uint32_t number_of_interfaces;

    p_interface_t interfaces[0];
} class_t;

typedef class_t *p_class;

typedef struct
{
    p_class_t class;
    uint32_t number_of_references;
//    handle_t handles[];

    p_void_t data;
    
    uint32_t number_of_joined_objects;
    p_object_t joined_objects[0];
    
    uint32_t number_of_own_interfaces;
    p_interface_t own_interfaces[];
} object_t;

typedef object_t *p_object_t;

typedef struct
{
    p_object_t object;
    
    p_object_t current_object;
    context_t context;
    p_interface_t interface;
} handle_t;

enum
{
    OBJECT_NONE,
    OBJECT_THIS,
    OBJECT_KERNEL,
    OBJECT_THIS_PROCESS,
    OBJECT_THIS_THREAD,
};

#define HANDLE_NULL         {NULL, NULL}
#define HANDLE_THIS         {(uint32_t *) OBJECT_THIS, NULL}
#define HANDLE_KERNEL       {(uint32_t *) OBJECT_KERNEL, NULL}
#define HANDLE_THIS_PROCESS {(uint32_t *) OBJECT_THIS_PROCESS, NULL}
#define HANDLE_THIS_THREAD  {(uint32_t *) OBJECT_THIS_THREAD, NULL}

extern handle_t repository_object_create (class_t class, uint32_t options,
    uint32_t number_of_joined_objects, handle_t joined_objects[], 
    sequence_t parameters);

enum
{
    CLONE_ONLY_HANDLE,
    CLONE_OPENED_INTERFACE,
};

extern handle_t repository_handle_clone (handle_t handle, uint32_t options);

extern handle_t repository_object_open (handle_t handle, interface_t interface, 
    uint32_t options, sequence_t parameters);

extern void repository_object_close (handle_t handle);
extern void repository_object_destroy (handle_t handle);

typedef struct
{
    interface_id_t interface_id;
    uint32_t interface_type;
    uint32_t number_of_methods;
    method_t *methods[0];
} interface_description_t;
typedef interface_description_t * interface_t;

extern interface_t interface_register (interface_description_t *interface_description);
extern void interface_unregister (interface_t interface);

typedef struct
{
    class_id_t class_id;
    uint32_t class_type;
    uint32_t number_of_interfaces;
    interface_t interfaces[];
    interface_t repository_interface;
} class_description_t;
typedef class_description_t * class_t;
       
extern class_t class_register (class_description_t *class_desscription);
extern void class_unregister (class_t class);
extern void class_add_interfaces (class_t class, 
    uint32_t number_of_interfaces, interface_t interfaces[])
extern void class_delete_interfaces (class_t class, 
    uint32_t number_of_interfaces, interface_t interfaces[])

extern exception_t exception_register (
    exception_description_t *exception_description);
extern void exception_unregister (exception_t exception);

extern return_t repository_init (int argc, char *argv[]);

#endif /* !__REGISTER_H__ */

