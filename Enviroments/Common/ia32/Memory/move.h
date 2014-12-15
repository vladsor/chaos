#ifndef __MEMORY_INLINES_MOVE__
#define __MEMORY_INLINES_MOVE__

/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */

static inline void * memory_move (void *dest, const void *src, size_t n)
{
    register unsigned long int __d0, __d1, __d2;
    
    if (dest < src)
    {
        asm volatile (
            "cld\n"
            "rep\n"
            "movsb"
        :
            "=&c" (__d0), 
            "=&S" (__d1), 
            "=&D" (__d2)
        : 
            "0" (n), 
            "1" (src), 
            "2" (dest)
        : "memory");
    }
    else
    {
        asm volatile (
            "std\n"
            "rep\n"
            "movsb\n"
            "cld"
        : 
            "=&c" (__d0), 
            "=&S" (__d1), 
            "=&D" (__d2)
        : 
            "0" (n), 
            "1" (n - 1 + (const char *) src),
            "2" (n - 1 + (char *) dest)
       : "memory");
    }

    return dest;
}

#endif /* !__MEMORY_INLINES_MOVE__ */

