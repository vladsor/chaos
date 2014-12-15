enum
{
    COMPUTER_STATE_STOPPED,
    COMPUTER_STATE_RUNNING,
    COMPUTER_STATE_WAITING,
};    

extern computer_reference_t computer_create (cpu_reference_t cpu,
    memory_reference_t memory, security_reference_t security);
    
extern void computer_destroy (computer_reference_t computer_reference);

extern void computer_reset (computer_reference_t computer_reference);
extern void computer_return (void);

#include <Kernel/Common/exception.h>
/*
#define EXCEPTION_TYPE_HARDWARE (0)
#define EXCEPTION_TYPE_SYSTEM   (1)
#define EXCEPTION_TYPE_USER     (2)

#ifndef _ASM

typedef struct
{
    uint32_t            pc;
    uint32_t            type;
    uint32_t            id;
} exception_info_t;

typedef exception_info_t * p_exception_info_t;

typedef struct
{
    LIST_NODE_PART;
    
    bool is_raised;
    p_void_t catch_point;
    uint32_t catch_stack_pointer;

    uint32_t edi, esi, ebp;
    uint32_t ebx, edx, ecx, eax;
    
    uint32_t invoke_stack_pointer;
} exception_context_t;    

typedef exception_context_t * p_exception_context_t;
*/

extern void computer_fire_exception (computer_reference_t computer_reference, 
    p_exception_info_t exception_info);

extern void computer_add_exception_context (
    computer_reference_t computer_reference, p_exception_context_t context);

extern p_exception_context_t computer_remove_exception_context (
    computer_reference_t computer_reference);


extern computer_reference_t computer_get_current (void);

