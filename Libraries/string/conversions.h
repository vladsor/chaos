/**
 * @file                conversions.h
 * @brief               Functions for convertions between string and numbers.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#ifndef __LIBRARY_STRING_CONVERSIONS_H__
#define __LIBRARY_STRING_CONVERSIONS_H__


/**
 * @brief               Convert string to signed integer.
 * @param input         Input string
 * @param number        Pointer to saved signed number
 * @param base          Base of number
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t string_to_int16 (char *input, int16_t *number, 
    unsigned int base, unsigned int *count);

extern return_t string_to_int32 (char *input, int32_t  *number, 
    unsigned int base, unsigned int *count);

extern return_t string_to_int64 (char *input, int64_t *number, 
    unsigned int base, unsigned int *count);

#define string_to_signed_int string_to_int32

extern return_t string_to_int32_with_base_autodetect (const char *string, 
    int32_t *number, int *characters);

#define string_to_number string_to_int32_with_base_autodetect

/**
 * @brief               Convert string to unsigned integer.
 * @param input         Input string
 * @param number        Pointer to saved unsigned number
 * @param base          Base of number  
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t string_to_uint16 (char *input, uint16_t *number, 
    unsigned int base, unsigned int *count);

extern return_t string_to_uint32 (char *input, uint32_t *number, 
    unsigned int base, unsigned int *count);

extern return_t string_to_uint64 (char *input, uint64_t *number, 
    unsigned int base, unsigned int *count);

#define string_to_unsigned_int string_to_uint32

/**
 * @brief               Convert string to double number.
 * @param input         Input string
 * @param number        Pointer to saved double number
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t string_to_double (char *input, double *number, 
    unsigned int *count);
/*
extern return_t string_to_float (char *input, float *number, 
    unsigned int *count);
*/
/**
 * @brief               Convert number to string.
 * @param string
 * @param number
 * @param base
 * @param size
 * @param precision
 * @param flags
 * @return
 */
extern char *int16_to_string (char *string, int16_t number, int base,
    int size, int precision, int flags);

extern char *int32_to_string (char *string, int32_t number, int base,
    int size, int precision, int flags);

extern char *uint32_to_string (char *string, uint32_t number, int base,
    int size, int precision, int flags);

extern char *int64_to_string (char *string, int64_t number, int base,
    int size, int precision, int flags);

extern char *uint64_to_string (char *string, uint64_t number, int base,
    int size, int precision, int flags);

#define number_to_string uint32_to_string

#endif /* __LIBRARY_STRING_CONVERSIONS_H__ */
