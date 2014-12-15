
/* Set up data structures for port allocation. */
extern return_t io_port_init (int argc, char *argv[]);

/* Register a port range. */
extern return_t io_port_register (unsigned int start, size_t ports, 
    char *description);

/* Unregister a port range. */
extern return_t io_port_unregister (unsigned int start);

