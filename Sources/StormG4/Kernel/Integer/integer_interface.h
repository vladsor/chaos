
typedef struct
{
    void (*get) (context_t context, p_uint32_t value);
    void (*set) (context_t context, uint32_t value);

} integer_interface_table_t;

typedef integer_interface_table_t * p_integer_interface_table_t;

extern interface_reference_t integer_interface_register (
    p_integer_interface_table_t table);

