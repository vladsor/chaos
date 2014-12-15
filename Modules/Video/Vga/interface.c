#include <enviroment.h>

#include <Classes/vga.h>

#include "interface.h"
#include "vga.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//extern return_t video_get_palette (video_palette_t *palette);

static return_t video_set_cursor_place (context_t *context UNUSED, 
    video_cursor_t *cursor)
{
    vga_cursor_place (cursor->x, cursor->y);
    
    return 0;
}

/* Set the font. */
static return_t video_font_set (void)
{
    /* FIXME: Do security checks here. */

    //vga_font_set ((u8 *) data, message_parameter.length);
    return 0;
}

      /* Set a video mode. */
static return_t video_mode_set (context_t *context UNUSED,
    video_mode_t *video_mode)
{
    return_t return_value;
    
    if (video_mode != NULL)
    {
        if (mode_set (video_mode->width, video_mode->height, 
            video_mode->depth, video_mode->mode_type))
        {
            if (video_mode->mode_type == VIDEO_MODE_TYPE_TEXT)
            {
              int index;
              
              for (index = 0; index < 16; index++)
              {
                vga_palette_set_entry (index, &text_palette[index]);
              }  
            }
            else if (video_mode->mode_type == VIDEO_MODE_TYPE_GRAPHIC &&
                     video_mode->depth == 8)
            {
              int index;
              
              for (index = 0; index < 256; index++)
              {
                video_palette_t entry;
                
                entry.red = ((index & 0xE0) >> 5) << 3;
                entry.green = ((index & 0x1C) >> 2) << 3;
                entry.blue = ((index & 0x03) >> 0) << 4;
                
                vga_palette_set_entry (index, &entry);
              }  
              
            }

            return_value = VIDEO_RETURN_SUCCESS;
          }
          else
          {
            return_value = VIDEO_RETURN_MODE_UNAVAILABLE;
          }
    }
    else
    {
        return_value = VIDEO_RETURN_MODE_UNAVAILABLE;
    }

    return return_value;
}

/* Set the palette. */
static return_t video_set_palette (video_palette_t *palette)
{
    vga_palette_set (palette);
    
    return 0;
}

static video_mode_set_method_t video_mode_set_method =
{
    VIDEO_MODE_SET_METHOD (video_mode_set)
};

static video_set_cursor_place_method_t video_set_cursor_place_method =
{
    VIDEO_SET_CURSOR_PLACE_METHOD (video_set_cursor_place)
};

static method_t *methods[] = 
{
    (method_t *) &video_mode_set_method,
    (method_t *) &video_set_cursor_place_method,
};
#define number_of_methods 2

handle_t video = {HANDLE_HEADER_EMPTY, NULL};

static interface_id_t video_interface_id;
static class_id_t video_class_id;

/* Main function. */

return_t vga_main (int argc UNUSED, char *argv[] UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "VGA main.\n");
    
    vga_cursor_place (0, 0);

  /* Set our name. */

//  system_process_name_set ("vga");
//  system_thread_name_set ("Initialising");

    /* Register our hardware ports. */

    if (io_port_register (VGA_PORT_BASE, VGA_PORTS, "VGA adapter"))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Couldn't register portrange 0x%X - 0x%X.",
            VGA_PORT_BASE, VGA_PORT_BASE + VGA_PORTS - 1);

        return -1;
    };

  /* FIXME: Actually check if an adapter is present. How is this done? */

  // if (!vga_detect ())
  // {
  //   return -1;
  // }
  
//  system_call_memory_reserve (VGA_MEMORY, VGA_MEMORY_SIZE,
//                              (void **) &graphic_video_memory);
/*  
  memory_virtual_allocate (&virtual_page_number, SIZE_IN_PAGES (VGA_MEMORY_SIZE));
  memory_virtual_map (virtual_page_number,
                      GET_PAGE_NUMBER (VGA_MEMORY), SIZE_IN_PAGES (VGA_MEMORY_SIZE),
                      PAGE_WRITABLE | PAGE_NON_PRIVILEGED | 
                      PAGE_CACHE_DISABLE);

  graphic_video_memory = (void *) (virtual_page_number * PAGE_SIZE);
*/
    graphic_video_memory = VGA_MEMORY;

//    vga_set_mode (1);

    register_interface_register (&video_interface_id, IID_VIDEO, 
        INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

    register_class_register (&video_class_id, CID_VGA, CLASS_TYPE_DYNAMIC,
        1, &video_interface_id, IID_NONE);

    register_object_create (&video, video_class_id, NULL);

    global_namespace_bind ("/devices/vga", &video);

    return 0;
}

