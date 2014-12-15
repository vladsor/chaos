
#ifndef __INTERFACE_NAMESPACE_H__
#define __INTERFACE_NAMESPACE_H__

#define IID_NAMESPACE 0x00000B01

enum
{
    NAMESPACE_RETURN_INVALID_NAME = 100,
    NAMESPACE_RETURN_NOT_NAMESPACE,
    NAMESPACE_RETURN_NOT_HANDLE,
    NAMESPACE_RETURN_NAME_NOT_EXISTS,
};

enum
{
    MID_NAMESPACE_BIND,
    MID_NAMESPACE_BIND_NAMESPACE,
    MID_NAMESPACE_REBIND,
    MID_NAMESPACE_RESOLVE,
    MID_NAMESPACE_UNBIND,
    
    NUMBER_OF_NAMESPACE_METHODS
};

typedef void (namespace_bind_function_t) (context_t *context, 
    char *name, handle_t *handle);
typedef void (namespace_bind_namespace_function_t) (context_t *context, 
    char *name, handle_t *handle);
typedef void (namespace_rebind_function_t) (context_t *context, 
    char *old_name, char *new_name);
typedef void (namespace_resolve_function_t) (context_t *context, 
    char *name, handle_t *handle);
typedef void (namespace_unbind_function_t) (context_t *context, 
    char *name);

typedef struct
{
    namespace_bind_function_t *bind;
    namespace_bind_namespace_function_t *bind_namespace;
    namespace_rebind_function_t *rebind;
    namespace_resolve_function_t *resolve;
    namespace_unbind_function_t *unbind;
} namespace_interface_t;

typedef struct
{
    namespace_bind_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} namespace_bind_method_t;

typedef struct
{
    namespace_bind_namespace_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} namespace_bind_namespace_method_t;

typedef struct
{
    namespace_rebind_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} namespace_rebind_method_t;

typedef struct
{
    namespace_resolve_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} namespace_resolve_method_t;

typedef struct
{
    namespace_unbind_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} namespace_unbind_method_t;

typedef struct
{
    char *name;
    handle_t *handle;
} namespace_bind_parameters_t;

#define NAMESPACE_BIND_METHOD(function) \
    (&(function)), \
    (MID_NAMESPACE_BIND), \
    (sizeof (namespace_bind_parameters_t)), \
    (2), \
    { \
        {sizeof (char *)}, \
        {sizeof (handle_t *)}, \
    }

typedef struct
{
    char *name;
    handle_t *handle;
} namespace_bind_namespace_parameters_t;

#define NAMESPACE_BIND_NAMESPACE_METHOD(function) \
    (&(function)), \
    (MID_NAMESPACE_BIND_NAMESPACE), \
    (sizeof (namespace_bind_namespace_parameters_t)), \
    (2), \
    { \
        {sizeof (char *)}, \
        {sizeof (handle_t *)}, \
    }

typedef struct
{
    char *old_name;
    char *new_name;
} namespace_rebind_parameters_t;
    
#define NAMESPACE_REBIND_METHOD(function) \
    (&(function)), \
    (MID_NAMESPACE_REBIND), \
    (sizeof (namespace_rebind_parameters_t)), \
    (2), \
    { \
        {sizeof (char *)}, \
        {sizeof (char *)}, \
    }

typedef struct
{
    char *name;
    handle_t *handle;
} namespace_resolve_parameters_t;

#define NAMESPACE_RESOLVE_METHOD(function) \
    (&(function)), \
    (MID_NAMESPACE_RESOLVE), \
    (sizeof (namespace_resolve_parameters_t)), \
    (2), \
    { \
        {sizeof (char *)}, \
        {sizeof (handle_t *)}, \
    }

typedef struct
{
    char *name;
} namespace_unbind_parameters_t;

#define NAMESPACE_UNBIND_METHOD(function) \
    (&(function)), \
    (MID_NAMESPACE_UNBIND), \
    (sizeof (namespace_unbind_parameters_t)), \
    (1), \
    { \
        {sizeof (char *)}, \
    }

#define namespace$bind(kh,name,handle) \
    ((namespace_interface_t *) ((kh)->functions))->bind ( \
        &((kh)->context), \
        (name), (handle))

#define namespace$bind_namespace(kh,name,handle) \
    ((namespace_interface_t *) ((kh)->functions))->bind_namespace ( \
        &((kh)->context), \
        (name), (handle))

#define namespace$rebind(kh,old_name,new_name) \
    ((namespace_interface_t *) ((kh)->functions))->rebind ( \
        &((kh)->context), \
        (old_name), (new_name))

#define namespace$resolve(kh,name,handle) \
    ((namespace_interface_t *) ((kh)->functions))->resolve ( \
        &((kh)->context), \
        (name), (handle))

#define namespace$unbind(kh,name) \
    ((namespace_interface_t *) ((kh)->functions))->unbind ( \
        &((kh)->context), \
        (name))


#endif /* !__INTERFACE_NAMESPACE_H__ */

