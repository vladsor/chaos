/* Copyright 2000-2002 chaos development. */

/**
 * @file                defines.h
 * @brief               String defines.h
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#ifndef __LIBRARY_STRING_DEFINES_H__
#define __LIBRARY_STRING_DEFINES_H__

/* Flags used by string_print_va. */

/**
 * @brief               Pad with zero 
 */
#define STRING_ZERO_PAD BIT_VALUE(0)

/**
 * brief                Unsigned/signed long. 
 */
#define STRING_SIGN     BIT_VALUE(1)

/**
 * @brief               Show plus. 
 */
#define STRING_PLUS     BIT_VALUE(2)

/**
 * @brief               Space if plus. 
 */
#define STRING_SPACE    BIT_VALUE(3)

/**
 * @brief               Left justified 
 */
#define STRING_LEFT     BIT_VALUE(4)

/**
 * @brief               Add prefix '0x' to heximal number. 
 */
#define STRING_SPECIAL  BIT_VALUE(5)

/**
 * @brief               Use 'ABCDEF' instead of 'abcdef' for heximal number. 
 */
#define STRING_LARGE    BIT_VALUE(6)

/* Flag bit settings */

/**
 * @brief               Fixed width wanted
 */
#define RESPECT_WIDTH	BIT_VALUE(0)

/**
 * @brief               Add + for positive/floats 
 */
#define ADD_PLUS	BIT_VALUE(1)

/**
 * @brief               Padding possibility	
 */  
#define SPACE_PAD	BIT_VALUE(2)

/**
 * @brief               Pad with zero
 */  
#define ZERO_PAD	BIT_VALUE(3)

/**
 * @brief               Ajust to left 
 */
#define LEFT_PAD 	BIT_VALUE(4)

#define PRINT_FORMATTED(print_function, text...)  \
  {                                               \
    char temp_buffer[STRING_MAX_LENGTH];          \
    string_print (temp_buffer, ## text);          \
    print_function (temp_buffer);                 \
  }

#endif /* __LIBRARY_STRING_DEFINES_H__ */
