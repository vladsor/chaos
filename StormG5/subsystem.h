static bool subsystem_set_enabled (char *name, bool enabled)
{
    unsigned int i;

    for(i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (!string_compare (subsystem_built_in[i].name, name))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "Set subsystem: \'%s\'[%u] enabled to %s\n", 
                subsystem_built_in[i].name, i,
                subsystem_built_in[i].enabled ? "true" : "false");

            subsystem_built_in[i].enabled = enabled;
        
            return TRUE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "Try to configure unknown subsystem."); 
    
    return FALSE;
}

static bool subsystem_set_parameters (char *name, char *parameters)
{
    unsigned int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%s, %s)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, name, parameters);

    for(i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (!string_compare (subsystem_built_in[i].name, name))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "Set subsystem: \'%s\'[%u] parameters to %s\n", 
                subsystem_built_in[i].name, i,
                parameters);

            string_copy (subsystem_built_in[i].parameters, parameters);
        
            return TRUE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "Try to configure unknown subsystem.\n"); 
    
    return FALSE;
}

char parse_enable[] = "--enable-";
#define parse_enable_length (sizeof (parse_enable) - 1)

char parse_disable[] = "--disable-";
#define parse_disable_length (sizeof (parse_disable) - 1)

char parse_parameters[] = "--parameters-";
#define parse_parameters_length (sizeof (parse_parameters) - 1)

static void argument_analyse (char *argument)
{
    if (!string_compare_max (argument, parse_enable, parse_enable_length))
    {
        subsystem_set_enabled (argument + parse_enable_length, TRUE);
    }
    else if (!string_compare_max (argument, parse_disable, 
        parse_disable_length))
    {
        subsystem_set_enabled (argument + parse_disable_length, FALSE);
    }
    else if (!string_compare_max (argument, parse_parameters, 
        parse_disable_length))
    {
        char subsystem[STRING_MAX_LENGTH];
        char parameters[STRING_MAX_LENGTH];
        char sep;
        uint32_t i;
        uint32_t start;
        
        for (i = parse_parameters_length; 
            argument[i] != '=' && argument[i] != 0; 
            i++)
        {
            subsystem[i - parse_parameters_length] = argument[i];
        }
        
        if (argument[i] == '\0')
        {
            return;
        }
        
        subsystem[i - parse_parameters_length] = '\0';
        i++;
        
        if (argument[i] != '"' && argument[i] != '\'')
        {
            return;
        }
        
        sep = argument[i];
        i++;
        start = i;
        
        for (; argument[i] != sep && argument[i] != 0; i++)
        {
            parameters[i - start] = argument[i];
        }
        
        subsystem_set_parameters (subsystem, parameters);
    }
}
