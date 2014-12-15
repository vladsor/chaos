
extern p_security_t security_create_static_internal (p_security_t security);
extern void security_destroy_static_internal (p_security_t security);

extern p_security_t security_create_internal (bool security_is_absolute, 
    p_generic_acl_t generic_acl);
extern void security_destroy_internal (p_security_t security);

