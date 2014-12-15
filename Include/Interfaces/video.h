
#ifndef __INTERFACE_VIDEO_H__
#define __INTERFACE_VIDEO_H__

#define INTERFACE_VIDEO_ID 0x000D

enum
{
    VIDEO_MODE_TYPE_TEXT,
    VIDEO_MODE_TYPE_GRAPHIC
};

/* IPC structures for video. */
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} video_palette_t;

enum
{
    METHOD_VIDEO_MODE_SET_ID,
    METHOD_VIDEO_CURSOR_SET_ID,
    METHOD_VIDEO_FONT_SET_ID,
    
    METHOD_VIDEO_NUMBER,
};

typedef void (video_mode_set_t) (context_t context, uint32_t width, 
    uint32_t height, uint32_t depth, uint32_t mode_type);
typedef video_mode_set_t * p_video_mode_set_t;
    
typedef void (video_cursor_set_t) (context_t context, uint32_t x, uint32_t y);
typedef video_cursor_set_t * p_video_cursor_set_t;

typedef void (video_font_set_t) (context_t context, sequence_t font);
typedef video_font_set_t * p_video_font_set_t;
    
typedef struct
{
    p_video_mode_set_t mode_set;
    p_video_cursor_set_t cursor_set;
    p_video_font_set_t font_set;
    
} video_interface_table_t;

typedef video_interface_table_t * p_video_interface_table_t;

static inline handle_reference_t video$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_VIDEO_ID, seq_empty, 0);
}    

static inline void video$handle$destroy (
    handle_reference_t handle)
{
    handle_destroy (handle);
}

static inline void video$mode_set (handle_reference_t handle, 
    uint32_t width, uint32_t height, uint32_t depth, uint32_t mode_type)
{
    uint32_t pars_in[] = {width, height, depth, mode_type};
    sequence_t pars_in_seq = {data: pars_in, count: 4};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_VIDEO_MODE_SET_ID, REFERENCE_NULL,
        pars_in_seq, empty_seq, empty_seq, 0);
}

static inline void video$cursor_set (handle_reference_t handle, 
    uint32_t x, uint32_t y)
{
    uint32_t pars_in[] = {x, y};
    sequence_t pars_in_seq = {data: pars_in, count: 2};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_VIDEO_CURSOR_SET_ID, REFERENCE_NULL, 
        pars_in_seq, empty_seq, empty_seq, 0);
}
    
#endif /* !__INTERFACE_VIDEO_H__ */

