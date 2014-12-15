/* $Id: port.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
/* Abstract: Handle port I/O. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA */

/* Define as TRUE to get lots of debug information. */

#define DEBUG FALSE

#include <storm/state.h>

#include <storm/generic/bit.h>
#include <storm/generic/debug.h>
#include <storm/generic/dispatch.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>
#include <storm/generic/port.h>
#include <storm/generic/process.h>
#include <storm/generic/return_values.h>
#include <storm/generic/string.h>
#include <storm/generic/thread.h>
#include <storm/generic/types.h>

#include <storm/ia32/gdt.h>
#include <storm/ia32/port.h>
#include <storm/ia32/tss.h>

void register_internal_ports (void)
{
  /* Timers. */

  port_range_link (0x0040,  1, "First timer");
  port_range_link (0x0041,  1, "Second timer");

  /* Interrupt controllers. */

  port_range_link (0x0020, 32, "Primary interrupt controller");
  port_range_link (0x00A0, 32, "Secondary interrupt controller");

  /* FPU. */

  port_range_link (0x00F8, 16, "Floating point unit");
}

void port_fix (unsigned int start, unsigned int ports)
{
  unsigned int port;
  int index;

  /* If the TSS is too small, expand it. */
  
  if (current_tss->iomap_size < BIT_IN_BYTES (start + ports - 1))
  {
    int old_iomap_size = current_tss->iomap_size;
    storm_tss_type *old_tss = current_tss;

    DEBUG_MESSAGE (DEBUG, "%u bytes wasn't enough to hold this I/O map (will be %u bytes).",
                   current_tss->iomap_size, BIT_IN_BYTES (start + ports - 1));
    DEBUG_MESSAGE (DEBUG, "Reallocating TSS.");

    current_tss = memory_global_allocate (sizeof (storm_tss_type) +
                                          BIT_IN_BYTES (start + ports));
    
    DEBUG_MESSAGE (DEBUG, "Allocating %u bytes.",
                   (sizeof (storm_tss_type) + BIT_IN_BYTES (start + ports - 1)));

    memory_copy (current_tss, old_tss,
                 sizeof (storm_tss_type) + old_iomap_size);
                                                
    current_tss->iomap_size = BIT_IN_BYTES (start + ports);
    memory_set_u8 (current_tss->iomap + old_iomap_size,
                   0xFF, current_tss->iomap_size - old_iomap_size);
    DEBUG_MESSAGE (DEBUG, "Clearing %u bytes", current_tss->iomap_size -
                   old_iomap_size)
    thread_unlink (old_tss->thread_id);
    current_tss_node = thread_link (current_tss);

    switch (dispatch_task_flag)
    {
      case 0:
      {
        gdt_setup_tss_descriptor (SELECTOR_TSS1 >> 3, current_tss, 3,
                                  sizeof (storm_tss_type) + 
                                  current_tss->iomap_size);
        cpu_set_tr (SELECTOR_TSS1);
        break;
      }
      
      case 1: 
      {
        gdt_setup_tss_descriptor (SELECTOR_TSS2 >> 3, current_tss, 3,
                                  sizeof (storm_tss_type) + 
                                  current_tss->iomap_size);
        cpu_set_tr (SELECTOR_TSS2);
        break;
      }
    }

    memory_global_deallocate (old_tss);
  }

  mutex_kernel_signal (&tss_tree_mutex);

  /* Add the port range to the callers I/O-map. */

  for (port = start; port < start + ports; port++)
  {
    DEBUG_MESSAGE (DEBUG, "Clearing bit %u in the I/O map", port);
    BIT_CLEAR (current_tss->iomap[port / 8],
               port % 8);
  }

  /* Since this thread has got a new TSS, we have to check if it is an
     IRQ handler. If so, we must update the TSS pointer. */

  for (index = 0; index < IRQ_LEVELS; index++)
  {
    if (irq[index].allocated && irq[index].thread_id == current_thread_id)
    {
      irq[index].tss = current_tss;
    }
  }
}
