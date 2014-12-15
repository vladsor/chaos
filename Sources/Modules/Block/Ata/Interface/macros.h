
#ifdef DEBUG_LEVEL
#include <string.h>

#ifndef DEBUG_MODULE_NAME
#   define DEBUG_MODULE_NAME ""
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
                __FILE__, __FUNCTION__, __LINE__, #condition, message); \
            while (1); \
        } \
    } while (0)

#elif defined (__STORM_KERNEL_MODULE__)

#include <EventClasses/debug.h>
extern event_supplier_reference_t debug_supplier;

#define DEBUG_PRINT(level, message_fmt...) \
    do { \
        if (DEBUG_LEVEL >= (level)) \
        { \
            debug_event_data_t __event__; \
            sequence_t __seq__ = {&__event__, 1, sizeof (__event__)}; \
            __event__.level = (level); \
            string_copy (__event__.module_name, DEBUG_MODULE_NAME); \
            string_copy (__event__.function_name, __FUNCTION__); \
            __event__.line = __LINE__; \
            string_print (__event__.message, ## message_fmt); \
            event_fire (debug_event_supplier, __seq__); \
        } \
    } while (0)

#else
#endif

#else

#define DEBUG_PRINT(dargs...)

#define DEBUG_PRINTW(level, message...) 

#define DEBUG_HALT(message)

#define DEBUG_ASSERT(condition, message)

#endif
