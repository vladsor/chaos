/* $Id: console_output.h,v 1.2 2000/09/29 21:09:30 hal Exp $ */
/* Abstract: Console outputting functions. */
/* Author: Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */

/* Functions. */

#ifndef __CONSOLE_OUTPUT_H__
#define __CONSOLE_OUTPUT_H__

#include "console.h"

extern void console_output (console_t *console, const wchar_t *string);
extern void console_output_at (console_t *console, int x, int y, 
    const wchar_t *string);

extern void keyboard_cursor_set (console_t *console, bool visibility);

#if SCROLL
extern void console_scroll_set(console_type *console, bool enabled);
extern void console_scroll(console_type *console, int lines);
#endif
void console_print_charset (console_t *console);

extern void mouse_cursor_draw (int width, int height, bool visibility);
extern void mouse_cursor_update (int width, int height, bool visibility, 
    uint32_t x, uint32_t y, uint32_t button_state);

#endif /* !__CONSOLE_OUTPUT_H__ */
