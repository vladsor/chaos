
void exception_register (exception_id_t exception_id, 
    uint32_t exception_type)
{
    p_exception_t exception;
    uint32_t i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (id: %X, type: %X)\n",
        __FILE__, __FUNCTION__, exception_id, exception_type);

    TRY
    {
        memory_allocate ((void **) &exception, sizeof (exception_t));
    }
    CATCH_ALL (e)
    {
        THROW (e);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Exception = %p\n",
        __FILE__, __FUNCTION__, exception);

    exception->id = exception_id;
    exception->type = exception_type;
    exception->number_of_references = 0;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Adding to storage: %p....\n",
        __FILE__, __FUNCTION__, exception);

    hash_table_add_element (exceptions_table, (hash_element_t *) exception);
}

void exception_unregister (exception_id_t exception_id)
{
    p_exception_t exception;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (id: %X)\n",
        __FILE__, __FUNCTION__, exception_id);

    exception = (p_exception_t) hash_table_search_element (&exception_id);
    
    if (exception == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (exception->number_of_references > 0)
    {
        THROW (EXCEPTION_IS_IN_USE);
    }

    hash_table_delete_element (exceptions_table, &exception_id);
    
    memory_deallocate (exception);
}

list_t context_list = NULL;

void exception_add_handler (p_exception_context_t exception_context)
{
    list_insert_node (&context_list, exception_context);
}

void exception_remove_handler ()
{
    list_remove_last (&context_list);
}

static void dump_registers (cpu_register_t *registers)
{
    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "CS: %04X EIP: %08X EFLAGS: %08X\n", 
        registers->cs, registers->eip, registers->eflags);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "SS: %04X ESP: %08X EBP: %08X\n",
        registers->ss, registers->esp, registers->ebp);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "DS:  %04X ES:  %04X FS:  %04X GS:  %04X\n",
        registers->ds, registers->es, registers->fs, registers->gs);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "EAX: %08X EBX: %08X ECX: %08X EDX: %08X\n",
        registers->eax, registers->ebx, registers->ecx, registers->edx);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "ESI: %08X EDI: %08X EBP: %08X ESP: %08X\n",
        registers->esi, registers->edi, registers->ebp, registers->esp);
}

void exception_invoke_handler (p_exception_info_t exception_info)
{
    p_exception_context_t context = NULL;
    
    context = context_list.last;
    
    if (context == NULL)
    {
        dump_registers (exception_info->state);    
    }
    else
    {
        memory_copy (context->info, exception_info, sizeof (exception_info_t));
        info->raises = TRUE;
        cpu_load_state (exception_info->state);
    }
}

