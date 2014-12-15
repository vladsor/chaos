/* $Id: console_output.c,v 1.4 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Functions for writing to the console. */
/* Author: Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include <unicode.h>

#include "Include/console_output.h"
#include "Include/console.h"
#include "Include/charset.h"

#define DEBUG_MODULE_NAME "Console"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Table for converting between ANSI and EGA colors. */

uint8_t color_table[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

/* Function:    console_scroll ()
   Purpose:     Scroll a console up requested number of lines.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console to scroll. */

/* FIXME: Optimize things like this: Let the outputting function wait
   a bit before scrolling and if multiple lines were written, we can
   call this function with console_scroll (console,
   number_of_lines). This needs the buffer for the console to be
   actual number of lines on screen + maximum scrollable lines per
   call to this function, to hold the text to be displayed at the
   bottom of the screen after the scrolling has been performed. */

static void console_scroll (console_t *console, int number_of_lines)
{
    memory_copy (console->output, console->output + console->width,
        console->width * (console->height - 1) * sizeof (character_t));

    memory_set_uint16 ((uint16_t *) (console->output + (console->height - 1) *
        console->width), ((console->current_attribute) << 8) + ' ', 
        console->width * sizeof (character_t) / sizeof (uint16_t));

    if (console->cursor_saved_y != -1 &&
        console->cursor_saved_y >= number_of_lines)
    {
        console->cursor_saved_y--;
    }

    number_of_lines++;
}

/* Function:    console_set_foreground ()
   Purpose:     Set foreground color to use when outputting text to a console.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console.
                chaos color code. */

static void console_set_foreground (console_t *console, uint32_t color)
{
    console->current_attribute =
        (console->current_attribute & 0xF0) + color_table[color];

    if (console->bold == TRUE)
    {
        console->modified_attribute =
            (console->current_attribute & 0xF0) +
            ((console->current_attribute & 0x0F) + 8);
    }
    else
    {
        console->modified_attribute = console->current_attribute;
    }
}

/* Function:    console_set_background ()
   Purpose:     Set background color to use when outputting text to a console.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console.
                chaos color code. */

static void console_set_background (console_t *console, uint32_t color)
{
    console->current_attribute =
        (console->current_attribute & 0x0F) + (color_table[color] << 4);

    if (console->bold == TRUE)
    {
        console->modified_attribute =
            (console->current_attribute & 0xF0) +
            ((console->current_attribute & 0x0F) + 8);
    }
    else
    {
        console->modified_attribute = console->current_attribute;
    }
}

static void console_kill_line (console_t *console, int argument)
{
    switch (argument)
    {
        case 0:
        {
            /* Clear line from cursor position. */
      
            memory_set_uint16 ((uint16_t *) ((uint32_t) console->output +
                (console->cursor_y * console->width +
                    console->cursor_x) * sizeof (character_t)),
                (console->modified_attribute << 8) + ' ',
                (console->width - console->cursor_x) *
                    sizeof (character_t) / 2);
            break;
        }
    
        case 1:
        {
            /* Clear from start of line to cursor position (inclusive). */
      
            memory_set_uint16 ((uint16_t *) ((uint32_t) console->output +
                               console->cursor_y * console->width *
                               sizeof (character_t)),
                      (console->modified_attribute << 8) + ' ',
                      console->cursor_x *
                      sizeof (character_t) / 2);
            break;
        }
    
        case 2:
        {
            /* Clear whole line. */
      
            memory_set_uint16 ((uint16_t *) ((uint32_t) console->output +
                               console->cursor_y * console->width *
                               sizeof (character_t)),
                      (console->modified_attribute << 8) + ' ',
                      console->width * sizeof (character_t) / 2);
            break;
        }
    }
}

static void console_kill_screen (console_t *console, int argument)
{
    switch (argument)
    {
        case 0:
        {
            unsigned int cursor_address =
                (console->cursor_y * console->width + console->cursor_x) *
                sizeof (character_t);
      
            /* Clear screen from cursor position (inclusive) to
               end. */
      
            memory_set_uint16 ((uint16_t *) ((uint32_t) console->output + 
                cursor_address), (console->current_attribute << 8),
         console->width * console->height *
         sizeof (character_t) / 2 - cursor_address);
            break;
        }
    
        case 1:
        {
            unsigned int cursor_address =
                (console->cursor_y * console->width + console->cursor_x) *
                sizeof (character_t) / 2;
      
            /* Clear screen from start to cursor position
               (inclusive). */
      
            memory_set_uint16 ((uint16_t *) console->output,
                               (console->current_attribute << 8),
                               console->width * console->height *
                               sizeof (character_t) / 2 - cursor_address);
            break;
        }
    
        case 2:
        {
            /* Clear the screen entire screen. */
      
            memory_set_uint16 ((uint16_t *) console->output,
                               (console->current_attribute << 8),
                               console->width * console->height *
                               sizeof (character_t) / 2);
            break;
        }
    }
}

static void console_cursor_up (console_t *console, int argument)
{
    if ((int) (console->cursor_y - argument) < 0)
    {
        console->cursor_y = 0;
    }
    else
    {
        console->cursor_y -= argument;
    }
}

static void console_cursor_down (console_t *console, int argument)
{
    if ((console->cursor_y + argument) > console->height)
    {
        console->cursor_y = console->height;
    }
    else
    {
        console->cursor_y += argument;
    }
}

static void console_cursor_right (console_t *console, int argument)
{
    if ((console->cursor_x + argument) > console->width)
    {
        console->cursor_x = console->width;
    }
    else
    {
        console->cursor_x += argument;
    }
}

static void console_cursor_left (console_t *console, int argument)
{
    if ((int) (console->cursor_x - argument) < 0)
    {
        console->cursor_x = 0;
    }
    else
    {
        console->cursor_x -= argument;
    }
}

static void console_cursor_move (console_t *console, int x, int y)
{
    x--;
    y--;

    if (x < 0)
    {
        console->cursor_x = 0;
    }
    else if (x > console->width)
    {
        console->cursor_x = console->width;
    }
    else
    {
        console->cursor_x = x;
    }

    if (y < 0)
    {
        console->cursor_y = 0;
    }
    else if (y > console->height)
    {
        console->cursor_y = console->height;
    }
    else
    {
        console->cursor_y = y;
    }
}

static void console_n (console_t *console, int argument)
{
    switch (argument)
    {
        case 6:
        {
            /* FIXME: What to do here? */
      
            console_output (console,
                            L"\nchaos Console Server. Copyright chaos development 1999-2004.\nStatus: OK.\n");
        }
    }
}

/* Function:    console_output ()
   Purpose:     Output a string to a console and take care of all
                ANSI escape sequences. This function also converts
                from UTF-8 to the best character set the console allows.
   Returns:     Nothing.
   Parameters:  Pointer to console-struct for console.
                Pointer to string to output. */

/* FIXME: Write small inline functions for all escape sequences and
   call them, so code won't have to be duplicated. */

void console_output (console_t *console, const wchar_t *string)
{
    unsigned int string_index = 0;
    int old_cursor_x;
    int old_cursor_y;
    char character;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        console, string);
  
    old_cursor_x = console->cursor_x;
    old_cursor_y = console->cursor_y;

    /* Modify the attribute according to the flags. */
  
    if (console->bold == TRUE)
    {
        console->modified_attribute = ((console->current_attribute & 0xF0) +
            ((console->current_attribute & 0x0F) + 8));
    }
    else
    {
        console->modified_attribute = console->current_attribute;
    }  
  
    while (string[string_index] != L'\0')
    {
        switch (console->state)
        {
            /* The string is, so far, nice and full of printable
               characters. */

            case CONSOLE_STATE_CHARACTER:
            {
                switch (string[string_index])
                {
                    /* Escape. */
          
                    case L'\e':
                    {
                        console->state = CONSOLE_STATE_PREESCAPE;
                        break;
                    }
          
                    /* New line. */
          
                    case L'\n':
                    {
                        console->cursor_x = 0;
                        console->cursor_y++;
            
                        if (console->cursor_y == console->height)
                        {
                            console_scroll (console, 1);
                            console->cursor_y--;
                        }
                        break;
                    }
          
                    /* Carriage return. */
          
                    case L'\r':
                    {
                        console->cursor_x = 0;
                        break;
                    }
          
                    /* Ordinary printable character. */
          
                    default:
                    {
                        /* FIXME: inverse, underline etc... Support all features
                           (except maybe blink) if in graphicmode. */
            
                        int buffer_index;
                        ucs2_t ucs2;

                        /* If this is an UTF-8 character, convert it to UCS-2. */
                        ucs2 = string[string_index];
                        string_index++;
   
                        character = convert_to_printable_char (ucs2, 
                            CODEPAGE_KOI8_R);

                        if (character == 0)
                        {
                            break;
                        }

                        buffer_index = (console->cursor_y * console->width + 
                            console->cursor_x);
                        console->output[buffer_index].attribute =
                            console->modified_attribute;

                        console->output[buffer_index].character = character;

                        console->cursor_x++;
            
                        if (console->cursor_x == console->width)
                        {
                            console->cursor_x = 0;
                            console->cursor_y++;
              
                            if (console->cursor_y == console->height)
                            {
                                console_scroll (console, 1);
                                console->cursor_y--;
                            }
                        }
                        break;
                    }
                }
                break;
            }

            /* Are we initiating an escape sequence? */

            case CONSOLE_STATE_PREESCAPE:
            {
                if (string[string_index] == L'[')
                {
                    console->state = CONSOLE_STATE_ESCAPE;
                }
                else
                {
                    console->state = CONSOLE_STATE_CHARACTER;
                }
                break;
            }

            /* The last characters were the start of an escape sequence. */
            
            case CONSOLE_STATE_ESCAPE:
            {
                switch (string[string_index])
                {
                    /* Numeric. */

                    case L'0' ... L'9':
                    {
                        console->numeric_argument[
                            console->numeric_argument_index] =
                            string[string_index] - '0';
                        console->state = CONSOLE_STATE_NUMERIC;
                        break;
                    }

                    /* Escape commands without numeric argument follows. */

                    /* Clear screen from cursor position (inclusive). */

                    case L'J':
                    {
                        console_kill_screen (console, 0);
                        break;
                    }

                    /* Save cursor position. */
          
                    case L's':
                    {          
                        console->cursor_saved_x = console->cursor_x;
                        console->cursor_saved_y = console->cursor_y;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
                    
                    /* Restore cursor position. */
          
                    case L'u':
                    {
                        if (console->cursor_saved_x != -1)
                        {
                            console->cursor_x = console->cursor_saved_x;
                            console->cursor_y = console->cursor_saved_y;
                        }
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
                    
                    /* Erase from cursor position to end of line. */
          
                    case L'K':
                    {
                        console_kill_line (console, 0);

                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
                    
                    /* Move one line up. */

                    case L'A':
                    {
                        console_cursor_up (console, 1);

                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Move one line down. */

                    case L'B':
                    {
                        console_cursor_down (console, 1);

                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Move one step to the right. */

                    case L'C':
                    {
                        console_cursor_right (console, 1);

                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Move one step to the left. */

                    case L'D':
                    {
                        console_cursor_left (console, 1);

                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Unknown escape command. */

                    default:
                    {
                        break;
                    }
                }
                break;
            }

            case CONSOLE_STATE_NUMERIC:
            {
                switch (string[string_index])
                {
                    /* Numeric. */

                    case L'0' ... L'9':
                    {
                        console->numeric_argument[
                            console->numeric_argument_index] *= 10;
                        console->numeric_argument[
                            console->numeric_argument_index] +=
                            (string[string_index] - '0');
                        break;
                    }
          
                    /* Another numeric value will follow. Save the current. */

                    case L';':
                    {
                        console->numeric_argument_index++;
                        console->numeric_argument[
                            console->numeric_argument_index] = 0;
                        break;
                    }
                    
                    /* Escape command that take numeric argument(s) follows. */

                    case L'J':
                    {
                        console_kill_screen (console, 
                                             console->numeric_argument[0]);

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
          
                    /* Clear line. */
                    
                    case L'K':
                    {
                        console_kill_line (console, 
                                           console->numeric_argument[0]);

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Device status report. */

                    case L'n':
                    {
                        console_n (console, console->numeric_argument[0]);

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Cursor absolute move. */
                    /* NOTE: This is 1-indexed!!! */

                    case L'f':
                    case L'H':
                    {
                        if (console->numeric_argument_index == 1)
                        {
                            console_cursor_move (console, 
                                                 console->numeric_argument[0],
                                                 console->numeric_argument[1]);
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }

                    /* Cursor up. */
          
                    case L'A':
                    {              
                        if (console->numeric_argument_index == 0)
                        {
                            console_cursor_up (console, 
                                               console->numeric_argument[0]);
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
          
                    /* Cursor down. */
          
                    case L'B':
                    { 
                        if (console->numeric_argument_index == 0)
                        {
                            console_cursor_down (console, 
                                                 console->numeric_argument[0]);
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
          
                    /* Cursor right. */
          
                    case L'C':
                    {
                        if (console->numeric_argument_index == 0)
                        {
                            console_cursor_right (console, 
                                                  console->numeric_argument[0]);
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
          
                    /* Cursor left. */
          
                    case L'D':
                    {
                        if (console->numeric_argument_index == 0)
                        {
                            console_cursor_left (console, 
                                                 console->numeric_argument[0]);
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
                    
                    /* Tabulation stuff. */

                    case L'g':
                    {
                        break;
                    }

                    /* Set attribute. */
          
                    case L'm':
                    {
                        unsigned int counter;

                        for (counter = 0; 
                             counter < console->numeric_argument_index + 1;
                             counter++)
                        {
                            switch (console->numeric_argument[counter])
                            {
                                /* Foreground color. */
                
                                case 30 ... 37:
                                {
                                    console_set_foreground (console, 
                                        console->numeric_argument[counter] - 30);
                                    break;
                                }
                
                                /* Background color. */
                
                                case 40 ... 47:
                                {
                                    console_set_background (console, 
                                        console->numeric_argument[counter] - 40);
                                    break;
                                }
                
                                /* All attributes off. */
                
                                case 0:
                                {
                                    console->bold = FALSE;
                                    console->underline = FALSE;
                                    console->inverse = FALSE;
                                    console->blink = FALSE;
                                    break;
                                }
                
                                /* Turn on bold. */
                
                                case 1:
                                {
                                    if (console->bold == FALSE)
                                    {
                                        console->bold = TRUE;
                                        console->modified_attribute =
                                            (console->current_attribute & 0xf0) +
                                            ((console->current_attribute & 0x0f) + 8);
                                    }
                                    break;
                                }
                                
                                /* Turn on underlined text. */
                                
                                case 4:
                                {
                                    console->underline = TRUE;
                                    break;
                                }
                
                                /* Turn on blink. */
                                
                                case 5:
                                {
                                    console->blink = TRUE;
                                    break;
                                }
                                
                                /* Turn on inverse. */
                
                                case 7:
                                {
                                    console->inverse = TRUE;
                                    break;
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        console->numeric_argument_index = 0;
                        console->state = CONSOLE_STATE_CHARACTER;
                        break;
                    }
          
                    /* Unknown escape command. */
                    
                    default:
                    {
                        break;
                    }
                }
                break;
            }

            /* Unknown state. */

            default:
            {
                break;
            }
        }

        string_index++;
    }

    /* Check if the cursor position was updated. If it was, move the
       physical cursor. */
  
    if (has_video &&
        current_console == console && console->keyboard_cursor_visibility &&
        (old_cursor_x != console->cursor_x || 
         old_cursor_y != console->cursor_y))
    {
//        video_cursor_t video_cursor;
        //    message_parameter_type message_parameter;

//        video_cursor.x = console->cursor_x;
//        video_cursor.y = console->cursor_y;
        video$cursor_set (video, console->cursor_x, console->cursor_y);
    }
}

void console_print_charset (console_t *console)
{
    unsigned char ch_h, ch_l;
    unsigned int buffer_index;

    console_output (console, L"\n");
  
    for (ch_h = 0 ; ch_h <= 0xF ; ch_h++)
    {
        for (ch_l = 0 ; ch_l <= 0xF ; ch_l++)
        {
            buffer_index = (console->cursor_y * console->width + 
                            console->cursor_x);

            console->output[buffer_index].character = ch_h << 4 | ch_l;

            console->cursor_x++;  
        }

        console_output (console, L"\n");
    }
}

void console_output_at (console_t *console, int x, int y, const wchar_t *string)
{
    unsigned int string_index = 0;
    int cursor_x = x;
    int cursor_y = y;
    char character;
    
    while (string[string_index] != L'\0')
    {
        switch (string[string_index])
        {
            /* New line. */
            case L'\n':
            {
                return;
            }
                    
            /* Ordinary printable character. */
            default:
            {
                int buffer_index;
                ucs2_t ucs2;

                ucs2 = string[string_index];
                string_index++;

                /* The ASCII characters are always the same. */
                character = convert_to_printable_char (ucs2, CODEPAGE_KOI8_R);
                
                if (character == '\0')
                {
                    break;
                }

                buffer_index = (cursor_y * console->width + cursor_x);
                console->output[buffer_index].attribute = console->modified_attribute;

                console->output[buffer_index].character = character;
                cursor_x++;
            
                if (cursor_x == console->width)
                {
                    return;              
                }
                break;
            }
        }
        string_index++;
    }
}

void keyboard_cursor_set (console_t *console, bool visibility)
{
//    video_cursor_t video_cursor;
    uint32_t x, y;
 
    if (visibility == console->keyboard_cursor_visibility)
    {
        return;
    }
    console->keyboard_cursor_visibility = visibility;
  
    if (!has_video || (current_console != console))
    {
        return;
    }

    if (!visibility)
    {
        x = console->width + 1;
        y = console->height + 1;
    }
    else
    {
        x = console->cursor_x;
        y = console->cursor_y;
    }

    video$cursor_set (video, x, y);    
  
    return;
}

void mouse_cursor_draw (int width, int height, bool visibility)
{
    unsigned int buffer_index;  
  
    int mouse_x, mouse_y;

    mouse_x = ( width * mouse_cursor_position.x) / 1000000;
    mouse_y = (height * mouse_cursor_position.y) / 1000000;

//  console->mouse_cursor_visibility = visibility;

    buffer_index = (mouse_y * width + mouse_x);

    if (!visibility)
    {
        screen[buffer_index] = character_under_mouse;
    }
    else
    {
        character_under_mouse = screen[buffer_index];
        screen[buffer_index] = mouse_cursor;
    }
}

void mouse_cursor_update (int width, int height, bool visibility, 
    uint32_t mouse_x, uint32_t mouse_y, uint32_t mouse_button_state UNUSED)
{
    unsigned int buffer_index;  
    int old_mouse_x, old_mouse_y;
    int new_mouse_x, new_mouse_y;

    if (!visibility)
    {
        mouse_cursor_position.x = mouse_x;
        mouse_cursor_position.y = mouse_y;
        return;
    }

    old_mouse_x = ( width * mouse_cursor_position.x) / 1000000;
    old_mouse_y = (height * mouse_cursor_position.y) / 1000000;
  
    mouse_cursor_position.x = mouse_x;
    mouse_cursor_position.y = mouse_y;
  
    new_mouse_x = ( width * mouse_cursor_position.x) / 1000000;
    new_mouse_y = (height * mouse_cursor_position.y) / 1000000;

    buffer_index = (old_mouse_y * width + old_mouse_x);
    screen[buffer_index] = character_under_mouse;

    buffer_index = new_mouse_y * width + new_mouse_x;
    character_under_mouse = screen[buffer_index];
    screen[buffer_index] = mouse_cursor;
}

