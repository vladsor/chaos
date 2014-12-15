/*
enum
{
    SECURITY_CURRENT,
    SECURITY_ABSOLUTE,
};
*/

typedef struct
{
    int method_create : 1;
    int method_destroy : 1;
    int method_invoke : 1;
    
    int interface_create : 1;
    int interface_destroy : 1;
    
    int class_create : 1;
    int class_destroy : 1;
    
    int object_create : 1;
    int object_destroy : 1;
    
    int handle_create : 1;
    int handle_destroy : 1;
    
    int security_create : 1;
    int security_destroy : 1;
    
    int : 19;
} generic_acl_t PACKED;

typedef generic_acl_t * p_generic_acl_t;

typedef struct
{
    method_reference_t reference;
    
    int destroy : 1;
    int invoke : 1;
    
    int : 30;

} method_acl_t PACKED;

typedef method_acl_t * p_method_acl_t;

typedef struct
{
    interface_reference_t reference;
    
    int destroy : 1;
    
    int : 31;
} interface_acl_t PACKED;

typedef interface_acl_t * p_interface_acl_t;

typedef struct
{
    class_reference_t reference;
    
    int destroy : 1;
    int set_interfaces : 1;
    int get_interfaces : 1;
    int get_interface : 1;
    
    int : 28;
} class_acl_t PACKED;

typedef class_acl_t * p_class_acl_t;

typedef struct
{
    object_reference_t object;
    
    int destroy : 1;

    int : 31;
} object_acl_t PACKED;

typedef object_acl_t * p_object_acl_t;

typedef struct
{
    handle_reference_t handle;
    
    int destroy : 1;

    int : 31;
} handle_acl_t PACKED;

typedef handle_acl_t * p_handle_acl_t;


typedef struct
{
    object_reference_t object;
    interface_reference_t interface;
    method_reference_t method;
    
    uint64_t data;
} user_acl_t;

typedef struct
{
    reference_struct_t header;

    bool is_absolute;
    
    p_generic_acl_t generic_acl;
    
    sequence_t exception_acls;
    sequence_t method_acls;
    sequence_t interface_acls;
    sequence_t class_acls;
    sequence_t object_acls;
    sequence_t handle_acls;
    
    sequence_t user_acls;
    
} security_t;

typedef security_t * p_security_t;

#if defined (__STORM_KERNEL__)

extern security_t security_absolute;
#define SECURITY_ABSOLUTE ((security_reference_t) &security_absolute)

#endif

extern security_reference_t security_create_static (p_security_t security);
extern void security_destroy_static (security_reference_t security);

extern void security_clone_static (security_reference_t security, 
    security_reference_t new_security, uint32_t options);

extern security_reference_t security_create (bool security_is_absolute, 
    p_generic_acl_t generic_acl/*, sequence_t exception_acls, 
    sequence_t method_acls, sequence_t interface_acls, sequence_t class_acls,
    sequence_t object_acls, sequence_t handle_acls, sequence_t user_acls*/);

extern void security_destroy (security_reference_t security);

extern security_reference_t security_get_current (void);

extern security_reference_t security_clone (security_reference_t security, 
    uint32_t options);

/*
extern bool security_is_absolute (security_reference_t security_reference);
extern void security_get_generic_acl (security_reference_t security_reference);
extern void security_get_object_acl (security_reference_t security_reference);
extern void security_get_interface_acl (security_reference_t security_reference);

*/
