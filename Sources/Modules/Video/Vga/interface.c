#include <enviroment.h>

#include <Classes/vga.h>

#include "Include/interface.h"
#include "Include/vga.h"

#include "Include/video_interface.h"
#include "Include/vga_class.h"

#define DEBUG_MODULE_NAME "VGA"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//extern return_t video_get_palette (video_palette_t *palette);

static void video_cursor_set (context_t context UNUSED, 
    uint32_t x, uint32_t y)
{
    vga_cursor_place (x, y);
}

/* Set the font. */
static void video_font_set (context_t context UNUSED, sequence_t font UNUSED)
{
    //vga_font_set ((u8 *) data, message_parameter.length);
}

      /* Set a video mode. */
static void video_mode_set (context_t context UNUSED,
    uint32_t width, uint32_t height, uint32_t depth, uint32_t mode_type)
{
//    return_t return_value = 0;
    
//    if (video_mode != NULL)
    {
        if (mode_set (width, height, depth, mode_type))
        {
            if (mode_type == VIDEO_MODE_TYPE_TEXT)
            {
                int index;
              
                for (index = 0; index < 16; index++)
                {
                    vga_palette_set_entry (index, &text_palette[index]);
                }  
            }
            else if (mode_type == VIDEO_MODE_TYPE_GRAPHIC && depth == 8)
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

//            return_value = VIDEO_RETURN_SUCCESS;
          }
          else
          {
//            return_value = VIDEO_RETURN_MODE_UNAVAILABLE;
          }
    }
/*
    else
    {
//        return_value = VIDEO_RETURN_MODE_UNAVAILABLE;
    }
*/
//    return return_value;
}

/* Set the palette. */
/*
static return_t video_set_palette (video_palette_t *palette)
{
    vga_palette_set (palette);
    
    return 0;
}
*/

static video_interface_table_t table =
{
    &video_mode_set,
    &video_cursor_set,
    &video_font_set,
};    

static interface_reference_t interfaces[1];
static class_reference_t class;
static object_reference_t video = REFERENCE_NULL;

/* Main function. */

return_t vga_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%u, %p, %p).\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        argc, argv, envp);
    
    vga_cursor_place (0, 0);

  /* Set our name. */

//  system_process_name_set ("vga");
//  system_thread_name_set ("Initialising");

    /* Register our hardware ports. */

    if (io_port_register (VGA_PORT_BASE, VGA_PORTS, "VGA adapter"))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Couldn't register portrange 0x%X - 0x%X.",
            DEBUG_MODULE_NAME,
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
    graphic_video_memory = (p_uint8_t) VGA_MEMORY;

//    vga_set_mode (1);

/*
    register_interface_register (&video_interface_id, IID_VIDEO, 
        INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

    register_class_register (&video_class_id, CID_VGA, CLASS_TYPE_DYNAMIC,
        1, &video_interface_id, IID_NONE);

    register_object_create (&video, video_class_id, NULL);
*/
    interfaces[0] = video_interface_register (&table);
    class = vga_class_register (interfaces);
    video = object_create (class, SECURITY_CURRENT, empty_seq, 0);

    namespace$bind (kernel_handle_namespace, L"/devices/video", video);

    return 0;
}

