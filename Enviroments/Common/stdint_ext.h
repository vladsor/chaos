typedef void * p_void_t;
typedef p_void_t * p_p_void_t;

typedef struct
{
    p_void_t data;
    uint32_t count;
   
} sequence_t;

typedef uint8_t * p_uint8_t;
typedef uint16_t * p_uint16_t;
typedef uint32_t * p_uint32_t;
typedef uint64_t * p_uint64_t;

#ifndef __cplusplus
/**
 * @brief              Boolean type with only two values: TRUE and FALSE
 */
typedef int            bool;
#endif

#ifndef _SIZE_T_
#define _SIZE_T_
/**
 * @brief               A size. 
 */
typedef unsigned int    size_t;
#endif

/**
 * @brief               A return value (STORM_RETURN_*) 
 */
typedef int             return_t;

/**
 * @brief               A function pointer. 
 */
typedef void           (function_t) (void);
typedef function_t * p_function_t;

/**
 * @brief               A linear/physical address. 
 */
typedef                 uint32_t address_t;

#ifndef __WCHAR_TYPE__
#define __WCHAR_TYPE__ int
#endif

#ifndef _WCHAR_T
#define _WCHAR_T

typedef __WCHAR_TYPE__ wchar_t;
#endif /* !_WCHAR_T */

typedef wchar_t * p_wchar_t;

#define WSTRING_MAX_LENGTH (256)
