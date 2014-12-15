
typedef return_t (main_function_t) (int argc, char *argv[], char **envp);
typedef main_function_t * p_main_function_t;

typedef struct
{
    char name[STRING_MAX_LENGTH];
    p_main_function_t init;
    bool enabled;
    char parameters[STRING_MAX_LENGTH];
} subsystem_built_in_t;

extern subsystem_built_in_t subsystem_built_in[];

#define NUMBER_OF_BUILT_IN (sizeof (subsystem_built_in) / \
    sizeof (subsystem_built_in_t))


