/**
 * @file                conversions.h
 * @brief               Functions for convertions between string and numbers.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#ifndef __LIBRARY_STRING_WCONVERSIONS_H__
#define __LIBRARY_STRING_WCONVERSIONS_H__


/**
 * @brief               Convert string to signed integer.
 * @param input         Input string
 * @param number        Pointer to saved signed number
 * @param base          Base of number
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t wstring_to_int16 (wchar_t *input, int16_t *number, 
    unsigned int base, unsigned int *count);

extern return_t wstring_to_int32 (wchar_t *input, int32_t  *number, 
    unsigned int base, unsigned int *count);

extern return_t wstring_to_int64 (wchar_t *input, int64_t *number, 
    unsigned int base, unsigned int *count);

#define wstring_to_signed_int wstring_to_int32

extern return_t wstring_to_int32_with_base_autodetect (const wchar_t *string, 
    int32_t *number, int *characters);

#define wstring_to_number wstring_to_int32_with_base_autodetect

/**
 * @brief               Convert string to unsigned integer.
 * @param input         Input string
 * @param number        Pointer to saved unsigned number
 * @param base          Base of number  
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t wstring_to_uint16 (wchar_t *input, uint16_t *number, 
    unsigned int base, unsigned int *count);

extern return_t wstring_to_uint32 (wchar_t *input, uint32_t *number, 
    unsigned int base, unsigned int *count);

extern return_t wstring_to_uint64 (wchar_t *input, uint64_t *number, 
    unsigned int base, unsigned int *count);

#define wstring_to_unsigned_int wstring_to_uint32

/**
 * @brief               Convert string to double number.
 * @param input         Input string
 * @param number        Pointer to saved double number
 * @param count         If not NULL saved length of string's number presentation
 * @return              String result code.
 */
extern return_t wstring_to_double (wchar_t *input, double *number, 
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
extern wchar_t * int16_to_wstring (wchar_t *string, int16_t number, int base,
    int size, int precision, int flags);

extern wchar_t * int32_to_wstring (wchar_t *string, int32_t number, int base,
    int size, int precision, int flags);

extern wchar_t * uint32_to_wstring (wchar_t *string, uint32_t number, int base,
    int size, int precision, int flags);

extern wchar_t * int64_to_wstring (wchar_t *string, int64_t number, int base,
    int size, int precision, int flags);

extern wchar_t * uint64_to_wstring (wchar_t *string, uint64_t number, int base,
    int size, int precision, int flags);

#define number_to_wstring uint32_to_wstring

#endif /* __LIBRARY_STRING_CONVERSIONS_H__ */
