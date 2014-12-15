
#define CONSTRAINT_CURRENT ((constraint_reference_t) 1)

typedef struct
{
    reference_struct_t header;
    
    constraint_reference_t parent;
    list_t childs;

/*
    cpu_max;
    memory_max;
    global_address_space;
    user_address_space;
*/    
    
} constraint_t;

typedef constraint_t * p_constraint;

extern constraint_reference_t constraint_create (constraint_reference_t parent);
extern void constraint_destroy (constraint_reference_t constraint_reference);

