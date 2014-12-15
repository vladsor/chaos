
#define INTERFACE_IRQ_SUPPLIER_FACTORY_ID 0x0030

typedef void (irq_supplier_factory_create_t) (context_t context, 
    event_supplier_reference_t irq_supplier, uint32_t irq_number);
typedef irq_supplier_factory_create_t * p_irq_supplier_factory_create_t;
        
typedef struct
{
    p_irq_supplier_factory_create_t create;    
    p_event_supplier_factory_destroy_t destroy;

} irq_supplier_factory_interface_table_t;

typedef irq_supplier_factory_interface_table_t * 
    p_irq_supplier_factory_interface_table_t;

static inline event_supplier_reference_t irq_supplier_factory$create (
    object_reference_t object, uint32_t irq_number)
{
	uint32_t pars[] = {(uint32_t) irq_number};
    sequence_t pars_seq = {data: pars, count: 1};
    
    return event_supplier_create (object, EVENT_CLASS_IRQ_ID, pars_seq, 0);
}


