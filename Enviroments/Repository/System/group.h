
typedef struct
{
    reference_struct_t header;
    
    sequence_t objects;
    
} group_t;

typedef group_t * p_group;

//extern p_group_t group_current;
//#define GROUP_CURRENT ((group_reference_t) group_current)

extern group_reference_t group_create_static (p_group_t group);
extern void group_destroy_static (group_reference_t group_reference);

extern group_reference_t group_create (sequence_t objects);
extern void group_destroy (group_reference_t group_reference);

extern object_reference_t group_get_object (interface_id_t interface_id);
