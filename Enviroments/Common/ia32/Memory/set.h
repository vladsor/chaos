/**
 * @file                set.h
 * @brief               Memory set functions.
 * @author              Per Lundberg <per@chaosdev.org>
 * @version             1.0
 * @date                1998-2002
 */

#ifndef __MEMORY_INLINES_SET__
#define __MEMORY_INLINES_SET__

/**
 * @brief               Set memory to the given uint8.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint8s to set.
 */
static inline void memory_set_uint8 (uint8_t *address, uint8_t value, 
    unsigned int count)
{
    int ecx, edi;

    asm volatile ("cld\n"
                  "rep\n"
                  "stosb"
                  :
                  "=&c" (ecx),
                  "=&D" (edi)
                  :
                  "a" (value),
                  "1" (address),
                  "0" (count)
                  :
                  "memory");
}

/**
 * @brief               Set memory to the given uint16.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint16s to set.
 */
static inline void memory_set_uint16 (uint16_t *address, uint16_t value, 
    unsigned int count)
{
    int ecx, edi;

    asm volatile ("cld\n"
                  "rep\n"
                  "stosw"
                  :
                  "=&c" (ecx),
                  "=&D" (edi)
                  :
                  "a" (value),
                  "1" (address),
                  "0" (count)
                  :
                  "memory");
}

/**
 * @brief               Set memory to the given uint32.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint32s to set.
 */
static inline void memory_set_uint32 (uint32_t *address, uint32_t value, 
    unsigned int count)
{
    int ecx, edi;

    asm volatile  ("cld\n"
                   "rep\n"
                   "stosl"
                   :
                   "=&c" (ecx),
                   "=&D" (edi)
                   :
                   "a" (value),
                   "1" (address),
                   "0" (count)
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

#endif /* !__MEMORY_INLINES_SET__ */
