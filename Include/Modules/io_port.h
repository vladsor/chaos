extern handle_t handle_io_port;

static inline return_t io_port_register (unsigned int start, size_t ports, 
    char *description)
{
    return io_port$aregister (&handle_io_port, start, ports, description);
}

static inline return_t io_port_unregister (unsigned int start)
{
    return io_port$unregister (&handle_io_port, start);
}

