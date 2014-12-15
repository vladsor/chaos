
#ifdef CONFIG_SMP
#define LOCK_PREFIX "lock ; "
#else
#define LOCK_PREFIX ""
#endif

#define ADDR (*(volatile long *) addr)

/**
 * @brief               Atomically set a bit in memory.
 * @param nr            The bit to set.
 * @param addr          The address to start counting from.
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 * Note that nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void atomic_bit_set (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btsl %1, %0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

/**
 * @brief               Clears a bit in memory.
 * @param nr            Bit to clear.
 * @param addr          Address to start counting from.
 *
 * atomic_bit_clear() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static inline void atomic_bit_clear (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btrl %1, %0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

/**
 * @brief               Toggle a bit in memory.
 * @param nr            Bit to clear.
 * @param addr          Address to start counting from.
 *
 * atomic_bit_toggle() is atomic and may not be reordered.
 * Note that nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void atomic_bit_toggle (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btcl %1, %0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

