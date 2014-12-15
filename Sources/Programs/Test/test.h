typedef uint32_t handle_t;

typedef struct
{
    uint64_t object_data;
    uint64_t handle_data;
} context_t;

#define HANDLE_THIS_PROCESS 0

#define SYSTEM_CALL_IDT_ENTRY \
                        (0x88)

static inline void system_call_computer_return (void)
{
    asm volatile 
    (
        "pushl %1\n"
        "int %0\n"
        :
        :
        "N" (SYSTEM_CALL_IDT_ENTRY),
        "N" (1)
    );
}

enum
{
    DEBUG_LEVEL_PANIC = -2,
    DEBUG_LEVEL_ERROR,
    DEBUG_LEVEL_NONE,
    DEBUG_LEVEL_WARNING,
    DEBUG_LEVEL_INFORMATIVE,
    DEBUG_LEVEL_INFORMATIVE1,
    DEBUG_LEVEL_INFORMATIVE2,
    DEBUG_LEVEL_INFORMATIVE3,
};

static inline return_t system_call_debug_print (uint8_t level, 
    const char *module_name, const char *function_name, uint32_t line, 
    const char *message)
{
    return_t return_value;

    asm volatile 
    (
        "pushl %7\n"
        "pushl %6\n"
        "pushl %5\n"
        "pushl %4\n"
        "pushl %3\n"
        "pushl %2\n"
        "int %1\n"
        "addl $24, %%esp\n"
        :
        "=a" (return_value)
        :
        "N" (SYSTEM_CALL_IDT_ENTRY),
        "N" (0),
        "g" ((uint32_t) level), 
        "g" (module_name), 
        "g" (function_name), 
        "g" (line), 
        "g" (message)
    );
    
    return return_value;
}

static inline void system_call_invoke (void)
{
    asm volatile (
        "int %0"
        :
        : "N" (SYSTEM_CALL_IDT_ENTRY));
}

static inline unsigned int arguments_parse (
  char *source, 
  char **array_of_pointers)
{
  unsigned int number_of_arguments = 0;
  unsigned int position;
  char waited_char = ' ';
  int state = 0;

  for(position = 0;source[position] != '\0';position++)
  {
    if (state == 0)
    {
      if (source[position] == waited_char)
      {
        continue;
      }
      else if (source[position] == '\"')
      {
        waited_char = '\"';
        array_of_pointers[number_of_arguments] = source + position + 1;
        number_of_arguments++;
      }
      else if (source[position] == '\'')
      {
        waited_char = '\'';
        array_of_pointers[number_of_arguments] = source + position + 1;
        number_of_arguments++;
      }
      else
      {
        array_of_pointers[number_of_arguments] = source + position;
        number_of_arguments++;
      }
      state = 1;
    }
    else if (state == 1)
    {
      if (source[position] == waited_char)
      {
        state = 0;
	source[position] = 0;
        waited_char = ' ';
      }
    }
  }

  return number_of_arguments;
}

#define process$parameters_get(process,parameters) \
    system_call_invoke ()
    
#define process$exit(process,return_value) \
    system_call_invoke ()
