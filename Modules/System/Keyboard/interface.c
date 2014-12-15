#include <enviroment.h>
#include <string.h>

#include <Interfaces/keyboard.h>
#include <Interfaces/mouse.h>

#include <Classes/integer.h>
#include <Classes/event_channel.h>

#include "controller.h"
#include "keyboard.h"
#include "mouse.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

class_id_t event_channel_class_id = CID_NONE;
handle_t keyboard_event_channel = {HANDLE_HEADER_EMPTY, NULL};
handle_t mouse_event_channel = {HANDLE_HEADER_EMPTY, NULL};


static void keyboard_irq_handler (void)
{
   handle_event ();
}
/* Handler for the keyboard IRQ. */

static void keyboard_register_irq_handler (void)
{
//  system_thread_name_set ("Keyboard IRQ handler");

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Registering keyboard IRQ handler: %p.\n",
        keyboard_irq_handler);

  /* Register our IRQ. Must be done by the IRQ handler thread, so we
     do it here. */

    irq_register (KEYBOARD_IRQ, keyboard_irq_handler);
}

/* Main function for the keyboard handling. */

return_t keyboard_main (int argc UNUSED, char *argv[] UNUSED)
{
    event_channel_create_parameters_t parameters;
    handle_t intg = {HANDLE_HEADER_EMPTY, NULL};
    const char *message;

    /* Flush any pending input. */

    keyboard_clear_input ();

    message = keyboard_init ();

    if (message != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "%s\n", message);
	
        return -1;
    }

    global_namespace_resolve ("/storm/classes/event_channel", &intg);
    register_object_open (&intg, IID_INTEGER);
    integer$get (&intg, &event_channel_class_id);
    register_object_close (&intg);

    parameters.event_data_size = sizeof (keyboard_packet_t);
    parameters.max_events = 50;
    register_object_create (&keyboard_event_channel, event_channel_class_id, 
        &parameters);
    global_namespace_bind ("/devices/keyboard-events", &keyboard_event_channel);
    register_object_open (&keyboard_event_channel, IID_EVENT_PROVIDER);

    /* Handle the IRQs. */

    keyboard_register_irq_handler ();

    /* Update the keyboard LEDs. */

    keyboard_update_leds ();

    /* No keys pressed at startup. */

    keyboard_reset_pressed_keys ();
    
    keyboard_load_maps ();
    
    return 0;
}

static void mouse_irq_handler (void)
{
    handle_event ();
}

/* Handler for the mouse IRQ. */

static void mouse_register_irq_handler (void)
{
//  system_thread_name_set ("Mouse IRQ handler");

    /* Register our IRQ. */

    irq_register (MOUSE_IRQ, mouse_irq_handler);
}

/* Main function for the mouse handling. */

return_t mouse_main (int argc UNUSED, char *argv[] UNUSED)
{
    event_channel_create_parameters_t parameters;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Mouse main.\n");

    /* Initialise a PS/2 mouse port, if found. */

    mouse_init ();
    
    parameters.event_data_size = sizeof (mouse_event_t);
    parameters.max_events = 50;
    register_object_create (&mouse_event_channel, event_channel_class_id, 
        &parameters);
    global_namespace_bind ("/devices/mouse-events", &mouse_event_channel);

    mouse_register_irq_handler ();

    return 0;
}
