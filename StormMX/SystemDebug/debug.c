/**
 * @file                debug.c
 * @brief               Code used for debugging the kernel.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.13
 * @date                1998-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include <string.h>

#include "Include/debug.h"
#include "Include/gdb.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

static uint32_t text_attribute = DEBUG_ATTRIBUTE_TEXT;
static uint32_t background_attribute = DEBUG_ATTRIBUTE_BACKGROUND;
static uint32_t volatile x_position = 0;
static uint32_t volatile y_position = 0;
static debug_screen_t *debug_screen = (debug_screen_t *) BASE_SCREEN;

static bool output_enabled = FALSE;
static uint8_t start_level = 0;

/* Initialize debugging. */
return_t system_debug_init (int argc, char *argv[])
{
    int i;
    char temp_buffer[STRING_MAX_LENGTH];
    
    /* Clear the screen. */
    memory_set_uint16 ((uint16_t *) debug_screen, 
        (background_attribute << 8) | ' ', DEBUG_SCREEN_WIDTH * 
        DEBUG_SCREEN_HEIGHT * sizeof (debug_screen_t));
    
    output_enabled = TRUE;
    
    for (i = 1; i < argc; i++)
    {
        if (!string_compare (argv[i], "--output-disable"))
        {
            output_enabled = FALSE;
        }
    }

    string_print (temp_buffer, "Storm %s (compiled by %s(%s %s) on %s %s).\n",
        storm_info.version, storm_info.maintainer, storm_info.compiler,
        storm_info.compiler_version, storm_info.build_date, 
        storm_info.build_time);
        
    system_debug_print (0, NULL, NULL, 0, temp_buffer);

#ifdef GDB
    system_debug_print (0, NULL, NULL, 0, "Connecting to gdb...");

    gdb_serial_init (GDB_PORT, GDB_SPEED);
    gdb_set_debug_traps ();

    BREAKPOINT ();
#endif

    return 0;
}

/* Put a character at the given position. */
static inline void put_character (int x, int y, char character,
    int character_attribute)
{
    int index = (y * DEBUG_SCREEN_WIDTH) + x;

    debug_screen[index].character = character;
    debug_screen[index].attribute = character_attribute;
}

/* Basic printing function. */
return_t system_debug_print (uint8_t level, char *module_name UNUSED, 
    char *function_name UNUSED, uint32_t line UNUSED, char *string)
{
    unsigned int index;

    if (!output_enabled)
    {
        return 0;    
    }
    
    if (level < start_level)
    {
        return 0;
    }
    
    switch (level)
    {
        case 0:
        {
            text_attribute = DEBUG_ATTRIBUTE_TEXT;
            break;
        }
        
        default:
        {
            text_attribute = 15;
            break;
        }
    }

    /* Handle the NULL string. */
    if (string == NULL)
    {
        string = "(null)";
    }
    
    for (index = 0; string[index] != '\0'; index++)
    {
        if (string[index] == '\n')
        {
            x_position = 0;
            y_position++;
        }
        else
        {
            put_character (x_position, y_position, string[index],
                text_attribute);
            x_position++;
        
            if (x_position == DEBUG_SCREEN_WIDTH)
            {
                x_position = 0;
                y_position++;
            }    
        }
        /* If we're passing the last line on screen, scroll everything
           upwards one line. */
        if (y_position >= DEBUG_SCREEN_HEIGHT)
        {
            y_position = DEBUG_SCREEN_HEIGHT - 1;
            
            memory_copy ((void *) debug_screen, 
                (void *) &debug_screen[DEBUG_SCREEN_WIDTH], 
                (DEBUG_SCREEN_WIDTH * (DEBUG_SCREEN_HEIGHT - 1)) * 2);
                
            memory_set_uint16 ((void *) &debug_screen[DEBUG_SCREEN_WIDTH * 
                (DEBUG_SCREEN_HEIGHT - 1)], 
                (background_attribute << 8) | ' ', DEBUG_SCREEN_WIDTH);
        }
    }
    
    return index;
}
