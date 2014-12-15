
enum
{
    SECURITY_THIS,
    SECURITY_ABSOLUTE,
};

typedef struct
{
    int exception_create : 1;
    int exception_destroy : 1;

    int method_create : 1;
    int method_destroy : 1;
    int method_invoke : 1;
    int method_invoke_static : 1;
    
    int interface_create : 1;
    int interface_destroy : 1;
    
    int class_create : 1;
    int class_destroy : 1;
    int class_set_interfaces : 1;
    int class_get_interfaces : 1;
    int class_get_interface : 1;
    
    int object_create : 1;
    int object_destroy : 1;
    
    int handle_create : 1;
    int handle_destroy : 1;
    
    int security_create : 1;
    int security_destroy : 1;
} generic_acl_t;

typedef generic_acl_t * p_generic_acl_t;

typedef struct
{
    exception_reference_t reference;
    
    int destroy : 1;
} exception_acl_t;

typedef exception_acl_t * p_exception_acl_t;

typedef struct
{
    method_reference_t reference;
    
    int destroy : 1;
    int invoke : 1;
    int invoke_static : 1;
} method_acl_t;

typedef method_acl_t * p_method_acl_t;

typedef struct
{
    interface_reference_t reference;
    
    int destroy : 1;
} interface_acl_t;

typedef interface_acl_t * p_interface_acl_t;

typedef struct
{
    class_reference_t reference;
    
    int destroy : 1;
    int set_interfaces : 1;
    int get_interfaces : 1;
    int get_interface : 1;
} class_acl_t;

typedef class_acl_t * p_class_acl_t;


#include <hash_table.h>

typedef struct
{
    HASH_ELEMENT_PART;

    security_id_t id;
    
    char name[STRING_MAX_LENGTH];

    uint32_t number_of_references;
    bool is_static;

    bool is_absolute;
    
    p_generic_acl_t generic_acl;
    
    sequence_t exception_acls;
    sequence_t method_acls;
    sequence_t interface_acls;
    sequence_t class_acls;
    sequence_t object_acls;
    sequence_t handle_acls;
    
} security_t;

typedef p_security_t * p_security_t;

extern security_reference_t security_create_static (p_security_t security);
extern void security_destroy_static (security_reference_t security);
extern void security_clone_static (security_reference_t security, 
    security_reference_t security, options);

extern security_reference_t security_create (bool security_is_absolute, 
    p_generic_acl_t generic_acl /*, p_object_acl, p_interface_acls*/);

extern void security_destroy (security_reference_t security);

extern security_reference_t security_clone (security_reference_t security, options);

/*
extern bool security_is_absolute (security_reference_t security_reference);
extern void security_get_generic_acl (security_reference_t security_reference);
extern void security_get_object_acl (security_reference_t security_reference);
extern void security_get_interface_acl (security_reference_t security_reference);

*/
