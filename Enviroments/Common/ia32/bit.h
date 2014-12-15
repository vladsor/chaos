/**
 * @brief               Find the first zero bit in a memory region.
 * @param addr          The address to start the search at.
 * @param size          The maximum size to search.
 * @return              Returns the bit-number of the first zero bit, not 
 *                      the number of the byte containing a bit.
 */
static inline int bit_find_first_zero (void * addr, size_t size)
{
	int d0, d1, d2;
	int res;

    if (size == 0)
    {
		return 0;
    }
    
	/* This looks at memory. Mark it volatile to tell gcc not to move it around 
     */
    asm volatile(
		"movl $-1, %%eax\n"
		"xorl %%edx, %%edx\n"
		"repe; scasl\n"
		"je 1f\n"
		"xorl -4(%%edi), %%eax\n"
		"subl $4, %%edi\n"
		"bsfl %%eax, %%edx\n"
		"1: subl %%ebx, %%edi\n"
		"shll $3, %%edi\n"
		"addl %%edi, %%edx"
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
 * @brief               Find the first zero bit in a memory region.
 * @param addr          The address to base the search on.
 * @param offset        The bitnumber to start searching at.
 * @param size          The maximum size to search.
 * @return
 */
static inline int bit_find_next_zero (void * addr, int size, int offset)
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
	res = bit_find_first_zero (p, size - 32 * (p - (unsigned long *) addr));
	
	return (offset + set + res);
}

/**
 * @brief               Find first zero in word.
 * @param word          The word to search.
 * @return              Undefined if no zero exists, so code should check 
 *                      against ~0UL first.
 */
static inline unsigned long ffz (unsigned long word)
{
	asm ("bsfl %1, %0"
		:"=r" (word)
		:"r" (~word));
		
	return word;
}


/**
 * @brief               Find first bit set.
 * @param x             The word to search.
 * @return
 *
 * This is defined the same way as the libc and compiler builtin ffs routines, 
 * therefore differs in spirit from the above ffz (man ffs).
 */
static inline int ffs (int x)
{
	int r;

	asm ("bsfl %1, %0\n"
		"jnz 1f\n"
		"movl $-1, %0\n"
		"1:" 
        : "=r" (r) 
        : "g" (x));
        
	return r + 1;
}

