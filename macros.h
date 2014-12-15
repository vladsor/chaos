
typedef struct
{
    cpu_state_t state;
    bool raised;

    uint32_t type;
    uint32_t id;
} exception_info_t;

typedef struct
{
    LIST_NODE_PART;
    
    cpu_state_t state;
    p_exception_info info;
   
} exception_context_t;

enum 
{
    EXCEPTION_TYPE_HARDWARE,
    EXCEPTION_TYPE_SYSTEM,
    EXCEPTION_TYPE_USER,
};

enum
{
    EXCEPTION_INALID_PARAMETERS,
    EXCEPTION_NOT_IMPLEMENTED,
    EXCEPTION_ACCESS_DENIED,
    EXCEPTION_IS_LOCKED,
    EXCEPTION_NOT_ENOUGH_RESOURCES,
    EXCEPTION_INTERNAL_FAULT,
    EXCEPTION_DOUBLE_FAULT,
};

extern void exception_add_handler (p_exception_context_t exception_context);
extern void exception_remove_handler ();
extern void exception_invoke_handler (p_exception_info_t exception_info);

#define TRY \
{ \
    __label__ finaly; \
    exception_context_t context; \
    exception_info_t info; \
    context.state.eip = &&finaly;\
    context.state.esp = cpu_get_esp (); \
    context.info = &info; \
    info.raised = FALSE; \
    exception_add_handler (&context);

#define THROW(exception_info) \
    exception_invoke_handler (exception_info)

#define THROW_SYSTEM(exception_id) \
do { \
    exception_info_t info; \
    info.type = EXCEPTION_TYPE_SYSTEM; \
    info.id = exception_id; \
    exception_invoke_handler (&info); \
} while (0)

#define FINALY

#define CATCH_ALL(name) \
finaly: \
    { \
        p_exception_info_t (name) = &info;\
        exception_remove_handler (); \
        if (info.raised) \
        {
    
#define END_TRY \
        } \
    } \
}

    if (exception_set_handler () == 0)
    {
    }
    else
    {
    }
 
#define CPU_LOAD_STATE(cpu_state)
{ 
asm (
"        movl $0, %eax\n"
"        movw %0 + 44,  %ss\n"
"        movl %0 + 16, %esp\n"
"        movl %0 +  4, %ecx\n"
"        movl %0 +  8, %edx\n"
"        movl %0 + 12, %ebx\n"
"        movl %0 + 20, %ebp\n"
"        movl %0 + 24, %esi\n"
"        movl %0 + 28, %edi\n"
"        movw %0 + 48,  %ds\n"
"        movw %0 + 52,  %es\n"
"        movw %0 + 56,  %fs\n"
"        movw %0 + 60,  %gs\n"
"        movl %0 + 36, %eax\n"
"        pushl %eax\n"  /* saved eflags */
"        movl %0 + 40, %eax\n"
"        pushl %eax\n"  /* saved cs */
"        movl %0 + 32, %eax\n"
"        pushl %eax\n"  /* saved eip */
"        movl %0, %eax\n"
"        iret"
    :
    : "g" (cpu_state));
}


#define CPU_SAVE_STATE(cpu_state)
{
"        movl $0, %eax\n"
"        movl %eax, %0\n"
"        movw  %ss, %0 + 44\n"
"        movl %esp, %0 + 16\n"
"        movl %ecx, %0 +  4\n"
"        movl %edx, %0 +  8\n"
"        movl %ebx, %0 + 12\n"
"        movl %ebp, %0 + 20\n"
"        movl %esi, %0 + 24\n"
"        movl %edi, %0 + 28\n"
"        movw  %ds, %0 + 48\n"
"        movw  %es, %0 + 52\n"
"        movw  %fs, %0 + 56\n"
"        movw  %gs, %0 + 60\n"
"        pushfl\n"  /* save eflags */
"        popl %eax\n"  /* save eflags */
"        movl %eax, %0 + 36\n"
"        movl  %cs, %0 + 40\n"   /* save cs */
"        movl   %1, %0 + 32" /* save eip */
    : "g" (cpu_state));
} 

