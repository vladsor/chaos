
#if defined (DEBUG_LEVEL)
#include <string.h>

#ifndef DEBUG_MODULE_NAME
#   define DEBUG_MODULE_NAME ""
#endif

#ifndef DEBUG_SUPPLIER
#   define DEBUG_SUPPLIER
#endif

#if defined (__STORM_KERNEL__)

#define DEBUG_PRINT(level, message...) \
    do { \
        if (DEBUG_LEVEL >= (level)) \
        { \
            char __temp_buffer__[STRING_MAX_LENGTH]; \
            string_print (__temp_buffer__, ## message); \
            system_debug_print ((level), (const char *) DEBUG_MODULE_NAME, \
                (const char *) __FUNCTION__, __LINE__, \
                (const char *) __temp_buffer__); \
        } \
    } while (0)

#define DEBUG_PRINTW(level, message...) \
    do { \
        if (DEBUG_LEVEL >= (level)) \
        { \
            wchar_t __temp_buffer__[WSTRING_MAX_LENGTH]; \
            wstring_print (__temp_buffer__, ## message); \
            system_debug_printw ((level), DEBUG_MODULE_NAME, \
                __FUNCTION__, __LINE__, __temp_buffer__); \
        } \
    } while (0)
    
#define DEBUG_PRINT_INFO \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_INFORMATIVE) \
        { \
            DEBUG_PRINT ("file: %s, function: %s, line: %s.\n", \
                __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (0)
 

#define DEBUG_HALT(message) \
    do { \
        { \
            DEBUG_PRINT (DEBUG_LEVEL_ERROR, message); \
            while (TRUE); \
        } \
    } while (0)
    
#define DEBUG_ASSERT(condition, message)\
    do { \
        if (!(condition)) \
        {               \
            DEBUG_PRINT (DEBUG_LEVEL_ERROR, "%s::%s:%u ASSERT(%s) %s\n", \
                DEBUG_MODULE_NAME, __FUNCTION__, __LINE__, #condition, message); \
            while (1); \
        } \
    } while (0)

#elif defined (__STORM_PROGRAM__)

//extern return_t system_debug_print (uint8_t level, const char *module_name, 
//    const char *function_name, uint32_t line, const char *message);

#define DEBUG_PRINT(level, message...) \
    do { \
        if (DEBUG_LEVEL >= (level)) \
        { \
            char __temp_buffer__[STRING_MAX_LENGTH]; \
            string_print (__temp_buffer__, ## message); \
            system_call_debug_print ((level), (const char *) DEBUG_MODULE_NAME, \
                (const char *) __FUNCTION__, __LINE__, \
                (const char *) __temp_buffer__); \
        } \
    } while (0)

#else /* defined (__STORM_KERNEL__) */

#define DEBUG_PRINTW(level, message...) \
    do { \
        if ((DEBUG_LEVEL >= (level)) && (DEBUG_SUPPLIER != REFERENCE_NULL)) \
        { \
            wchar_t __temp_buffer__[WSTRING_MAX_LENGTH]; \
            wchar_t __function_name__[WSTRING_MAX_LENGTH]; \
            wstring_print (__function_name__, L"%s", __FUNCTION__); \
            wstring_print (__temp_buffer__, ## message); \
            debug$fire ((DEBUG_SUPPLIER), (level), \
                (const wchar_t *) DEBUG_MODULE_NAME, \
                (const wchar_t *) __function_name__, (uint32_t) __LINE__, \
                (const wchar_t *) __temp_buffer__); \
        } \
    } while (0)

#endif 

#else /* defined (DEBUG_LEVEL) */

#define DEBUG_PRINT(dargs...)

#define DEBUG_PRINTW(level, message...) 

#define DEBUG_HALT(message)

#define DEBUG_ASSERT(condition, message)

#endif /* defined (DEBUG_LEVEL) */
