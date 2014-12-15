
#define INTERFACE_INTEGER_VALUE_CONTROL_ID 0x0002

enum 
{
    METHOD_CONTROL_CREATE_ID,
    METHOD_CONTROL_DESTROY_ID,
    
    METHOD_CONTROL_NUMBER
};

typedef struct
{
    p_void_t (*create) (context_t context, uint32_t value);
    void (*destroy) (context_t context, p_void_t object_data);

} integer_control_interface_table_t;

typedef integer_control_interface_table_t * p_integer_control_interface_table_t;

extern interface_reference_t integer_control_interface_register (
    p_integer_control_interface_table_t table);
