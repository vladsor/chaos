
#ifndef __ENVIROMENT_COMMON_IA32_ATOMIC_UINT32_H_
#define __ENVIROMENT_COMMON_IA32_ATOMIC_UINT32_H_

#ifdef CONFIG_SMP
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
typedef struct { volatile uint32_t value; } atomic_uint32_t;

#define ATOMIC_UINT32_INIT(i) { (i) }

/**
 * @brief               Read atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * @return              Value of variable
 * 
 * Atomically reads the value of variable.
 */ 
#define atomic_uint32_read(variable)   ((variable)->value)

/**
 * @brief               Set atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * @param i             Required value
 * 
 * Atomically sets the value of v to i.
 */ 
#define atomic_uint32_write(variable,i)      (((variable)->value) = (i))

/**
 * @brief               Add integer to atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * @param i             Integer value to add
 * 
 * Atomically adds i to variable.
 */
static inline void atomic_uint32_add (atomic_uint32_t *variable, uint32_t i)
{
    asm volatile (
        LOCK "addl %1, %0"
        :"=m" (variable->value)
        :"ir" (i), "m" (variable->value));
}

/**
 * @brief               Subtract the atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * @param i             Integer value to subtract
 * 
 * Atomically subtracts i from variable.
 */
static inline void atomic_uint32_subtract (atomic_uint32_t *variable, 
    uint32_t i)
{
    asm volatile (
        LOCK "subl %1, %0"
        :"=m" (variable->value)
        :"ir" (i), "m" (variable->value));
}

/**
 * @brief               Increment atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * 
 * Atomically increments variable by 1.
 */ 
static inline void atomic_uint32_increment (atomic_uint32_t *variable)
{
    asm volatile (
        LOCK "incl %0"
        :"=m" (variable->value)
        :"m" (variable->value));
}

/**
 * @brief               Decrement atomic variable
 * @param variable      Pointer of type atomic_uint32_t
 * 
 * Atomically decrements variable by 1.
 */ 
static inline void atomic_uint32_decrement (atomic_uint32_t *variable)
{
    asm volatile (
        LOCK "decl %0"
        :"=m" (variable->value)
        :"m" (variable->value));
}

static inline void atomic_uint32_clear (atomic_uint32_t *variable, 
    uint32_t mask)
{
    asm volatile (
        LOCK "andl %0, %1"
        :
        : "r" (~(mask)), 
          "m" (variable->value)
        : "memory");
}

static inline void atomic_uint32_set (atomic_uint32_t *variable, 
    uint32_t mask)
{
    asm volatile (
        LOCK "orl %0, %1"
        :
        : "r" (mask), 
          "m" (variable->value)
        : "memory");
}

static inline void atomic_uint32_toggle (atomic_uint32_t *variable, 
    uint32_t mask)
{
    asm volatile (
        LOCK "xorl %0, %1"
        :
        : "r" (mask), 
          "m" (variable->value)
        : "memory");
}


/**
 * @brief               Subtract value from variable and test result.
 * @param variable      Pointer of type atomic_uint32_t
 * @param i             Integer value to subtract
 * 
 * Atomically subtracts i from v and returns
 * true if the result is zero, or false for all
 * other cases.  
 */
static inline int atomic_uint32_subtract_and_test (atomic_uint32_t *variable,
    uint32_t i)
{
    unsigned char c;

    asm volatile (
        LOCK "subl %2,%0; sete %1"
        : "=m" (variable->value), "=qm" (c)
        : "ir" (i), "m" (variable->value)
        : "memory");
		
    return c;
}

/**
 * @brief               Increment and test.
 * @param variable      Pointer of type atomic_uint32_t
 * 
 * Atomically increments v by 1
 * and returns true if the result is zero, or false for all
 * other cases.  Note that the guaranteed
 * useful range of an atomic_uint32_t is only 24 bits.
 */ 
static inline int atomic_uint32_increment_and_test (atomic_uint32_t *variable)
{
    unsigned char c;

    asm volatile (
        LOCK "incl %0; sete %1"
        : "=m" (variable->value), "=qm" (c)
        : "m" (variable->value) 
        : "memory");
        
    return c != 0;
}

/**
 * @brief               Decrement and test.
 * @param variable      Pointer of type atomic_uint32_t
 * 
 * Atomically decrements v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.  Note that the guaranteed
 * useful range of an atomic_uint32_t is only 24 bits.
 */ 
static inline int atomic_uint32_decrement_and_test (atomic_uint32_t *variable)
{
    unsigned char c;

    asm volatile (
        LOCK "decl %0; sete %1"
        :"=m" (variable->value), "=qm" (c)
        :"m" (variable->value) 
        : "memory");
        
    return c != 0;
}

/**
 * @brief               Add and test if negative.
 * @param variable      Pointer of type atomic_uint32_t
 * @param i             Integer value to add
 * 
 * Atomically adds i to v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.  Note that the guaranteed
 * useful range of an atomic_uint32_t is only 24 bits.
 */ 
static inline int atomic_add_negative (atomic_uint32_t *variable, uint32_t i)
{
	unsigned char c;

	asm volatile (
		LOCK "addl %2,%0; sets %1"
		: "=m" (variable->value), "=qm" (c)
		: "ir" (i), "m" (variable->value) 
        : "memory");
		
	return c;
}

#endif /* !__ENVIROMENT_COMMON_IA32_ATOMIC_UINT32_H_ */


