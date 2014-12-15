
#define INTERFACE_EVENT_SUPPLIER_FACTORY_ID 0x8001

enum
{
	METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID,
	METHOD_EVENT_SUPPLIER_FACTORY_DESTROY_ID,

	METHOD_EVENT_SUPPLIER_FACTORY_NUMBER
};

typedef void (event_supplier_factory_create_t) (context_t context, 
    event_supplier_reference_t event_supplier);
typedef event_supplier_factory_create_t * p_event_supplier_factory_create_t;

typedef void (event_supplier_factory_destroy_t) (context_t context, 
    event_supplier_reference_t event_supplier);
typedef event_supplier_factory_destroy_t * p_event_supplier_factory_destroy_t;

typedef struct
{
    p_event_supplier_factory_create_t create;
    p_event_supplier_factory_destroy_t destroy;
    
} event_supplier_factory_interface_table_t;

typedef event_supplier_factory_interface_table_t * 
    p_event_supplier_factory_interface_table_t;
