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
 * atomic_set - set atomic variable
 * @param v pointer of type atomic_t
 * @param i required value
 * 
 * Atomically sets the value of v to i.
 */ 
#define atomic_uint32_set(variable,i)      (((variable)->value) = (i))

/**
 * atomic_add - add integer to atomic variable
 * @param i: integer value to add
 * @param v: pointer of type atomic_t
 * 
 * Atomically adds i to v.
 */
static inline void atomic_uint32_add (atomic_uint32_t *variable, uint32_t i)
{
    asm volatile (
        LOCK "addl %1, %0"
        :"=m" (variable->value)
        :"ir" (i), "m" (variable->value));
}

/**
 * atomic_sub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v.
 */
static inline void atomic_uint32_subtract (atomic_uint32_t *variable, uint32_t i)
{
    asm volatile (
        LOCK "subl %1,%0"
        :"=m" (variable->value)
        :"ir" (i), "m" (variable->value));
}

/**
 * atomic_inc - increment atomic variable
 * @param v: pointer of type atomic_t
 * 
 * Atomically increments v by 1.
 */ 
static inline void atomic_uint32_increment (atomic_uint32_t *variable)
{
    asm volatile (
        LOCK "incl %0"
        :"=m" (variable->value)
        :"m" (variable->value));
}

/**
 * atomic_dec - decrement atomic variable
 * @param v: pointer of type atomic_t
 * 
 * Atomically decrements v by 1.
 */ 
static inline void atomic_uint32_decrement (atomic_uint32_t *variable)
{
    asm volatile (
        LOCK "decl %0"
        :"=m" (variable->value)
        :"m" (variable->value));
}

static inline void atomic_uint32_clear_mask (atomic_uint32_t *variable, uint32_t mask)
{
    asm volatile (
        LOCK "andl %0, %1"
        :
        : "r" (~(mask)), "m" (variable->value)
        : "memory")
}

static inline void atomic_uint32_set_mask (atomic_uint32_t *variable, uint32_t mask)
{
    asm volatile (
        LOCK "orl %0, %1"
        :
        : "r" (mask), "m" (variable->value)
        : "memory")
}

static inline void atomic_uint32_change_mask (atomic_uint32_t *variable, uint32_t mask)
{
    asm volatile (
        LOCK "xorl %0, %1"
        :
        : "r" (mask), "m" (variable->value)
        : "memory")
}


/**
 * atomic_sub_and_test - subtract value from variable and test result
 * @param i: integer value to subtract
 * @param v: pointer of type atomic_t
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
        : "=m" (v->counter), "=qm" (c)
        : "ir" (i), "m" (v->counter)
        : "memory");
		
    return c;
}

/**
 * atomic_inc_and_test - increment and test 
 * @param v: pointer of type atomic_t
 * 
 * Atomically increments v by 1
 * and returns true if the result is zero, or false for all
 * other cases.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */ 
static inline int atomic_uint32_increment_and_test (atomic_uint32_t *variable,
    uint32_t i)
{
    unsigned char c;

    asm volatile (
        LOCK "incl %0; sete %1"
        : "=m" (v->counter), "=qm" (c)
        : "m" (v->counter) : "memory");
        
    return c != 0;
}

/**
 * atomic_dec_and_test - decrement and test
 * @param v: pointer of type atomic_t
 * 
 * Atomically decrements v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */ 
static inline int atomic_uint32_decrement_and_test (atomic_uint32_t *variable,
    uint32_t i)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "decl %0; sete %1"
        :"=m" (v->counter), "=qm" (c)
        :"m" (v->counter) : "memory");
        
    return c != 0;
}

/**
 * atomic_add_negative - add and test if negative
 * @param v: pointer of type atomic_t
 * @param i: integer value to add
 * 
 * Atomically adds i to v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */ 
static inline int atomic_add_negative (atomic_uint32_t *variable, uint32_t i)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "addl %2,%0; sets %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
	return c;
}

