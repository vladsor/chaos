#define IID_IO_PORT 0x00000601

enum
{
    MID_IO_PORT_AREGISTER,
    MID_IO_PORT_UNREGISTER,
};

typedef return_t (io_port_aregister_function_t) (unsigned int start, 
    size_t ports, char *description);
typedef return_t (io_port_unregister_function_t) (unsigned int start);
    
typedef struct
{
    io_port_aregister_function_t *aregister;
    io_port_unregister_function_t *unregister;
} io_port_interface_t;

#define io_port$aregister(handle,start,ports,description) \
    ((io_port_interface_t *) ((handle)->functions))->aregister ( \
        (start), (ports), (description))

#define io_port$unregister(handle,start) \
    ((io_port_interface_t *) ((handle)->functions))->unregister ( \
        (start))

