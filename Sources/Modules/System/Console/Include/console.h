/* $Id: console.h,v 1.4 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Console header file. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <Classes/keyboard.h>
#include <Classes/mouse.h>
#include <Interfaces/video.h>

/* The default attribute to use for newly created consoles. */

#define CONSOLE_DEFAULT_ATTRIBUTE       0x07

/* The location of the physical video memory. */

#define CONSOLE_VIDEO_MEMORY            0xB8000
#define CONSOLE_VIDEO_MEMORY_SIZE       (64 * KIB)

/* Maximum number of numeric arguments per escape sequence. */

#define MAX_NUMBER_OF_NUMERIC_PARAMETERS 10

enum
{
    CONSOLE_KEYBOARD_NORMAL,
    CONSOLE_KEYBOARD_EXTENDED
};

typedef struct
{
    uint8_t character;
    uint8_t attribute;

} character_t PACKED;

/* A virtual console structure. */

typedef struct
{
    /* Location of the cursor. */

    int cursor_x;
    int cursor_y;

    /* Stored location of the cursor. */

    int cursor_saved_x;
    int cursor_saved_y;

    /* If type is VIDEO_MODE_TYPE_TEXT, characters. Otherwise,
       pixels. */

    int width;
    int height;  
    int depth;
    int type;

    bool echo_enabled;
  
    /* States of keyboard and mouse cursors */
  
    bool keyboard_cursor_visibility;
    bool mouse_cursor_visibility;
  
    bool scrollable;
  
    /* The current state of the console. Used for ANSI escape
       sequences. */

    unsigned int state;
    unsigned int numeric_argument_index;
    int numeric_argument[MAX_NUMBER_OF_NUMERIC_PARAMETERS];

    /* FIXME: This should be extended to support other formats. Right
       now, we just use the EGA attribute. */

    uint8_t current_attribute;

    /* Pointer to the buffer for this console. */

    character_t *buffer;

    /* The actual output to this console should go here. When the
       console is activated, this and the previous one will differ. */

    character_t *output;

    /* FIXME: This isn't neccessary. */

    uint8_t modified_attribute;

    int character_width;
    int character_height;

    bool bold;
    bool underline;
    bool blink;
    bool inverse;

    bool wants_keyboard;
    int keyboard_type;
    
    keyboard_event_data_t keyboard_buffer[20];
    uint32_t keyboard_buffer_head;
    uint32_t keyboard_buffer_tail;
    
//    atomic_uint32_t keyboard_buffer_head;
//    atomic_uint32_t keyboard_buffer_tail;
    countlock_t keyboard_count;

    /* And/Or mouse? */

    bool wants_mouse;

    bool keyboard_cursor_enabled;
    bool mouse_cursor_enabled;

    /* Is this console locked? */
    /* FIXME: Real mutexing is needed. */
  
    bool lock;

    /* Next console. */

    struct console_t *next;

} console_t;

/* States for a console. */

enum
{
    CONSOLE_STATE_CHARACTER,
    CONSOLE_STATE_PREESCAPE,
    CONSOLE_STATE_ESCAPE,
    CONSOLE_STATE_NUMERIC,
};

#define CONSOLE_HOT_KEY_DESCRIPTION_LENGTH 256

typedef void (hot_key_function_t)(void *);
typedef hot_key_function_t * p_hot_key_function_t;

typedef struct
{
    keyboard_event_data_t key;
    p_hot_key_function_t function;
    void *parameter;
    wchar_t description[CONSOLE_HOT_KEY_DESCRIPTION_LENGTH];
  
} hot_key_record_t;

/* Global variables. */

extern character_t *screen;
extern volatile bool has_video;
extern volatile bool has_keyboard;

//extern ipc_structure_type video_structure;
//extern ipc_structure_type keyboard_structure;

extern volatile console_t *current_console;
extern volatile unsigned int number_of_consoles;
extern console_t *console_list;
extern volatile console_t *console_shortcut[];

typedef struct
{
    int x;
    int y;
} position_t;

extern hot_key_record_t table_of_hot_keys[];
extern unsigned int number_of_hot_keys;

extern volatile character_t mouse_cursor;
extern volatile position_t mouse_cursor_position;
extern volatile character_t character_under_mouse;

//extern handle_t keyboard_events;
//extern handle_t mouse_events;
//extern handle_t video;
extern handle_reference_t video;

/* External functions. */

extern void console_link (console_t *console);
extern void console_flip (console_t *console);

extern void console_keyboard_handler (context_t context, 
    p_keyboard_event_data_t event_data);

extern void console_mouse_handler (context_t context, uint32_t mouse_x, 
    uint32_t mouse_y, uint32_t mouse_button_state);

#endif /* !__CONSOLE_H__ */

