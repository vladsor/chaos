/**
 * find_first_zero_bit - find the first zero bit in a memory region
 * @param addr The address to start the search at
 * @param size The maximum size to search
 *
 * @return Returns the bit-number of the first zero bit, not the number of the byte
 * containing a bit.
 */
static inline int find_first_zero_bit (void * addr, size_t size)
{
	int d0, d1, d2;
	int res;

    if (size == 0)
    {
		return 0;
    }
    
	/* This looks at memory. Mark it volatile to tell gcc not to move it around */
    asm volatile(
		"movl $-1,%%eax\n"
		"xorl %%edx,%%edx\n"
		"repe; scasl\n"
		"je 1f\n"
		"xorl -4(%%edi),%%eax\n"
		"subl $4,%%edi\n"
		"bsfl %%eax,%%edx\n"
		"1: subl %%ebx,%%edi\n"
		"shll $3,%%edi\n"
		"addl %%edi,%%edx"
		: 
            "=d" (res), 
            "=&c" (d0), 
            "=&D" (d1), 
            "=&a" (d2)
		:
            "1" ((size + 31) >> 5), 
            "2" (addr), 
            "b" (addr));
		
	return res;
}

/**
 * find_next_zero_bit - find the first zero bit in a memory region
 * @param addr The address to base the search on
 * @param offset The bitnumber to start searching at
 * @param size The maximum size to search
 */
static inline int find_next_zero_bit (void * addr, int size, int offset)
{
	unsigned long * p = ((unsigned long *) addr) + (offset >> 5);
	int set = 0, bit = offset & 31, res;
	
	if (bit)
    {
		/*
		 * Look for zero in first byte
		 */
		asm (
            "bsfl %1, %0\n"
			"jne 1f\n"
			"movl $32, %0\n"
			"1:"
			: "=r" (set)
			: "r" (~(*p >> bit)));
			
		if (set < (32 - bit))
		{
			return set + offset;
        }
        
		set = 32 - bit;
		p++;
	}
	
	/*
	 * No zero yet, search remaining full bytes for a zero
	 */
	res = find_first_zero_bit (p, size - 32 * (p - (unsigned long *) addr));
	
	return (offset + set + res);
}

/**
 * ffz - find first zero in word.
 * @param word The word to search
 *
 * @return Undefined if no zero exists, so code should check against ~0UL first.
 */
static inline unsigned long ffz (unsigned long word)
{
	asm ("bsfl %1, %0"
		:"=r" (word)
		:"r" (~word));
		
	return word;
}


/**
 * ffs - find first bit set
 * @param x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */
static inline int ffs (int x)
{
	int r;

	asm ("bsfl %1,%0\n"
		"jnz 1f\n"
		"movl $-1,%0\n"
		"1:" 
        : "=r" (r) 
        : "g" (x));
        
	return r + 1;
}

#ifdef CONFIG_SMP
#define LOCK_PREFIX "lock ; "
#else
#define LOCK_PREFIX ""
#endif

#define ADDR (*(volatile long *) addr)

/**
 * set_bit - Atomically set a bit in memory
 * @param nr the bit to set
 * @param addr the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 * Note that nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void atomic_bit_set (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btsl %1,%0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

/**
 * clear_bit - Clears a bit in memory
 * @param nr Bit to clear
 * @param addr Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static inline void atomic_bit_clear (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btrl %1,%0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

/**
 * change_bit - Toggle a bit in memory
 * @param nr Bit to clear
 * @param addr Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void atomic_bit_change (volatile void * addr, int nr)
{
    asm volatile (
        LOCK_PREFIX "btcl %1,%0"
        : "=m" (ADDR)
        : "Ir" (nr));
}

