
#define IID_CONSOLE 0x00002001

enum
{
    MID_CONSOLE_OUTPUT,
    MID_CONSOLE_OUTPUT_AT,
    MID_CONSOLE_KEYBOARD_SET_ENABLED,
    MID_CONSOLE_MOUSE_SET_ENABLED,
    MID_CONSOLE_KEYBOARD_SET_CURSOR,
    MID_CONSOLE_MOUSE_SET_CURSOR,
    MID_CONSOLE_VIDEO_MODE_SET,
};

typedef return_t (console_output_function_t) (context_t *context, char *text);
typedef return_t (console_output_at_function_t) (context_t *context, int x, 
    int y, char *text);
typedef return_t (console_keyboard_set_enabled_function_t) (context_t *context, 
    bool enabled);
typedef return_t (console_mouse_set_enabled_function_t) (context_t *context, 
    bool enabled);
typedef return_t (console_keyboard_set_cursor_function_t) (context_t *context,
    bool visible);
typedef return_t (console_mouse_set_cursor_function_t) (context_t *context, 
    bool visible);
typedef return_t (console_video_mode_set_function_t) (context_t *context,
    console_attribute_t *console_attribute);

typedef struct
{
    console_output_function_t *output;
    console_output_at_function_t *output_at;
    console_keyboard_set_enabled_function_t *keyboard_set_enabled;
    console_mouse_set_enabled_function_t *mouse_set_enabled;
    console_keyboard_set_cursor_function_t *keyboard_set_cursor;
    console_mouse_set_cursor_function_t *mouse_set_cursor;
    console_video_mode_set_function_t *video_mode_set;
} console_interface_t;

typedef struct
{
    console_output_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} console_output_method_t;

#define CONSOLE_OUTPUT_METHOD(function) \
    (&(function)), \
    (MID_CONSOLE_OUTPUT), \
    (sizeof (char *)), \
    (1), \
    { \
        {sizeof (char *)}, \
    }    

#define console$output(handle,text) \
    ((console_interface_t *) ((handle)->functions))->output ( \
        &((handle)->context), \
        (text))

#define console$output_at(handle,x,y,text) \
    ((console_interface_t *) ((handle)->functions))->output_at ( \
        &((handle)->context), \
        (x), (y), (text))

#define console$keyboard_set_enabled(handle,enabled) \
    ((console_interface_t *) ((handle)->functions))->keyboard_set_enabled ( \
        &((handle)->context), \
        (enabled))

#define console$mouse_set_enabled(handle,enabled) \
    ((console_interface_t *) ((handle)->functions))->mouse_set_enabled ( \
        &((handle)->context), \
        (enabled))

#define console$keyboard_set_cursor(handle,visible) \
    ((console_interface_t *) ((handle)->functions))->keyboard_set_cursor ( \
        &((handle)->context), \
        (visible))

#define console$mouse_set_cursor(handle,visible) \
    ((console_interface_t *) ((handle)->functions))->mouse_set_cursor ( \
        &((handle)->context), \
        (visible))

#define console$video_mode_set(handle,attribute) \
    ((console_interface_t *) ((handle)->functions))->video_mode_set ( \
        &((handle)->context), \
        (attribute))
