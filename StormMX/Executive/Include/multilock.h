/**
 * @file                multilock.h
 * @brief               locking. 
 */

#ifndef __STORM_THREAD_MULTILOCK_H__
#define __STORM_THREAD_MULTILOCK_H__

typedef uint32_t multilock_t;

/**
 * @brief               The setting of a lock.
 */
enum multilock_t
{
    /**
     * @brief           The lock is unlocked.
     */
    MULTI_UNLOCKED = 0,

    /**
     * @brief           The lock is locked.
     */
    MULTI_LOCKED = -2,
    
    MULTI_WRITE_LOCKED = -1,
};

/** 
 * @brief               Get the lock. 
 * @param lock          The lock to get.
 */
static inline void multi_read_lock (multilock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl %3, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl %2, %%eax\n"
                  "jbe 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:\n"
                  "incl %%eax\n"
                  "movl %%eax, %0"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "n" (MULTI_UNLOCKED),
                  "n" (MULTI_LOCKED),
                  "bcdDS" (*lock));
}

static inline void multi_write_lock (multilock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl %4, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl %3, %%eax\n"
                  "je 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:\n"
                  "movl %2, %0"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "n" (MULTI_WRITE_LOCKED),
                  "n" (MULTI_UNLOCKED),
                  "n" (MULTI_LOCKED),
                  "bcdDS" (*lock));
}

/**
 * @brief               Get the look, from code that MAY BE run from
 *                      within an interrupt handler. 
 * @param lock          The lock to get.
 *
 */
/*
static inline void spin_lock_interrupt (spinlock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl %1, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl %1, %%eax\n"
                  "je 0b\n"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "n" (SPIN_LOCKED),
                  "bcdDS" (*lock));
}
*/
/**
 * @brief               Unlock a spinlock which has previously been 
 *                      locked with spin_lock. 
 * @param lock          The lock to unlock.
 */
static inline void multi_read_unlock (multilock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl %3, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl %2, %%eax\n"
                  "jne 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:\n"
                  "decl %%eax\n"
                  "movl %%eax, %0"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "n" (MULTI_UNLOCKED),
                  "n" (MULTI_LOCKED),
                  "bcdDS" (*lock));
}

static inline void multi_write_unlock (multilock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl %3, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl %3, %%eax\n"
                  "jne 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:\n"
                  "movl %2, %0"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "n" (MULTI_UNLOCKED),
                  "n" (MULTI_LOCKED),
                  "bcdDS" (*lock));
}

#endif /* !__STORM_THREAD_MULTI_H__ */

