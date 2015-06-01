/**
 * @file                compare.h
 * @brief               Memory compare functions.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2002
 */

#ifndef __MEMORY_INLINES_COMPARE__
#define __MEMORY_INLINES_COMPARE__

/**
 * @brief               Compare two memory areas.
 * @param memory1       First memory area.
 * @param memory2       Second memory area.
 * @param size          Length of memory areas.
 * @return              TRUE if equals, FALSE otherwise.
 */
static inline bool memory_compare (void *memory1, void *memory2, 
    unsigned int size)
{
  register int eax;
  int esi, edi, ecx;
  
  asm volatile ("cld\n"
                "1: decl %3\n"
     "=&S" (esi), 
     "=&D" (edi), 
     "=&c" (ecx)
   : "1" (memory1), 
     "2" (memory2), 
     "3" (size));

  return (eax == 0);
}

#endif /* !__MEMORY_INLINES_COMPARE__ */