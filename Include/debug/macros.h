
#ifdef DEBUG_LEVEL
#include <string.h>

#ifndef DEBUG_MODULE_NAME
#   define DEBUG_MODULE_NAME ""
#endif

#define DEBUG_PRINT(level, message...) \
    do { \
        if (DEBUG_LEVEL >= (level)) \
        { \
            char __temp_buffer__[STRING_MAX_LENGTH]; \
            string_print (__temp_buffer__, ## message); \
            system_debug_print ((level), DEBUG_MODULE_NAME, \
                __FUNCTION__, __LINE__, __temp_buffer__); \
        } \
    } while (0)
    
#define DEBUG_PRINT_INFO \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_INFORMATIVE) \
        { \
            DEBUG_PRINT ("file: %s, function: %s, line: %s.\n", \
                __FILE__, __FUNCTION__, __LINE__); \
        } \    } while (0) 

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
        } \
    } while (0)

#else

#define DEBUG_DATA

#define DEBUG_INIT

#define DEBUG_PRINT(dargs...)

#define DEBUG_HALT(message)

#define DEBUG_ASSERT(condition, message)

#endif
