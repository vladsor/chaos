
#define INTERFACE_FLAT_NAMESPACE_ID 0x0005

enum
{
    NAME_TYPE_NONE,
    NAME_TYPE_REFERENCE,
    NAME_TYPE_INTERNAL_NAMESPACE,
    NAME_TYPE_EXTERNAL_NAMESPACE,
    NAME_TYPE_LINK,
};    

enum
{
    METHOD_FLAT_NAMESPACE_ADD_ENTRY_ID,
    METHOD_FLAT_NAMESPACE_GET_ENTRY_ID,
    METHOD_FLAT_NAMESPACE_DELETE_ENTRY_ID,
    METHOD_FLAT_NAMESPACE_LIST_ENTRIES_ID,
    
    METHOD_FLAT_NAMESPACE_NUMBER
};

typedef void (flat_namespace_add_entry_t) (context_t context, 
    wchar_t *name, reference_t reference, uint32_t type);
typedef flat_namespace_add_entry_t * p_flat_namespace_add_entry_t;
        
typedef reference_t (flat_namespace_get_entry_t) (context_t context, 
    wchar_t *name, p_uint32_t type);
typedef flat_namespace_get_entry_t * p_flat_namespace_get_entry_t;
    
typedef void (flat_namespace_delete_entry_t) (context_t context, 
    wchar_t *name);
typedef flat_namespace_delete_entry_t * p_flat_namespace_delete_entry_t;
        
typedef uint32_t (flat_namespace_list_entries_t) (context_t context, 
    sequence_t names, uint32_t start);
typedef flat_namespace_list_entries_t * p_flat_namespace_list_entries_t;

typedef struct
{
    p_flat_namespace_add_entry_t add_entry;

    p_flat_namespace_get_entry_t get_entry;
    
    p_flat_namespace_delete_entry_t delete_entry;

    p_flat_namespace_list_entries_t list_entries;

} flat_namespace_interface_table_t;

typedef flat_namespace_interface_table_t * p_flat_namespace_interface_table_t;

static inline handle_reference_t flat_namespace$handle$create (
    object_reference_t object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_FLAT_NAMESPACE_ID, empty_seq, 0);
}    

static inline void flat_namespace$add_entry (handle_reference_t handle, 
    wchar_t *name, reference_t reference, uint32_t type)
{
    uint32_t pars[3] = {(uint32_t) name, (uint32_t) reference, type};
    sequence_t pars_in_seq = {data: pars, count: 3};
    
    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_FLAT_NAMESPACE_ADD_ENTRY_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, empty_seq, 0);
}

static inline reference_t flat_namespace$get_entry (handle_reference_t handle, 
    wchar_t *name, p_uint32_t type)
{
    uint32_t pars[2] = {(uint32_t) name, (uint32_t) type};
    sequence_t pars_in_seq = {data: pars, count: 2};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};

    handle_invoke_method (handle, METHOD_FLAT_NAMESPACE_GET_ENTRY_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, pars_out_seq, 0);
        
    return (reference_t) ret;
}

static inline void flat_namespace$delete_entry (handle_reference_t handle, 
    wchar_t *name)
{
    uint32_t pars[1] = {(uint32_t) name};
    sequence_t pars_in_seq = {data: pars, count: 1};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_FLAT_NAMESPACE_DELETE_ENTRY_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, empty_seq, 0);
}

static inline uint32_t flat_namespace$list_entries (handle_reference_t handle, 
    sequence_t names UNUSED, uint32_t start UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_FLAT_NAMESPACE_LIST_ENTRIES_ID, 
        REFERENCE_NULL, empty_seq, empty_seq, empty_seq, 0);
    
    return 0;
}

