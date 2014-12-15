
typedef event_supplier_reference_t 
    (kernel_event_supplier_init_function_t) (void);
typedef kernel_event_supplier_init_function_t * 
    p_kernel_event_supplier_init_function_t;

enum
{
    KERNEL_EVENT_SUPPLIER_INTERFACE_IRQ_INDEX,
    KERNEL_EVENT_SUPPLIER_INTERFACE_DEBUG_INDEX,
};

typedef struct
{
    const wchar_t *name;
    p_kernel_event_supplier_init_function_t init;
    bool enabled;

} kernel_event_supplier_interface_info_t;

extern kernel_event_supplier_interface_info_t 
    kernel_event_supplier_interfaces_info[];

extern kernel_event_supplier_init_function_t irq_supplier_init;
extern kernel_event_supplier_init_function_t debug_supplier_init;

