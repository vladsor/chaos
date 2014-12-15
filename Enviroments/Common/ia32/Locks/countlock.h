
/**
 * @file                countlock.h
 * @brief               locking. 
 */

#ifndef __STORM_IA32_COUNTLOCK_H__
#define __STORM_IA32_COUNTLOCK_H__

typedef struct
{
    volatile unsigned int value;
    
} countlock_t;

typedef countlock_t * p_countlock_t;

/**
 * @brief           The lock is unlocked.
 */
#define COUNT_UNLOCKED (0)

static inline void count_init (p_countlock_t lock)
{
    lock->value = COUNT_UNLOCKED;
}

static inline void count_down (p_countlock_t lock)
{
    asm volatile 
    (
        "0:  decl %0\n"
        "jns 1f\n"
        "incl %0\n"
        "hlt\n"               /* This one is the key. */
        "jmp 0b\n"
        "1:\n"
        :
            "=m" (lock->value)
        :
            "m" (lock->value)
    );
}

static inline bool count_try_down (p_countlock_t lock)
{
    register int res = 1;
    asm volatile 
    (
        "0:  decl %1\n"
        "jns 1f\n"
        "incl %1\n"
        "movl $0, %0\n"
        "1:\n"
        :
            "=g" (res),
            "=m" (lock->value)
        :
            "m" (lock->value)
    );
    
    return res == 1;
}    

static inline void count_down_interrupt (p_countlock_t lock)
{
    asm volatile 
    (
        "0:  decl %0\n"
        "jns 1f\n"
        "incl %0\n"
        "jmp 0b\n"
        "1:\n"
        :
            "=m" (lock->value)
        :
            "m" (lock->value)
    );
}

static inline void count_up (p_countlock_t lock)
{
    asm volatile 
    (
        "incl %0\n"
        :
            "=m" (lock->value)
        :
            "m" (lock->value)
    );
}

#endif /* !__STORM_IA32_COUNTLOCK_H__ */

