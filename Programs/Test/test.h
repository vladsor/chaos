typedef uint32_t handle_t;

#define HANDLE_THIS_PROCESS 0

#define SYSTEM_CALL_IDT_ENTRY \
                        (0x88)

static inline void system_call_invoke (void)
{
    asm volatile (
        "int %0"
        :
        : "n" (SYSTEM_CALL_IDT_ENTRY));
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
