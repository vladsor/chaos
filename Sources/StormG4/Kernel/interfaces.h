
typedef interface_reference_t (kernel_interface_init_function_t) (void);
typedef kernel_interface_init_function_t *p_kernel_interface_init_function_t;

enum
{
    KERNEL_INTERFACE_KERNEL_CONTROL_INDEX,
    KERNEL_INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_INDEX,
    KERNEL_INTERFACE_NAMESPACE_INDEX,
    KERNEL_INTERFACE_TIMER_INDEX,
    KERNEL_INTERFACE_STORM_MODULE_FACTORY_INDEX,
    KERNEL_INTERFACE_IRQ_SUPPLIER_FACTORY_INDEX,
    KERNEL_INTERFACE_STORM_PROGRAM_FACTORY_INDEX,
};

typedef struct
{
    const wchar_t *name;
    p_kernel_interface_init_function_t init;
    interface_reference_t interface;
    bool enabled;

} kernel_interface_info_t;

extern kernel_interface_info_t kernel_interfaces_info[];

extern kernel_interface_init_function_t kernel_control_init;
extern kernel_interface_init_function_t flat_namespace_object_factory_init;
extern kernel_interface_init_function_t namespace_init;
extern kernel_interface_init_function_t timer_interface_init;    
extern kernel_interface_init_function_t storm_module_factory_interface_init;    
extern kernel_interface_init_function_t irq_supplier_factory_init;
extern kernel_interface_init_function_t storm_program_factory_interface_init; 
   
