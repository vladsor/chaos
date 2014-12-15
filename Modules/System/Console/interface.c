/* $Id: connection.c,v 1.4 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Connection handling in the land of Oz. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include <unicode.h>

//#include <Classes/kernel.h>
#include <Classes/console.h>
#include <Classes/integer.h>
#include <Classes/stream_channel.h>

#include <Interfaces/video.h>
#include <Interfaces/keyboard.h>
#include <Interfaces/mouse.h>

#include "console_output.h"
#include "console.h"
#include "charset.h"
#include "interface.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

handle_t keyboard_events = {HANDLE_HEADER_EMPTY, NULL};
handle_t mouse_events = {HANDLE_HEADER_EMPTY, NULL};
handle_t video = {HANDLE_HEADER_EMPTY, NULL};

/* Open a new console with the requested attributes. */
static return_t interface_console_create (context_t *context, 
    console_attribute_t *console_attribute)
{    
    console_t *console = NULL;
    video_mode_t video_mode;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    memory_allocate ((void **) &console, sizeof (console_t));
    memory_set_uint8 ((uint8_t *) console, 0, sizeof (console_t));

    /* Fill in some required stuff. */
        
    console->width = console_attribute->width;
    console->height = console_attribute->height;
    console->depth = console_attribute->depth;
    console->type = console_attribute->mode_type;
        
    console->cursor_x = 0;
    console->cursor_y = 0;
        
    console->cursor_saved_x = -1;
    console->cursor_saved_y = -1;

    console->wants_keyboard = TRUE;
    
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

{
    class_id_t stream_channel_class_id = CID_NONE;
    stream_channel_create_parameters_t parameters;
    handle_t intg = {HANDLE_HEADER_EMPTY, NULL};

    global_namespace_resolve ("/storm/classes/stream_channel", &intg);
    register_object_open (&intg, IID_INTEGER);
    integer$get (&intg, &stream_channel_class_id);
    register_object_close (&intg);

    parameters.block_size = sizeof (char);
    parameters.max_blocks = 20;
    register_object_create (&console->ikeyboard_buffer, stream_channel_class_id, 
        &parameters);
    
    register_handle_clone (&console->ikeyboard_buffer, 
        &console->okeyboard_buffer, 0);
    register_object_open (&console->ikeyboard_buffer, IID_INPUT_STREAM);
    register_object_open (&console->okeyboard_buffer, IID_OUTPUT_STREAM);
}        
    /* Is this the first console? If so, activate it. */

    if (current_console == NULL)
    {
        current_console = console;
        console->output = screen;
          
//        if (has_video)
        {
            /* Try to set the requested video mode. */
            /* FIXME: Error handling and return values! */
            
            video_mode.width = console_attribute->width;
            video_mode.height = console_attribute->height;
            video_mode.depth = console_attribute->depth;
            video_mode.mode_type = console_attribute->mode_type;
                        
            if (video$mode_set (&video, &video_mode) != 0)
            {
//                return -1;
            }
        }
/*        
        else
        {
            return -1;
        }
*/        
    }        

    console_link (console);
//    console_flip (*our_console);

    (console_t *) context->object_data = console;
    
    /* We have added a new console. */
        
    number_of_consoles++;
    
    return 0;
}

object_create_method_t console_create_method =
{
    &interface_console_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

static return_t interface_console_destroy (context_t *context UNUSED)
{
    return 0;
}

object_destroy_method_t console_destroy_method =
{
    &interface_console_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static return_t interface_console_output (context_t *context, char *text)
{
    console_t *console = (console_t *) context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %s)\n",
        __FILE__, __FUNCTION__, console, text);
  
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
    
    return 0;
}

static return_t interface_console_output_at (context_t *context, int x, int y, 
    char *text)
{
    console_t *console = (console_t *) context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
    
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
    
    return 0;
}

static return_t interface_console_keyboard_cursor_set (context_t *context,
    bool enabled)
{
    console_t *console = (console_t *) context->object_data;
    
    keyboard_cursor_set (console, enabled);
    
    return 0;
}

static return_t interface_console_mouse_cursor_set (context_t *context, 
    bool visible)
{
    console_t *console = (console_t *) context->object_data;
    
    if (console->mouse_cursor_visibility != visible)
    {
        console->mouse_cursor_visibility = visible;

        mouse_cursor_draw (console->width, console->height, visible);
    }
    
    return 0;
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

static return_t interface_console_set_enabled_keyboard (context_t *context, 
    bool enabled)
{
    console_t *console = (console_t *) context->object_data;
    
    console->wants_keyboard = enabled;

    return 0;
}

static return_t interface_console_set_enabled_mouse (context_t *context, 
    bool enabled)
{
    console_t *console = (console_t *) context->object_data;
    
    console->wants_mouse = enabled;

    return 0;
}    

/* Change the video mode for this console. */

static return_t interface_console_video_mode_set (context_t *context,
    console_attribute_t *console_attribute)
{
    console_t *console = (console_t *) context->object_data;
    video_mode_t video_mode;
      
    video_mode.width = console_attribute->width;
    video_mode.height = console_attribute->height;
    video_mode.depth = console_attribute->depth;
    video_mode.mode_type = console_attribute->mode_type;
      
    if (video$mode_set (&video, &video_mode) != VIDEO_RETURN_SUCCESS)
    {
        return -1;
    }
    else
    {
        console->width = console_attribute->width;
        console->height = console_attribute->height;
        console->depth = console_attribute->depth;
        console->type = console_attribute->mode_type;
        
        console->cursor_x = 0;
        console->cursor_y = 0;
        
        console->cursor_saved_x = -1;
        console->cursor_saved_y = -1;
    }
      
    return 0;
}

static console_output_method_t console_output_method =
{
    CONSOLE_OUTPUT_METHOD (interface_console_output)
};

static method_t *console_methods[] = 
{
    (method_t *) &console_output_method,
};

#define number_of_console_methods 1

static return_t interface_console_read (context_t *context, uint8_t *data, 
    uint32_t count)
{
    console_t *console = (console_t *) context->object_data;
    int i=0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, context, data, count);

    input_stream$read (&current_console->ikeyboard_buffer,
        data, count);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s [%c]\n",
        __FILE__, __FUNCTION__, data[0]);
/*
while(1);    
    for (i=0;i<count;i++)
    {
        while (!console->buffer_full && console->buffer_start == 
            console->buffer_end);
            
        data[i] = console->keyboard_buffer[console->buffer_end];
        
        if (console->buffer_full)
        {
            console->buffer_full = FALSE;
        }
        
        console->buffer_end++;
        console->buffer_end %= 20;
    }
*/    
    return 0;
}

static input_stream_read_method_t console_read_method =
{
    INPUT_STREAM_READ_METHOD (interface_console_read)
};

static method_t *input_stream_methods[] = 
{
    (method_t *) &console_read_method,
};

#define number_of_input_stream_methods 1

static return_t interface_console_write (context_t *context, uint8_t *data, 
    uint32_t count)
{
    console_t *console = (console_t *) context->object_data;
    char text[2] = {0, 0};
    int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u): ",
        __FILE__, __FUNCTION__, context, data, count);

    for (i=0;i<count;i++)
    {
        text[0] = data[i];
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "{%c}%X", data[i], data[i]);

        console_output (console, text);
    }
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            ".\n");
    
    return 0;
}

static output_stream_write_method_t console_write_method =
{
    OUTPUT_STREAM_WRITE_METHOD (interface_console_write)
};

static method_t *output_stream_methods[] = 
{
    (method_t *) &console_write_method,
};

#define number_of_output_stream_methods 1

static return_t events_process (void)
{
    keyboard_packet_t keyboard_packet;
    
    while (TRUE)
    {
        event_observer$read (&keyboard_events, &keyboard_packet);

        console_keyboard_handler (&keyboard_packet);
    }
}

thread_t thr;
static void keyboard_register_handler (void)
{
    thread$create (&handle_thread, &thr, &events_process);
}

static method_t *control_methods[] = 
{
    (method_t *) &console_create_method,
    (method_t *) &console_destroy_method,
};

#define number_of_control_methods 2

static interface_id_t console_control_id;
static interface_id_t console_interface_ids[3];
static class_id_t console_class_id;
static handle_t class = {HANDLE_HEADER_EMPTY, NULL};
static class_id_t integer_class_id;

static thread_t thr_test;
static void test_thread (void)
    {
        handle_t console = {HANDLE_HEADER_EMPTY, NULL};
        handle_t istr = {HANDLE_HEADER_EMPTY, NULL};
        handle_t ostr = {HANDLE_HEADER_EMPTY, NULL};
        char text[] = "Test string\nNext line\n";
        
        console_attribute_t attribute = {80,25,1,VIDEO_MODE_TYPE_TEXT};
        register_object_create (&console, console_class_id, &attribute);
        register_handle_clone (&console, &istr, 0);
        register_handle_clone (&console, &ostr, 0);

        register_object_open (&ostr, IID_OUTPUT_STREAM);
        output_stream$write (&ostr, text, string_length (text));

        register_object_open (&istr, IID_INPUT_STREAM);
        
        for (;;)
        {
            char tmp;
            input_stream$read (&istr, &tmp, 1);
            output_stream$write (&ostr, &tmp, 1);
        }
    }

/* Main function. */

return_t console_main (int argc UNUSED, char *argv[] UNUSED)
{
//  system_call_memory_reserve (CONSOLE_VIDEO_MEMORY, CONSOLE_VIDEO_MEMORY_SIZE,
//                              (void **) &screen);

    screen = (character_t *) CONSOLE_VIDEO_MEMORY;

    global_namespace_resolve ("/devices/keyboard-events", &keyboard_events);
    register_object_open (&keyboard_events, IID_EVENT_OBSERVER);
    
    global_namespace_resolve ("/devices/mouse-events", &mouse_events);
    register_object_open (&mouse_events, IID_EVENT_OBSERVER);
    
    global_namespace_resolve ("/devices/vga", &video);
    register_object_open (&video, IID_VIDEO);

    keyboard_register_handler ();

    register_interface_register (&console_control_id, IID_CONSOLE_CONTROL,
        INTERFACE_TYPE_CONTROL, number_of_control_methods, control_methods, 
        NULL);
    register_interface_register (&console_interface_ids[0], IID_CONSOLE, 
        INTERFACE_TYPE_DYNAMIC, number_of_console_methods, console_methods, 
        NULL);
    register_interface_register (&console_interface_ids[1], IID_INPUT_STREAM, 
        INTERFACE_TYPE_DYNAMIC, number_of_input_stream_methods, 
        input_stream_methods, NULL);
    register_interface_register (&console_interface_ids[2], IID_OUTPUT_STREAM, 
        INTERFACE_TYPE_DYNAMIC, number_of_output_stream_methods, 
        output_stream_methods, NULL);
    register_class_register (&console_class_id, CID_CONSOLE, CLASS_TYPE_DYNAMIC,
        3, console_interface_ids, console_control_id);

    global_namespace_resolve ("/storm/classes/integer", &class);
    register_object_open (&class, IID_INTEGER);
    integer$get (&class, &integer_class_id);
    register_object_close (&class);
    
    register_object_create (&class, integer_class_id, &console_class_id);
    global_namespace_bind ("/storm/classes/console", &class);
    
//    thread_create (&thr_test, &test_thread);
             
    return 0;
}
