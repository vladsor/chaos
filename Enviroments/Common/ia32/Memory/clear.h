/**
 * @file                clear.h
 * @brief               Memory clear functions.
 * @author              Vladimir Sorokin.
 * @version             1.0
 * @date                2003-2004
 */

#ifndef __MEMORY_CLEAR__
#define __MEMORY_CLEAR__

static inline void memory_clear (void *address, size_t size)
{
    int ecx, edi;

    asm volatile  (
        "xorl %%eax, %%eax\n"
        "cld\n"
        "rep ; stosl\n"
        "testb $2, %b3\n"
        "je 1f\n"
        "stosw\n"
        "1: testb $1, %b3\n"
        "je 2f\n"
        "stosb\n"
        "2:"
    :
        "=&c" (ecx),
        "=&D" (edi)
    :
        "0" (size / 4),
        "q" (size),
        "1" (address)
    :
        "memory");
}

/**
 * @brief               Clear (zero out) a page.
 * @param address       The base address of the page to clear.
 */
static inline void memory_clear_page (void *address)
{
    memory_set_uint32 ((uint32_t *) address, 0, PAGE_SIZE / 4);
}

#endif /* !__MEMORY_CLEAR__ */
