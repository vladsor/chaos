object_reference_t object_translate_reference (object_reference_t object)
{
    switch (object)    
    {
        case OBJECT_THIS:
        {
            return object_current;
        }

        case OBJECT_INVOKER:
        {
            return object_current_invoker;
        }
        
        case OBJECT_KERNEL:
        {
            return object_kernel;
        }
        
        case OBJECT_THIS_PROCESS:
        {
            return object_process_current;
        }
        
        case OBJECT_THIS_THREAD:
        {
            return object_thread_current;
        }
    };
    
    return object;
}

