/* $Id: connection.c,v 1.4 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Connection handling in the land of Oz. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include <unicode.h>

//#include <Classes/kernel.h>
#include <Classes/console.h>
//#include <Classes/integer.h>
//#include <Classes/stream_channel.h>

#include <Interfaces/video.h>
#include <Interfaces/keyboard.h>
#include <Interfaces/mouse.h>

#include "Include/console_output.h"
#include "Include/console.h"
#include "Include/charset.h"
#include "Include/interface.h"

#include "Include/console_factory_interface.h"
#include "Include/console_control_interface.h"
#include "Include/input_stream_interface.h"
#include "Include/output_stream_interface.h"

#include "Include/handler_interface.h"

#include "Include/console_manager_class.h"
#include "Include/console_class.h"

#include "Include/keyboard_event_class.h"
#include "Include/mouse_event_class.h"

#define DEBUG_MODULE_NAME "Console"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

handle_reference_t video = REFERENCE_NULL;

/* Open a new console with the requested attributes. */
static uint64_t interface_console_create (context_t context UNUSED, 
    uint32_t console_width, uint32_t console_height, uint32_t console_depth, 
    uint32_t console_mode_type)
{    
    console_t *console = NULL;
//    video_mode_t video_mode;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%u, %u, %u, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        console_width, console_height, console_depth, console_mode_type);

    memory_allocate ((void **) &console, sizeof (console_t));
    memory_clear ((uint8_t *) console, sizeof (console_t));

    /* Fill in some required stuff. */
        
    console->width = console_width;
    console->height = console_height;
    console->depth = console_depth;
    console->type = console_mode_type;
        
    console->cursor_x = 0;
    console->cursor_y = 0;
        
    console->cursor_saved_x = -1;
    console->cursor_saved_y = -1;

    console->wants_keyboard = TRUE;
    
    console->keyboard_cursor_visibility = TRUE;
    console->mouse_cursor_visibility = FALSE;

    console->scrollable = FALSE;
        
    console->state = CONSOLE_STATE_CHARACTER;
    console->numeric_argument_index = 0;
        
    console->current_attribute = CONSOLE_DEFAULT_ATTRIBUTE;
        
    /* Allocate memory for a buffer for this console. */
        
    if (console->type == VIDEO_MODE_TYPE_TEXT)
    {
        memory_allocate ((void **) &(console->buffer), console->width *
            console->height * sizeof (character_t));
            
        memory_set_uint8 ((uint8_t *) console->buffer, 0, console->width *
            console->height * sizeof (character_t));
    }
    else
    {
        memory_allocate ((void **) &(console->buffer), console->width *
            console->height * console->depth);
    }
        
    console->output = console->buffer;
    console->lock = FALSE;
    
    console->echo_enabled = TRUE;

    /* Is this the first console? If so, activate it. */
#if 0
    if (current_console == NULL)
    {
        current_console = console;
        console->output = screen;
          
//        if (has_video)
        {
            /* Try to set the requested video mode. */
            /* FIXME: Error handling and return values! */
            
            video$mode_set (video, console_width, console_height, console_depth,
                console_mode_type);
        }
    }        
#endif

    console_link (console);
    console_flip (console);

//    (console_t *) context->object_data = console;
    
    /* We have added a new console. */
        
    number_of_consoles++;
    
    return (address_t) console;
}

static void interface_console_destroy (context_t context UNUSED, 
    uint64_t object_data)
{
    console_t *console = (console_t *) (address_t) object_data;

    memory_deallocate (console->buffer);
    memory_deallocate (console);
}

static console_factory_interface_table_t console_factory_table =
{
    create: &interface_console_create,
    destroy: &interface_console_destroy,
    clone: NULL,
};

static void interface_console_output (context_t context, const wchar_t *text)
{
    console_t *console = (console_t *) (address_t) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        console, text);
  
    if (console != NULL/* && has_video*/)
    {
        /* This is not purely correct, but it's better than
           nothing... */
        /* FIXME: library_semaphore. */
/*        
        while ((*our_console)->lock == TRUE)
        {
          system_call_dispatch_next ();
        }
*/        
        console->lock = TRUE;
        
        console_output (console, text);
        
        console->lock = FALSE;
    }
}

static void interface_console_output_at (context_t context, int x, int y, 
    const wchar_t *text)
{
    console_t *console = (console_t *) (address_t) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%u, %u, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        x, y, text);
    
    if (console != NULL/* && has_video*/)
    {
        /* This is not purely correct, but it's better than
           nothing... */
        /* FIXME: library_semaphore. */
/*        
        while ((*our_console)->lock == TRUE)
        {
          system_call_dispatch_next ();
        }
*/
        if (x >= 0 && x < console->width &&
            y >= 0 && y < console->height)
        {
            console->lock = TRUE;
            
            console_output_at (console, x, y, text);
            
            console->lock = FALSE;
        }
    }
}

static void interface_console_keyboard_cursor_set (context_t context,
    bool visible)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    
    keyboard_cursor_set (console, visible);
}

static void interface_console_mouse_cursor_set (context_t context, 
    bool visible)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    
    if (console->mouse_cursor_visibility != visible)
    {
        console->mouse_cursor_visibility = visible;

        mouse_cursor_draw (console->width, console->height, visible);
    }
}
/*    
    case IPC_CONSOLE_GET_HOT_KEYS_AMOUNT:
    {
      message_parameter_type reply_message;
      
      reply_message.protocol = IPC_PROTOCOL_CONSOLE;
      reply_message.data = &number_of_hot_keys;
      reply_message.length = sizeof (unsigned int);
      reply_message.block = TRUE;
      ipc_send (ipc_structure->output_mailbox_id, &reply_message);
      
      break;
    }
    
    case IPC_CONSOLE_GET_HOT_KEYS_INFO:
    {
      message_parameter_type reply_message;
      
      reply_message.protocol = IPC_PROTOCOL_CONSOLE;

      memory_allocate ( (void **)&reply_message.data, number_of_hot_keys * 
                       sizeof (hot_key_record_type));
      memory_copy (reply_message.data, table_of_hot_keys, number_of_hot_keys * 
                   sizeof (hot_key_record_type));
      reply_message.length =  number_of_hot_keys * sizeof (hot_key_record_type);
      reply_message.block = TRUE;

      ipc_send (ipc_structure->output_mailbox_id, &reply_message);
      break;
    }
    
    case IPC_CONSOLE_KEYBOARD_EXTENDED:
    {
      (*our_application)->keyboard_type = CONSOLE_KEYBOARD_EXTENDED;
      break;
    }
    
    case IPC_CONSOLE_KEYBOARD_NORMAL:
    {
      (*our_application)->keyboard_type = CONSOLE_KEYBOARD_NORMAL;
      break;
    }
*/

static void interface_console_keyboard_enable (context_t context, 
    bool enabled)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    
    console->wants_keyboard = enabled;
}

static void interface_console_mouse_enable (context_t context, 
    bool enabled)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    
    console->wants_mouse = enabled;
}    

/* Change the video mode for this console. */

static void interface_console_video_mode_set (context_t context,
    uint32_t video_mode_width, uint32_t video_mode_height, 
    uint32_t video_mode_depth, uint32_t video_mode_type)
{
    console_t *console = (console_t *) (address_t) context.object_data;
     
    video$mode_set (video, video_mode_width, video_mode_height, 
        video_mode_depth, video_mode_type);
    {
        console->width = video_mode_width;
        console->height = video_mode_height;
        console->depth = video_mode_depth;
        console->type = video_mode_type;
        
        console->cursor_x = 0;
        console->cursor_y = 0;
        
        console->cursor_saved_x = -1;
        console->cursor_saved_y = -1;
    }
}

static console_control_interface_table_t console_control_table = 
{
    output:                 &interface_console_output,
    output_at:              &interface_console_output_at,
    keyboard_enable:        &interface_console_keyboard_enable,
    keyboard_cursor_set:    &interface_console_keyboard_cursor_set,
    mouse_enable:           &interface_console_mouse_enable,
    mouse_cursor_set:       &interface_console_mouse_cursor_set,
    video_mode_set:         &interface_console_video_mode_set,
};    

static uint32_t interface_console_read (context_t context, sequence_t bytes)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    uint32_t counter = 0;
	p_keyboard_event_data_t keyboard_packet;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        console, bytes.data, bytes.count);

    for (counter = 0; counter < bytes.count; counter++)
    {
        count_down (&console->keyboard_count);
        
        keyboard_packet = &console->keyboard_buffer[
            console->keyboard_buffer_tail];
        current_console->keyboard_buffer_tail++;
        current_console->keyboard_buffer_tail %= 20;

        if (keyboard_packet->key_pressed)
        {
            if (keyboard_packet->has_character_code)
            {
                if (keyboard_packet->character < 256)
                {
                    ((char *) bytes.data)[counter] = 
                        (char) keyboard_packet->character;
                }    
            }
        }        
    }    

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s: [%c]\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        ((char *) bytes.data)[0]);
        
    return counter;
}

static input_stream_interface_table_t input_stream_table =
{
    read: &interface_console_read,
};

static uint32_t interface_console_write (context_t context, sequence_t bytes)
{
    console_t *console = (console_t *) (address_t) context.object_data;
    wchar_t text[2] = {0, 0};
    uint32_t i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        console, bytes.data, bytes.count);

    for (i = 0; i < bytes.count; i++)
    {
        text[0] = ((p_uint8_t) bytes.data)[i];
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "{%c}%X", (char) text[0], (uint32_t) text[0]);

        console_output (console, (const wchar_t *) text);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, ".\n");
    
    return bytes.count;
}

static output_stream_interface_table_t output_stream_table =
{
    write: &interface_console_write,
};

static object_reference_t system_console;
static class_reference_t console_class;
static interface_reference_t console_interfaces[3];

//static handle_reference_t console_factory_handle;
static object_reference_t console_manager;
static class_reference_t console_manager_class;
static interface_reference_t console_manager_interfaces[1];
//static interface_reference_t keyboard_handler_interface;
static event_consumer_interface_reference_t 
    console_manager_consumer_interfaces[2];
    
static event_consumer_reference_t key_consumer;
static event_supplier_reference_t key_supplier;
static event_queue_reference_t key_queue;

//static event_supplier_reference_t mouse_supplier;

object_reference_t keyboard_object;
object_reference_t mouse_object;
object_reference_t vga;

/* Main function. */

return_t console_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        argc, argv, envp);
    
//  system_call_memory_reserve (CONSOLE_VIDEO_MEMORY, CONSOLE_VIDEO_MEMORY_SIZE,
//                              (void **) &screen);

    screen = (character_t *) CONSOLE_VIDEO_MEMORY;

    keyboard_object = namespace$resolve (kernel_handle_namespace, 
        L"/devices/keyboard");

    key_supplier = keyboard$supplier$create (keyboard_object);

//    mouse_object = namespace$resolve (kernel_handle_namespace, 
//        L"/devices/mouse");

//    mouse_supplier = mouse$supplier$create (mouse_object);

    vga = namespace$resolve (kernel_handle_namespace, L"/devices/video");
    video = video$handle$create (vga);
    
    console_manager_interfaces[0] = console_factory_interface_register (
        &console_factory_table);

    console_manager_consumer_interfaces[0] = 
        keyboard_consumer_interface_register (EVENT_CONSUMER_TYPE_PUSH, 
            &console_keyboard_handler, REFERENCE_NULL, REFERENCE_NULL);

    console_manager_consumer_interfaces[1] = 
        mouse_consumer_interface_register (EVENT_CONSUMER_TYPE_PUSH, 
            &console_mouse_handler, REFERENCE_NULL, REFERENCE_NULL);

    console_manager_class = console_manager_class_register (
        console_manager_interfaces, NULL, console_manager_consumer_interfaces);
    
    console_manager = object_create (console_manager_class, SECURITY_CURRENT, 
        empty_seq, 0);

    console_interfaces[0] = console_control_interface_register (
        &console_control_table);
    console_interfaces[1] = input_stream_interface_register (
        &input_stream_table);
    console_interfaces[2] = output_stream_interface_register (
        &output_stream_table);

    console_class = console_class_register (console_interfaces, NULL, NULL, 
        console_manager_interfaces[0]);

    key_consumer = keyboard$consumer$create (console_manager);
    key_queue = event_queue_create (keyboard_description_register (), 
        EVENT_QUEUE_TYPE_SYNCHRONOUS, 0);
    event_supplier_set_queue (key_supplier, key_queue);
    event_consumer_set_queue (key_consumer, key_queue);

    system_console = console$object$create (console_class, 80, 25, 1, 
        VIDEO_MODE_TYPE_TEXT);

    namespace$bind (kernel_handle_namespace, L"/devices/SystemConsole", 
        system_console);
    namespace$bind (kernel_handle_namespace, L"/Classes/Console", 
        console_class);

    {        
        handle_reference_t system_console_handle;
        system_console_handle = console_control$handle$create (system_console);
        console_control$output (system_console_handle, L"Test string.\n");
    }    
             
    return 0;
}

