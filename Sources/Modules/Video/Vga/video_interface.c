#include <enviroment.h>

#include <Interfaces/video.h>
#include "Include/video_interface.h"

#define DEBUG_MODULE_NAME "video"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void mode_set_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_video_mode_set_t video_mode_set;
    uint32_t width;
    uint32_t height;
    uint32_t depth; 
    uint32_t mode_type;
    
    video_mode_set = (p_video_mode_set_t) (address_t) function;

    width = ((p_uint32_t ) parameters_in.data)[0];
    height = ((p_uint32_t ) parameters_in.data)[1]; 
    depth = ((p_uint32_t ) parameters_in.data)[3];
    mode_type = ((p_uint32_t ) parameters_in.data)[4];

    video_mode_set (context, width, height, depth, mode_type);
}

static void cursor_set_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_video_cursor_set_t video_cursor_set;
    uint32_t x;
    uint32_t y;

    video_cursor_set = (p_video_cursor_set_t) (address_t) function;
    
    x = ((p_uint32_t ) parameters_in.data)[0];
    y = ((p_uint32_t ) parameters_in.data)[1]; 

    video_cursor_set (context, x, y);
}

static void font_set_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_video_font_set_t video_font_set;
    sequence_t font = {data: NULL, count: 0};

    video_font_set = (p_video_font_set_t) (address_t) function;
    
    video_font_set (context, font);
}

static description_reference_t method_description_mode_set;
static description_reference_t method_description_cursor_set;
static description_reference_t method_description_font_set;

static method_reference_t methods[METHOD_VIDEO_NUMBER];
static sequence_t method_seq = {data: methods, count: METHOD_VIDEO_NUMBER};

static description_reference_t interface_description;

interface_reference_t video_interface_register (
    p_video_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_mode_set = method_description_register (
        METHOD_VIDEO_MODE_SET_ID,
        L"mode_set",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_VIDEO_MODE_SET_ID] = method_create_dynamic (
        method_description_mode_set, REFERENCE_NULL, MEMORY_CURRENT,
        &mode_set_wrapper, (address_t) table->mode_set, 0);

    method_description_cursor_set = method_description_register (
        METHOD_VIDEO_CURSOR_SET_ID,
        L"cursor_set",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_VIDEO_CURSOR_SET_ID] = method_create_dynamic (
        method_description_cursor_set, REFERENCE_NULL, MEMORY_CURRENT,
        &cursor_set_wrapper, (address_t) table->cursor_set, 0);
    
    method_description_font_set = method_description_register (
        METHOD_VIDEO_FONT_SET_ID,
        L"font_set",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_VIDEO_FONT_SET_ID] = method_create_dynamic (
        method_description_font_set, REFERENCE_NULL, MEMORY_CURRENT,
        &font_set_wrapper, (address_t) table->font_set, 0);

    interface_description = interface_description_register (
        INTERFACE_VIDEO_ID,
        L"video",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

