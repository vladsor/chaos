
virtual_cpu_reference_t virtual_cpu_create_internal (uint32_t cpu_policy, 
    resource_usage_t cpu_usage)
{
    p_virtual_cpu_t virtual_cpu;
    
    memory_allocate ((void **) &virtual_cpu, sizeof (virtual_cpu_t));
    
    if (cpu_policy != POLICY_UNSPECIFIED)
    {
        THROW (EXCEPTION_NOT_IMPLEMENTED);
    }
    
    virtual_cpu->policy = cpu_policy;

    if (cpu_policy == POLICY_UNSPECIFIED)
    {
        // Ignoring 'cpu_usage'
        
        virtual_cpu->usage.max = 0;
        virtual_cpu->usage.average = 0;
        virtual_cpu->usage.min = 0;
        virtual_cpu->usage.max_burst = 0;
    }    
}

void virtual_cpu_destroy_internal (
    virtual_cpu_reference_t virtual_cpu_reference)
{
    p_virtual_cpu_t virtual_cpu;

    virtual_cpu = (p_virtual_cpu_t) virtual_cpu_reference;
    
    memory_deallocate (virtual_cpu);
}

