/* $Id: console.c,v 1.5 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Console server. Will eventually be 100% ANSI escape
             sequence compatible. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#include <enviroment.h>
#include <memory_inlines.h>
#include <string.h>

#include <Classes/console.h>

#include "console.h"
#include "console_output.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//define DEBUG_LEVEL DEBUG_LEVEL_NONE
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
    video_cursor_t video_cursor;
    video_mode_t video_mode;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

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
    /* Set the correct videomode for this console. */

    if (console->width != current_console->width ||
        console->height != current_console->height ||
        console->depth != current_console->depth ||
        console->type != current_console->type)
    {
      video_mode.width = console->width;
      video_mode.height = console->height;
      video_mode.depth = console->depth;
      video_mode.mode_type = console->type;
      
      if (video$mode_set (&video, &video_mode) != VIDEO_RETURN_SUCCESS)
      {
        /* FIXME: Fail and return here. */
      }
    }

    /* Move the cursor. */
    /* FIXME: library_video should have a function for this. */
    if (console->keyboard_cursor_visibility)
    {
      video_cursor.x = console->cursor_x;
      video_cursor.y = console->cursor_y;
    }
    else
    {
      video_cursor.x = console->width + 1;
      video_cursor.y = console->height + 1;
    }

        video$set_cursor_place (&video, &video_cursor);
    }

    if (console->type == VIDEO_MODE_TYPE_TEXT)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s copying data.\n",
            __FILE__, __FUNCTION__);
        
        memory_copy (console->output, console->buffer, console->width * 
            console->height * sizeof (character_t));
    }

    if (console->mouse_cursor_visibility)
    {
        mouse_cursor_draw (console->width, console->height, TRUE);    
    }

    current_console = console;
} 
