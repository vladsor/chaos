/**
 * @file                copy.h
 * @brief               Memory copy functions.
 * @author              Per Lundberg <per@chaosdev.org>
 * @version             1.0
 * @date                1998-2002
 */

#ifndef __MEMORY_INLINES_COPY__
#define __MEMORY_INLINES_COPY__

/**
 * @brief               Copy between memory areas.
 * @param to            The source.
 * @param from          The destination.
 * @param size          The number of bytes to copy.
 * @return              Pointer to destination.
 */
static inline void *memory_copy (void *to, void *from, unsigned int size)
{
    int ecx, edi, esi;

    asm volatile ("cld\n"
                  "rep ; movsl\n"
                  "testb $2, %b4\n"
                  "je 1f\n"
                  "movsw\n"
                  "1: testb $1, %b4\n"
                  "je 2f\n"
                  "movsb\n"
                  "2:"
                  :
                  "=&c" (ecx),
                  "=&D" (edi),
                  "=&S" (esi)
                  :
                  "0" (size / 4),
                  "q" (size),
                  "1" ((long) to),
                  "2" ((long) from)
                  :
                  "memory");

    return (to);
}

#endif /* !__MEMORY_INLINES_COPY__ */
