typedef struct
{
    reference_struct_t header;
    
    list_t childs;

    uint64_t data;

    p_class_t class;

/*
    sequence_t own_interfaces;
    sequence_t own_event_supplier_interfaces;
    sequence_t own_event_consumer_interfaces;
*/

    p_security_t security;
//    p_computer_t computer;    
/*
    p_virtual_cpu_t virtual_cpu;
    p_contstraint_t constraint;
*/
    
} object_t;

typedef object_t * p_object_t;
typedef p_object_t * p_p_object;

#if defined (__STORM_KERNEL__)

extern object_reference_t kernel_object;
#define OBJECT_KERNEL (kernel_object)

#else

#define OBJECT_KERNEL (object_get_kernel ())

#endif


