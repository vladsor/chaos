
typedef uint32_t security_id_t;
typedef security_id_t * p_security_id_t;

typedef struct
{
    int access : 1;
    
    int interface_register : 1;
    int interface_unregister : 1;
    
    int class_register : 1;
    int class_unregister : 1;
    
    int object_create : 1;
    int object_destroy : 1;
    
    int handle_open : 1;
    int handle_close : 1;
} generic_acl_t;
/*
typedef struct
{
    int access : 1;
    create
    destroy;
    int : 1 open;
    close;
} acl_t;
*/
typedef struct
{
    HASH_ELEMENT_PART;

    security_id_t id;
    
    char name[STRING_MAX_LENGTH];

    bool is_absolute;
    
    generic_acl_t generic_acl;
//    object_acl_t object_acl;
    
//    sequence_t interface_acls;
} security_t;


extern void security_create (p_security_reference_t security_reference,
    generic_acl, object_acl, interface_acls);
extern void security_destroy (security_reference_t security_reference);

extern bool security_is_absolute (security_reference_t security_reference);
extern void security_get_generic_acl (security_reference_t security_reference);
extern void security_get_object_acl (security_reference_t security_reference);
extern void security_get_interface_acl (security_reference_t security_reference);

