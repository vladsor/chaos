
#ifndef __INTERFACE_VIDEO_H__
#define __INTERFACE_VIDEO_H__

enum
{
    VIDEO_MODE_TYPE_TEXT,
    VIDEO_MODE_TYPE_GRAPHIC
};

enum
{
    /* The call completed successfully. */

    VIDEO_RETURN_SUCCESS,

    /* The requested mode could not be set. */

    VIDEO_RETURN_MODE_UNAVAILABLE,
};

/* IPC structures for video. */

typedef struct
{
    unsigned int x;
    unsigned int y;
} video_cursor_t;

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} video_palette_t;

typedef struct
{
    /* Video mode resolution. */
    unsigned int width;
    unsigned int height;
    unsigned int depth;
  
    /* Do we want a double buffered mode? We may get it anyway, but we
       might as well state what we'd prefer. For example, most games
       would likely always want a double buffered mode for flicker-free
       animation. */
    bool buffered;

    /* Which type of mode do we want? (Graphic or text) */
    unsigned int mode_type;
    
} video_mode_t;


#define IID_VIDEO 0x00001001

enum
{
    MID_VIDEO_MODE_SET,
    MID_VIDEO_SET_CURSOR_PLACE,
};

typedef return_t (video_mode_set_function_t) (context_t *context, 
    video_mode_t *video_mode);
typedef return_t (video_set_cursor_place_function_t) (context_t *context, 
    video_cursor_t *video_cursor);
    
typedef struct
{
    video_mode_set_function_t *mode_set;
    video_set_cursor_place_function_t *set_cursor_place;
} video_interface_t;

typedef struct
{
    video_mode_set_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} video_mode_set_method_t;

#define VIDEO_MODE_SET_METHOD(function) \
    (&(function)), \
    (MID_VIDEO_MODE_SET), \
    (sizeof (video_mode_t *)), \
    (1), \
    { \
        {sizeof (video_mode_t *)}, \
    }    

typedef struct
{
    video_set_cursor_place_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} video_set_cursor_place_method_t;

#define VIDEO_SET_CURSOR_PLACE_METHOD(function) \
    (&(function)), \
    (MID_VIDEO_SET_CURSOR_PLACE), \
    (sizeof (video_cursor_t *)), \
    (1), \
    { \
        {sizeof (video_cursor_t *)}, \
    }    


#define video$mode_set(handle,mode) \
    ((video_interface_t *) ((handle)->functions))->mode_set ( \
        &((handle)->context), \
        (mode))

#define video$set_cursor_place(handle,cursor) \
    ((video_interface_t *) ((handle)->functions))->set_cursor_place ( \
        &((handle)->context), \
        (cursor))

//extern return_t video_mode_set (video_mode_t *video_mode);
//extern return_t video_set_cursor_place (video_cursor_t *video_cursor);
//extern return_t video_set_palette (video_palette_t *palette);
//extern return_t video_get_palette (video_palette_t *palette);

#endif /* !__INTERFACE_VIDEO_H__ */
