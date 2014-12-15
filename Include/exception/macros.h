/*
    __context__.catch_point = &&try_label; \
    __context__.catch_stack_pointer = cpu_esp_get (); \
    cpu_flags_save (__context__.eflags); \
    asm  \
    ( \
        "movl %%edi, %0\n" \
        "movl %%esi, %1\n" \
        "movl %%ebp, %2\n" \
        "movl %%ebx, %3\n" \
        "movl %%edx, %4\n" \
        "movl %%ecx, %5\n" \
        "movl %%eax, %6\n" \
            :   "=m" (__context__.edi), \
                "=m" (__context__.esi), \
                "=m" (__context__.ebp), \
                "=m" (__context__.ebx), \
                "=m" (__context__.edx), \
                "=m" (__context__.ecx), \
                "=m" (__context__.eax) \
    ); \
    __label__ try_label; \
try_label: \
*/

#define EXCEPTION_TRY \
do { \
    volatile exception_context_t __context__; \
    computer_add_exception_context (COMPUTER_CURRENT, \
        (p_exception_context_t) &__context__); \
    if (!__context__.is_raised)
    
#define EXCEPTION_THROW(exception_info) \
do { \
    compiter_fire_exception (COMPUTER_CURRENT, exception_info); \
} while (0)

#define EXCEPTION_THROW_SYSTEM(exception_id)  \
({ \
    __label__ throw_label; \
    exception_info_t __info; \
throw_label: \
    memory_clear (&__info, sizeof (__info)); \
    __info.type = EXCEPTION_TYPE_SYSTEM; \
    __info.id = exception_id; \
    __info.pc = (uint32_t) &&throw_label; \
    computer_fire_exception (COMPUTER_CURRENT, &__info); \
})

#define EXCEPTION_FINALY

#define EXCEPTION_CATCH_ALL(name) \
    else \
    { \
        exception_info_t name UNUSED;
    
#define EXCEPTION_END_TRY \
    } \
    if (!__context__.is_raised) \
    { \
        computer_remove_exception_context (COMPUTER_CURRENT); \
    } \
} while (0)

 

