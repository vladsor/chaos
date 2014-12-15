/* $Id: vga.c,v 1.2 2001/02/10 21:25:42 jojo Exp $ */
/* Abstract: VGA server for chaos. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org>
            Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

#include <enviroment.h>

#include <Interfaces/video.h>

#include "Include/font_8x8.h"

#include "Include/vga.h"

#define DEBUG_MODULE_NAME "VGA"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

static void vga_set_mode (uint32_t mode UNUSED)
{
}

typedef struct
{
    unsigned int mode;
    unsigned int width;
    unsigned int height;
    unsigned int bpp;
    unsigned int type;
} vga_mode_t;

vga_mode_t mode[] =
{
  { 0, 320, 200, 8, VIDEO_MODE_TYPE_GRAPHIC },
  { 1, 80,  25,  4, VIDEO_MODE_TYPE_TEXT },
  { 2, 80,  50,  4, VIDEO_MODE_TYPE_TEXT }
};

vga_mode_t *current_mode = NULL;

video_palette_t text_palette[] =
{ 
  /* Dark. */

  { 0x00, 0x00, 0x00 }, /* Black. */
  { 0x08, 0x08, 0x18 }, /* Blue. */
  { 0x08, 0x18, 0x08 }, /* Green. */
  { 0x08, 0x18, 0x18 }, /* Cyan. */
  { 0x18, 0x08, 0x08 }, /* Red. */
  { 0x18, 0x08, 0x18 }, /* Purple. */
  { 0x18, 0x18, 0x08 }, /* Brown. */
  { 0x28, 0x28, 0x28 }, /* Gray. */

  /* Light. */

  { 0x20, 0x20, 0x20 }, /* Dark gray. */
  { 0x28, 0x28, 0x38 },
  { 0x28, 0x38, 0x28 },
  { 0x28, 0x38, 0x38 },
  { 0x38, 0x28, 0x28 },
  { 0x38, 0x28, 0x38 },
  { 0x38, 0x38, 0x28 }, /* Yellow. */
  { 0x38, 0x38, 0x38 }  /* White. */
};

uint8_t *graphic_video_memory = (uint8_t *) NULL;
  
#define VIDEO_MODES (sizeof (mode) / sizeof (vga_mode_t))

/* Set up the given video mode. */

bool mode_set (unsigned int width, unsigned int height,
    unsigned int bpp, unsigned int type)
{
  unsigned int search;
  
  for (search = 0; search < VIDEO_MODES; search++)
  {
    if (width == mode[search].width &&
    height == mode[search].height &&
    bpp == mode[search].bpp &&
    type == mode[search].type)
    {
      vga_set_mode (mode[search].mode);
      current_mode = &mode[search];
      return TRUE;
    }
  }

  return FALSE;
}

/* Set the VGA palette. */

void vga_palette_set (video_palette_t *palette)
{
    port_uint8_out (VGA_PALETTE_WRITE, 0);
    port_uint8_out_string (VGA_PALETTE_DATA, (uint8_t *) palette, 256 * 3);
}

/* Set one entry in the VGA palette. */

void vga_palette_set_entry (uint8_t num, video_palette_t *entry)
{
    port_uint8_out (VGA_PALETTE_WRITE, num);
    port_uint8_out (VGA_PALETTE_DATA, entry->red);
    port_uint8_out (VGA_PALETTE_DATA, entry->green);
    port_uint8_out (VGA_PALETTE_DATA, entry->blue);
}

/* Set a font. */
#if 0
static void vga_font_set (uint8_t *font_data, unsigned int length)
{
  /* First, the sequencer. */
  /* Synchronous reset. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x01);

  /* CPU writes only to map 2. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x02);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x04);

  /* Sequential addressing. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x04);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x07);

  /* Clear synchronous reset. */
  
  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);
  
  /* Now, the graphics controller. */
  /* Select map 2. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x04);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x02);

  /* Disable odd-even addressing. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x05);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);

  /* Map start at A0000. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x06);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);
    
  memory_copy (graphic_video_memory, font_data, length);

  /* First, the sequencer. */
  /* Synchronous reset. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x01);

  /* CPU writes to maps 0 and 1. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x02);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);

  /* Odd-even addressing. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x04);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);

  /* Character Map Select. */
  
  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x03);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0);

  /* Clear synchronous reset. */

  port_uint8_out_pause (VGA_SEQUENCER_REGISTER, 0x00);
  port_uint8_out_pause (VGA_SEQUENCER_DATA, 0x03);
  
  /* Now, the graphics controller. */
  /* Select map 0 for CPU. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x04);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x00);

  /* Enable even-odd addressing. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x05);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x10);

  /* Map starts at B8000. */

  port_uint8_out_pause (VGA_GRAPHIC_REGISTER, 0x06);
  port_uint8_out_pause (VGA_GRAPHIC_DATA, 0x0E);
}
#endif
/* Place the text mode cursor. When in graphics mode, this function
   does nothing. */

void vga_cursor_place (int x, int y)
{
    uint16_t position = 0;

    if (current_mode != NULL)
    {
        if (current_mode->type != VIDEO_MODE_TYPE_TEXT)
        {
            return;
        }
    
        position = y * current_mode->width + x;
    
        /* Cursor position high. */
    
        port_uint8_out (VGA_CRT_CR_REGISTER, VGA_CRT_CR_CLR_HIGH);
        port_uint8_out (VGA_CRT_CR_DATA, UINT16_HIGH_UINT8 (position));
    
        /* Cursor position low. */
    
        port_uint8_out (VGA_CRT_CR_REGISTER, VGA_CRT_CR_CLR_LOW);
        port_uint8_out (VGA_CRT_CR_DATA, UINT16_LOW_UINT8 (position));
    }
}

