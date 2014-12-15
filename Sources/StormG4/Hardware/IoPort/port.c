/* $chaos: port.c,v 1.6 2002/10/22 21:11:31 per Exp $ */
/* Abstract: I/O port management. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#if 0
class_io_port io_port_reserved[] =
{
  /* Timers */

  { CLASS_IO_PORT, "First timer (real time clock)", NULL, { 0, 0, 0 }, NULL, 
    0x0040,  1 },
  { CLASS_IO_PORT, "Second timer (memory refresh)", NULL, { 0, 0, 0 }, NULL,   
    0x0041,  1 },

  /* Interrupt controllers. */

  { CLASS_IO_PORT, "Primary interrupt controller", NULL, { 0, 0, 0 }, NULL,   
    0x0020, 32 },
  { CLASS_IO_PORT, "Secondary interrupt controller", NULL, { 0, 0, 0 }, NULL,   
    0x00A0, 32 },

  /* FPU. */

  { CLASS_IO_PORT, "Floating point unit", NULL, { 0, 0, 0 }, NULL,   
    0x00F8, 16 },

  /* DMA. */

  { CLASS_IO_PORT, "Primary DMA controller", NULL, { 0, 0, 0 }, NULL,   
    0x0000, 32 },
  { CLASS_IO_PORT, "DMA page register", NULL, { 0, 0, 0 }, NULL,   
    0x0080, 16 },
  { CLASS_IO_PORT, "Secondary DMA controller", NULL, { 0, 0, 0 }, NULL,   
    0x00C0, 32 },
};
#endif

/* Set up data structures for port allocation. */
return_t io_port_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    return STORM_RETURN_SUCCESS;
}

/* Register a port range. */
return_t io_port_register (unsigned int start UNUSED, size_t ports UNUSED, 
    const char *description UNUSED)
{
    return STORM_RETURN_SUCCESS;
}

/* Unregister a port range. */
return_t io_port_unregister (unsigned int start UNUSED)
{
    return STORM_RETURN_SUCCESS;
}
