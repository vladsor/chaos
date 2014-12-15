
/* Defines. */
#define MODULE_NAME_LENGTH              48
#define MODULE_VERSION_LENGTH           16

/** 
 * @brief               A module information structure. 
 */
typedef struct
{
    /** 
     * @brief           The module name.
     */
    char                name[MODULE_NAME_LENGTH];
    
    /**
     * @brief           The module version. 
     */
    char                version[MODULE_VERSION_LENGTH];
} module_info_t;

extern function_info_t functions_table[];

typedef return_t (module_start_t) (int argc, char *argv[], char **envp);
typedef module_start_t * p_module_start_t;

typedef return_t (module_stop_t) (void);
typedef module_stop_t * p_module_stop_t;

typedef struct
{
    elf_parsed_t elf_parsed;
    
    p_module_start_t start;
    p_module_stop_t stop;
  
} storm_module_data_t;

typedef storm_module_data_t * p_storm_module_data_t;

typedef struct
{
    object_reference_t object;
    
    bool enabled;
    
} storm_module_info_t;

typedef storm_module_info_t * p_storm_module_info_t;

extern p_storm_module_info_t storm_modules;

