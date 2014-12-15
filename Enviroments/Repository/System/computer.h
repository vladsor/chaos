typedef struct
{
    p_handle_t handle;
    p_object_t object;
    p_class_t class;
    p_interface_t interface;
    p_method_t method;

    sequence_t parameters_in;
    sequence_t parameters_inout;
    sequence_t parameters_out;

} invoke_record_t;    

#include <list.h>

typedef struct
{
    list_node_t node;
    
    p_void_t computer;
} computer_node_t;    

typedef computer_node_t * p_computer_node_t;

struct computer_struct;
typedef struct computer_struct computer_t;
typedef computer_t * p_computer_t;

struct computer_struct
{
    volatile uint32_t state;
    
    p_cpu_t cpu;
    p_memory_t memory;
    p_security_t security;
    
    p_task_state_t task_state;
    p_uint8_t stack;
    
    p_uint8_t user_stack_virtual;
    p_uint8_t user_stack_physical;

    invoke_record_t invoke_stack[100];
    volatile uint32_t invoke_top;
    
    list_t exception_context_stack;
    uint32_t exception_top;
    
    p_computer_t upper;
    p_computer_t nested;

    computer_node_t node;
    
    bool upper_is_sync;
    bool nested_is_sync;
};    


#if defined (__STORM_KERNEL__)
extern computer_t computer_kernel;
#define COMPUTER_KERNEL ((computer_reference_t) &computer_kernel)

extern volatile p_computer_t computer_current;

#define COMPUTER_CURRENT \
                        ((computer_reference_t) computer_current)
                        
#define CPU_CURRENT     ((cpu_reference_t) computer_current->cpu)
#define MEMORY_CURRENT  ((memory_reference_t) computer_current->memory)
#define SECURITY_CURRENT \
                        ((security_reference_t) computer_current->security)

#define METHOD_CURRENT ((method_reference_t) \
    computer_current->invoke_stack[computer_current->invoke_top - 1].method)

#define INTERFACE_CURRENT ((interface_reference_t) \
    computer_current->invoke_stack[computer_current->invoke_top - 1].interface)

#define CLASS_CURRENT ((class_reference_t) \
    computer_current->invoke_stack[computer_current->invoke_top - 1].class)

#define OBJECT_CURRENT ((object_reference_t) \
    computer_current->invoke_stack[computer_current->invoke_top - 1].object)

#define HANDLE_CURRENT ((handle_reference_t) \
    computer_current->invoke_stack[computer_current->invoke_top - 1].handle)

#else
 /* defined (__STORM_KERNEL__)
 */

#define COMPUTER_CURRENT (computer_get_current ())
#define CPU_CURRENT (cpu_get_current ())
#define MEMORY_CURRENT  ((memory_reference_t) NULL)
#define SECURITY_CURRENT (security_get_current ())

#define OBJECT_CURRENT (object_get_current ())

#endif

