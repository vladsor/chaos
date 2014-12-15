/* $Id: log.c,v 1.2 2001/02/10 21:25:14 jojo Exp $ */
/* Abstract: Log server for chaos. This server's purpose is to collect
             debug and/or warnings from servers and from the
             kernel. */
/* Author: Per Lundberg <plundis@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */

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
   USA. */

#include "config.h"

static console_structure_type monitor_console;

/* An empty tag list. */

tag_type empty_tag =
{
  0, 0, ""
};

volatile bool irq_active[16];
volatile bool old_irq_active[16];

event_parameter_type event_par[16] = {
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },

  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },

  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },

  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
  { EVENT_CLASS_NONE, 0, NULL },
};

#define irq_handler(n)              \
static void irq##n##_handler (event_parameter_type *event_parameter \
  __attribute__ ((unused))) \
{                                   \
  irq_active[n] = TRUE;             \
}

irq_handler (1);
irq_handler (2);
irq_handler (3);
irq_handler (4);
irq_handler (5);
irq_handler (6);
irq_handler (7);
irq_handler (8);
irq_handler (9);
irq_handler (10);
irq_handler (11);
irq_handler (12);
irq_handler (13);
irq_handler (14);
irq_handler (15);

static void print_irq (unsigned int irq_number)
{
  int x_pos =  irq_number < 8 ? irq_number * 6 + 2 : (irq_number - 8) * 6 + 2;
  int y_pos =  irq_number < 8 ? 2 : 4;

  if (irq_active[irq_number])
  {
    console_print_at (&monitor_console, x_pos, y_pos, "*");
    irq_active[irq_number] = FALSE;  
    old_irq_active[irq_number] = TRUE;  
  }
  else
  {
    if (old_irq_active[irq_number])
    {
      console_print_at (&monitor_console, x_pos, y_pos, " ");
      old_irq_active[irq_number] = FALSE;  
    }
  }
}

return_type main (void)
{
  int i;
  
  /* Initialise the memory library. */

  memory_init ();

  /* Set our name. */

  system_process_name_set (PACKAGE_NAME);

  system_call_process_parent_unblock ();
  
  if (console_init (&monitor_console, &empty_tag,
                    IPC_CONSOLE_CONNECTION_CLASS_CLIENT) != 
		    CONSOLE_RETURN_SUCCESS)
  {
    return -1;
  }
        
  if (console_open (&monitor_console, 80, 50, 4, VIDEO_MODE_TYPE_TEXT) != 
      CONSOLE_RETURN_SUCCESS)
  {
    return -1;
  }

  console_clear (&monitor_console);

  console_print (&monitor_console,
           " " PACKAGE_NAME " version " PACKAGE_VERSION "\n");

  console_print (&monitor_console, 
   "IRQ0  IRQ1  IRQ2  IRQ3  IRQ4  IRQ5  IRQ6  IRQ7\n");
  console_print (&monitor_console, 
   "\n");
  console_print (&monitor_console, 
   "IRQ8  IRQ9  IRQ10 IRQ11 IRQ12 IRQ13 IRQ14 IRQ15 \n");

  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_1, irq1_handler, &event_par[1]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_2, irq2_handler, &event_par[2]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_3, irq3_handler, &event_par[3]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_4, irq4_handler, &event_par[4]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_5, irq5_handler, &event_par[5]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_6, irq6_handler, &event_par[6]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_7, irq7_handler, &event_par[7]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_8, irq8_handler, &event_par[8]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_9, irq9_handler, &event_par[9]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_10, irq10_handler, &event_par[10]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_11, irq11_handler, &event_par[11]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_12, irq12_handler, &event_par[12]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_13, irq13_handler, &event_par[13]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_14, irq14_handler, &event_par[14]);
  event_set_handler (SYSTEM_EVENT_QUEUE_INTERRUPTS_15, irq15_handler, &event_par[15]);

  
  while (TRUE)
  {
    for (i = 0 ; i < 16 ; i++)
    {
      print_irq (i);
    }
    system_sleep (10);
  }

}
