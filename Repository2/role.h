
// Control 
extern 
    role_reference_t 
        role_create 
        (
            scene_reference_t scene_reference,
            object_reference_t object_reference, 
//            interface_reference_t interface_reference,
            interface_id_t interface_id, 
            data_t parameter, 
            uint32_t options
        );

extern 
    void 
        role_destroy 
        (
            role_reference_t role_reference
        );

extern 
    role_reference_t 
        role_clone 
        (
            role_reference_t role_reference, 
            uint32_t options
        );

extern 
    void 
        role_play 
        (
            role_reference_t role_reference,
//            interface_id_t interface_id, 
            method_id_t method_id, 
            uint32_t options
        );

// Get and set methods

data_t role_get_data (role_reference_t role_reference);
void role_set_data (role_reference_t role, data_t data)

/*
extern object_reference_t role_get_object (role_reference_t role_reference);

extern interface_reference_t role_get_interface (
    role_reference_t role_reference);
*/

