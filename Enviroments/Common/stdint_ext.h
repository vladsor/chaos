typedef void * p_void_t;

typedef struct
{
    p_void_t data;
    uint32_t count;
    uint32_t block_size;
   
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

//typedef wchar_t * p_wchar_t;

