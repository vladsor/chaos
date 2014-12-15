#ifndef __INTERFACE_NAMESPACE_H__
#define __INTERFACE_NAMESPACE_H__

#define INTERFACE_NAMESPACE_ID 0x0003

enum
{
    METHOD_NAMESPACE_BIND_ID,
    METHOD_NAMESPACE_REBIND_ID,
    METHOD_NAMESPACE_RESOLVE_ID,
    METHOD_NAMESPACE_UNBIND_ID,
    
    METHOD_NAMESPACE_NUMBER
};

typedef void (namespace_bind_t) (context_t context, wchar_t *name, 
    reference_t reference);
typedef namespace_bind_t * p_namespace_bind_t;

typedef void (namespace_rebind_t) (context_t context, wchar_t *old_name, 
    wchar_t *new_name);
typedef namespace_rebind_t * p_namespace_rebind_t;

typedef reference_t (namespace_resolve_t) (context_t context, wchar_t *name);
typedef namespace_resolve_t * p_namespace_resolve_t;

typedef void (namespace_unbind_t) (context_t context, wchar_t *name);
typedef namespace_unbind_t * p_namespace_unbind_t;

typedef struct
{
    p_namespace_bind_t bind;
    p_namespace_rebind_t rebind;
    p_namespace_resolve_t resolve;
    p_namespace_unbind_t unbind;

} namespace_interface_table_t;

typedef namespace_interface_table_t * p_namespace_interface_table_t;

static inline handle_reference_t namespace$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_NAMESPACE_ID, seq_empty, 0);
}    

static inline void namespace$handle$destroy (
    handle_reference_t handle)
{
    handle_destroy (handle);
}    

static inline void namespace$bind (handle_reference_t handle, 
    const wchar_t *name, reference_t reference)
{
    uint32_t pars[2] = {(uint32_t) name, (uint32_t) reference};
    sequence_t pars_in_seq = {data: pars, count: 2};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_NAMESPACE_BIND_ID, REFERENCE_NULL,
        pars_in_seq, empty_seq, empty_seq, 0);
}

static inline reference_t namespace$resolve (handle_reference_t handle, 
    const wchar_t *name)
{
    uint32_t pars[1] = {(uint32_t) name};
    sequence_t pars_in_seq = {data: pars, count: 1};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t ret[1] = {(uint32_t) REFERENCE_NULL};
    sequence_t pars_out_seq = {data: ret, count: 1};
    
    handle_invoke_method (handle, METHOD_NAMESPACE_RESOLVE_ID, REFERENCE_NULL,
        pars_in_seq, empty_seq, pars_out_seq, 0);
    
    return (reference_t) ret[0];
}

static inline void namespace$unbind (handle_reference_t handle, 
    const wchar_t *name)
{
    uint32_t pars[1] = {(uint32_t) name};
    sequence_t pars_in_seq = {data: pars, count: 1};

    sequence_t empty_seq = {data: NULL, count: 0};

    handle_invoke_method (handle, METHOD_NAMESPACE_UNBIND_ID, REFERENCE_NULL,
        pars_in_seq, empty_seq, empty_seq, 0);
}

#endif /* !__INTERFACE_NAMESPACE_H__ */

