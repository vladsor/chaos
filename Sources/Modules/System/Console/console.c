/* $Id: console.c,v 1.5 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Console server. Will eventually be 100% ANSI escape
             sequence compatible. */
/**
 * @author Henrik Hallin <hal@chaosdev.org>
 * @author Per Lundberg <plundis@chaosdev.org> 
 * @author Vladimir Sorokin
 */

/* Copyright 1999-2000 chaos development. */

#include <enviroment.h>
#include <string.h>

#include <Classes/console.h>

#include "Include/console.h"
#include "Include/console_output.h"
#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"Console"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (console_debug_supplier)
#endif

#include <debug/macros.h>

volatile position_t mouse_cursor_position = { 0 , 0 };
volatile character_t character_under_mouse;
volatile character_t mouse_cursor = { '*', 2 };

volatile unsigned int number_of_consoles = 0;
character_t *screen = (character_t *) NULL;
volatile console_t *current_console = NULL;
console_t *console_list = NULL;

//ipc_structure_type video_structure;
//ipc_structure_type keyboard_structure;

volatile bool has_video = FALSE;
volatile bool has_keyboard = FALSE;

volatile unsigned int console_id = 0;

volatile console_t *console_shortcut[12] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/* Link in this console into our linked list of consoles. */

void console_link (console_t *console)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        console);

    if (console_list == NULL)
    {
        console_list = console;
        console_list->next = NULL;
    }
    else
    {
        console->next = (struct console_t *) console_list;
        console_list = console;
    }

    console_shortcut[number_of_consoles] = console;
}

/* Function:    console_flip ()
   Purpose:     Save the console state to current_console->buffer and
                copy the contents of console->buffer to the screen.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console to flip to.
   TODO:        Support switching of video mode. */

void console_flip (console_t *console)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        console);

    if (current_console != NULL)
    {
        if (current_console->mouse_cursor_visibility)
        {
            mouse_cursor_draw (current_console->width, current_console->height, 
                FALSE);    
        }

        current_console->output = current_console->buffer;

        if (current_console->type == VIDEO_MODE_TYPE_TEXT)
        {
            memory_copy (current_console->buffer, screen, 
                current_console->width * current_console->height * 
                sizeof (character_t));
        }
    }

    console->output = screen;
    
    if (has_video)
    {
        uint32_t x, y;
        
        /* Set the correct videomode for this console. */

        if (console->width != current_console->width ||
            console->height != current_console->height ||
            console->depth != current_console->depth ||
            console->type != current_console->type)
        {
      
                /* FIXME: Fail and return here. */
                video$mode_set (video, console->width, console->height, 
                    console->depth, console->type);
        }

        /* Move the cursor. */
        /* FIXME: library_video should have a function for this. */
        if (console->keyboard_cursor_visibility)
        {
            x = console->cursor_x;
            y = console->cursor_y;
        }
        else
        {
            x = console->width + 1;
            y = console->height + 1;
        }

        video$cursor_set (video, x, y);
    }

    if (console->type == VIDEO_MODE_TYPE_TEXT)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s: copying data.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        memory_copy (console->output, console->buffer, console->width * 
            console->height * sizeof (character_t));
    }

    if (console->mouse_cursor_visibility)
    {
        mouse_cursor_draw (console->width, console->height, TRUE);    
    }

    current_console = console;
} 

