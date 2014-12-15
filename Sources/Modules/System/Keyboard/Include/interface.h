
#include <Classes/kernel.h>
extern handle_reference_t kernel_handle_namespace;
extern event_queue_reference_t kernel_debug_queue;

#define KEYBOARD_IRQ    (1)
#define MOUSE_IRQ       (12)

#include <Classes/keyboard.h>
#include <Classes/mouse.h>

extern return_t keyboard_main (int argc, char *argv[], char **envp);
extern return_t mouse_main (int argc, char *argv[], char **envp);

extern volatile event_supplier_reference_t keyboard_debug_supplier;
extern volatile event_supplier_reference_t mouse_debug_supplier;

extern void interface_fire_keyboard_event (p_keyboard_event_data_t event);
extern void interface_fire_mouse_event (uint32_t x, uint32_t y, 
    uint32_t button);

#define KEYBOARD_SAFE_IRQ_HANDLER
