
#define INTERFACE_CONSOLE_CONTROL_ID 0x00021

enum
{
    METHOD_CONSOLE_CONTROL_OUTPUT_ID,
    METHOD_CONSOLE_CONTROL_OUTPUT_AT_ID,
    METHOD_CONSOLE_CONTROL_KEYBOARD_ENABLE_ID,
    METHOD_CONSOLE_CONTROL_MOUSE_ENABLE_ID,
    METHOD_CONSOLE_CONTROL_KEYBOARD_CURSOR_SET_ID,
    METHOD_CONSOLE_CONTROL_MOUSE_CURSOR_SET_ID,
    METHOD_CONSOLE_CONTROL_VIDEO_MODE_SET_ID,

    METHOD_CONSOLE_CONTROL_NUMBER,
};

typedef void (console_control_output_t) (context_t context, 
    const wchar_t *text);
typedef console_control_output_t * p_console_control_output_t;

typedef void (console_output_at_t) (context_t context, int x, int y, 
    const wchar_t *text);
typedef console_output_at_t * p_console_output_at_t;
    
typedef void (console_keyboard_enable_t) (context_t context, 
    bool enabled);
typedef console_keyboard_enable_t * p_console_keyboard_enable_t;
    
typedef void (console_keyboard_cursor_set_t) (context_t context,
    bool visible);
typedef console_keyboard_cursor_set_t * p_console_keyboard_cursor_set_t;

typedef void (console_mouse_enable_t) (context_t context, 
    bool enabled);
typedef console_mouse_enable_t * p_console_mouse_enable_t;
    
typedef void (console_mouse_cursor_set_t) (context_t context,
    bool visible);
typedef console_mouse_cursor_set_t * p_console_mouse_cursor_set_t;

typedef void (console_video_mode_set_t) (context_t context,
    uint32_t video_mode_width, uint32_t video_mode_height, 
    uint32_t video_mode_depth, uint32_t video_mode_type);
typedef console_video_mode_set_t * p_console_video_mode_set_t;

typedef struct
{
    p_console_control_output_t      output;
    p_console_output_at_t           output_at;
    p_console_keyboard_enable_t     keyboard_enable;
    p_console_keyboard_cursor_set_t keyboard_cursor_set;
    p_console_mouse_enable_t        mouse_enable;
    p_console_mouse_cursor_set_t    mouse_cursor_set;
    p_console_video_mode_set_t      video_mode_set;

} console_control_interface_table_t;

typedef console_control_interface_table_t * p_console_control_interface_table_t;

static inline handle_reference_t console_control$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0};

    return handle_create (object, INTERFACE_CONSOLE_CONTROL_ID, seq_empty, 0);
}    

static inline void console_control$handle$destroy (
    handle_reference_t handle)
{
    handle_destroy (handle);
}

static inline void console_control$output (handle_reference_t handle, 
    const wchar_t *text)
{
    uint32_t pars_in[] = {(uint32_t) text};
    sequence_t pars_in_seq = {data: pars_in, count: 1};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_CONSOLE_CONTROL_OUTPUT_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, empty_seq, 0);
}

