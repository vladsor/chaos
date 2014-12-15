/* $Id: keyboard.h,v 1.2 2001/02/10 21:25:03 jojo Exp $ */
/* Abstract: Header file for the keyboard server. */

/* Copyright 1998-2000 chaos development. */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

/* Timeout in ms for keyboard command acknowledge. */

#define KEYBOARD_TIMEOUT                        1000

/* Timeout in ms for initializing the keyboard. */

#define KEYBOARD_INIT_TIMEOUT                   1000

/* Keyboard commands. */

#define KEYBOARD_COMMAND_SET_LEDS               0xED
#define KEYBOARD_COMMAND_SET_RATE               0xF3
#define KEYBOARD_COMMAND_ENABLE                 0xF4
#define KEYBOARD_COMMAND_DISABLE                0xF5
#define KEYBOARD_COMMAND_RESET                  0xFF

/* Keyboard replies. */
/* Power on reset. */

#define KEYBOARD_REPLY_POWER_ON_RESET           0xAA

/* Acknowledgement of previous command. */

#define KEYBOARD_REPLY_ACK                      0xFA

/* Command NACK, send the command again. */

#define KEYBOARD_REPLY_RESEND                   0xFE

/* Hardware defines. */

/* Return values from keyboard_read_data (). */
/* No data. */

#define KEYBOARD_NO_DATA                        (-1)

/* Parity or other error. */

#define KEYBOARD_BAD_DATA                       (-2)

/* Shift states. */

#define KEYBOARD_LEFT_SHIFT                     (1 << 0)
#define KEYBOARD_RIGHT_SHIFT                    (1 << 1)
#define KEYBOARD_LEFT_ALT                       (1 << 2)
#define KEYBOARD_RIGHT_ALT                      (1 << 3)
#define KEYBOARD_LEFT_CONTROL                   (1 << 4)
#define KEYBOARD_RIGHT_CONTROL                  (1 << 5)

/* Function prototypes. */

extern void keyboard_clear_input (void);
extern const char *keyboard_set_repeat_rate (void);
extern void keyboard_handle_event (uint8_t scancode);
extern const char *keyboard_init (void);
extern void keyboard_update_leds (void);

extern return_t keyboard_switch_map_to_next (void);

extern void keyboard_load_maps (void);
extern void keyboard_reset_pressed_keys (void);

extern bool keyboard_exists;

#endif /* !__KEYBOARD_H__ */

