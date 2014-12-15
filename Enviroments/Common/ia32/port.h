/**
 * @file                port.h
 * @brief               Port in/output. 
 * @author              Per Lundberg <per@chaosdev.org>,
 *                      Vladimir Sorokin
 * @version             1.1
 * @date                1998-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __ENVIROMENT_IA32_PORT_H__
#define __ENVIROMENT_IA32_PORT_H__

/**
 * @brief               Write byte to port.
 * @param port          Port
 * @param data          Written byte
 */
static inline void port_uint8_out (uint16_t port, uint8_t data)
{
    asm ("outb	%1,%0"
         :
         :
         "Nd"(port),
         "a"(data));
};

/**
 * @brief               Write word to port.
 * @param port          Port
 * @param data          Written word
 */
static inline void port_uint16_out (uint16_t port, uint16_t data)
{
  asm ("outw %1, %0"
       :
       : "Nd" (port),
         "a" (data));
}

/**
 * @brief               Write double word to port.
 * @param port          Port
 * @param data          Written double word
 */
static inline void port_uint32_out (uint16_t port, uint32_t data)
{
  asm ("outl %1, %0"
       :
       : "Nd" (port),
         "a" (data));
}

/**
 * @brief               Read byte from port.
 * @param port          Port
 * @return              Read byte
 */
static inline uint8_t port_uint8_in (uint16_t port)
{
  uint8_t data;
  asm volatile ("inb	%1,%0"
                :
                "=a"(data)
                :
                "Nd"(port));

  return data;
};

/**
 * @brief               Read word from port.
 * @param port          Port
 * @return              Read word
 */
static inline uint16_t port_uint16_in (uint16_t port)
{
  uint16_t data;

  asm volatile ("inw %1, %0"
                : "=a" (data)
                : "Nd" (port));

  return data;
}

/**
 * @brief               Read double word from port.
 * @param port          Port
 * @return              Read double word
 */
static inline uint32_t port_uint32_in (uint16_t port)
{
  uint32_t data;

  asm volatile ("inl %1, %0"
                : "=a" (data)
                : "Nd" (port));

  return data;
}

/* 'Pausing' version of the above. */

/**
 * @brief               Write byte to port and wait a pause.
 * @param port          Port
 * @param data          Written byte
 */
static inline void port_uint8_out_pause (uint16_t port, uint8_t data)
{
    asm ("outb %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         :
         "Nd" (port),
         "a" (data));
}

/**
 * @brief               Write word to port and wait a pause.
 * @param port          Port
 * @param data          Written word
 */
static inline void port_uint16_out_pause (uint16_t port, uint16_t data)
{
    asm ("outw %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         : 
         "Nd" (port),
         "a" (data));
}

/**
 * @brief               Write double word to port and wait a pause.
 * @param port          Port
 * @param data          Written double word
 */
static inline void port_uint32_out_pause (uint16_t port, uint32_t data)
{
    asm ("outl %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         :
         "Nd" (port),
         "a" (data));
}

/* String operations. */

/**
 * @brief               Write byte string to port.
 * @param port          Port
 * @param data          Pointer to byte string
 * @param length        Length of string in bytes
 */
static inline void port_uint8_out_string (uint16_t port, uint8_t *data,
    size_t length)
{
    asm volatile ("cld\n"
                  "rep\n"
                  "outsb"
                  :
                  :
                  "c" (length),
                  "S" (data),
                  "d" (port));
}

/**
 * @brief               Write word string to port.
 * @param port          Port
 * @param data          Pointer to word string
 * @param length        Length of string in words
 */
static inline void port_uint16_out_string (uint16_t port, uint16_t *data,
    size_t length)
{
    asm volatile ("cld\n"
                  "rep\n"
                  "outsw"
                  :
                  :
                  "c" (length),
                  "S" (data),
                  "d" (port));
}

/**
 * @brief               Write double word string to port.
 * @param port          Port
 * @param data          Pointer to double word string
 * @param length        Length of string in double words
 */
static inline void port_uint32_out_string (uint16_t port, uint32_t *data,
    size_t length)
{
    asm volatile ("cld\n"
                  "rep\n"
                  "outsl"
                  :
                  :
                  "c" (length),
                  "S" (data),
                  "d" (port));
}

/**
 * @brief               Read byte string from port.
 * @param port          Port
 * @param data          Pointer to byte string
 * @param length        Length of string in bytes
 */
static inline void port_uint8_in_string (uint16_t port, uint8_t *data, 
    size_t length)
{
  asm volatile ("cld\n"
                "rep\n"
                "insb"
                :
                : 
		"c" (length),
                "D" (data),
                "d" (port));
}

/**
 * @brief               Read word string from port.
 * @param port          Port
 * @param data          Pointer to word string
 * @param length        Length of string in words
 */
static inline void port_uint16_in_string (uint16_t port, uint16_t *data, 
    size_t length)
{
  asm volatile ("cld\n"
                "rep\n"
                "insw"
                :
                : 
		"c" (length),
                "D" (data),
                "d" (port));
}

/**
 * @brief               Read double word string from port.
 * @param port          Port
 * @param data          Pointer to double word string
 * @param length        Length of string in double words
 */
static inline void port_uint32_in_string (uint16_t port, uint32_t *data,
    size_t length)
{
  asm volatile ("cld\n"
                "rep\n"
                "insl"
                :
                : 
		"c" (length),
                "D" (data),
                "d" (port));
}

#endif /* !__ENVIROMENT_IA32_PORT_H__ */

