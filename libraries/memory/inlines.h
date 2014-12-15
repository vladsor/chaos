/* Compare two strings. Returns 0 if equal. */
/*
static inline int memory_compare 
  (void *memory1, void *memory2, unsigned int size)
{
  int esi, edi;
  register int result;

  asm volatile
  ("\
    cld
    repe cmpsb
    jne 1f

    xorl %%eax, %%eax
    jmp 2f
1:
    movl $1, %%eax
2:    
   "
   : "=a" (result), "=c" (size), "=&S" (esi), "=&D" (edi)
   : "1" (memory1), "2" (memory2));

  return result;
}
*/
static inline int memory_compare
  (void *memory1, void *memory2, unsigned int size)
{
  register int eax;
  int esi, edi, ecx;

  asm volatile
  ("\
    cld
1:  decl %3
    js 2f
    lodsb
    scasb
    jne 3f
    jmp 1b
2:  xorl %%eax, %%eax
    jmp 4f
3:  sbbl %%eax, %%eax
    orb $1, %%al
4:
"
   : "=a" (eax), "=&S" (esi), "=&D" (edi), "=&c" (ecx)
   : "1" (memory1), "2" (memory2), "3" (size));

  return eax;
}
