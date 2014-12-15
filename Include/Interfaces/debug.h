#include "Common/debug.h"

#define IID_DEBUG 0x00000201

enum
{
    MID_DEBUG_PRINT,
};

typedef return_t (debug_print_function_t) (uint8_t level, char *module_name, 
    char *function_name, uint32_t function_line, char *message);

typedef struct
{
    debug_print_function_t *print;
} debug_interface_t;
       
#define debug$print(handle,level,module_name,function_name,function_line,\
        message) \
    ((debug_interface_t *) ((handle)->functions))->print ( \
        (level), (module_name), (function_name), (function_line), (message))

