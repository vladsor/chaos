#include <enviroment.h>
#include <memory_inlines.h>

#include "vga.h"
#include "font_8x8.h"

uint8_t *graphic_video_memory = (uint8_t *) 0xA0000;

uint8_t mode_80x50[] = {
    0x067, 0x000, 0x003, 0x000, 0x003, 0x000, 0x002, 0x05F, 0x04F, 0x050, 0x082, 0x055, 0x081, 0x0BF, 0x01F, 0x000,
    0x047, 0x006, 0x007, 0x000, 0x000, 0x000, 0x000, 0x09C, 0x08E, 0x08F, 0x028, 0x01F, 0x096, 0x0B9, 0x0A3, 0x0FF,
    0x000, 0x000, 0x000, 0x000, 0x000, 0x010, 0x00E, 0x000, 0x0FF, 0x000, 0x001, 0x002, 0x003, 0x004, 0x005, 0x014,
    0x007, 0x038, 0x039, 0x03A, 0x03B, 0x03C, 0x03D, 0x03E, 0x03F, 0x00C, 0x000, 0x00F, 0x008, 0x000,
};

uint8_t mode_320x200x256[] = {
    0x63, 0x00, 0x03, 0x01, 0x0F, 0x00, 0x0E, 0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
};
/*
mode_640x400x256:
        db   063h, 000h, 003h, 001h, 00Fh, 000h, 006h, 05Fh, 04Fh, 050h, 082h, 054h, 080h, 0BFh, 01Fh, 000h
        db   040h, 000h, 000h, 000h, 000h, 000h, 000h, 09Ch, 08Eh, 08Fh, 050h, 000h, 096h, 0B9h, 0E3h, 0FFh
        db   000h, 000h, 000h, 000h, 000h, 040h, 005h, 00Fh, 0FFh, 000h, 001h, 002h, 003h, 004h, 005h, 006h
        db   007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh, 041h, 000h, 00Fh, 000h, 000h

mode_640x480x16:
        db   0E3h, 000h, 003h, 001h, 00Fh, 000h, 006h, 05Fh, 04Fh, 050h, 082h, 054h, 080h, 00Bh, 03Eh, 000h
        db   040h, 000h, 000h, 000h, 000h, 000h, 000h, 0EAh, 08Ch, 0DFh, 028h, 000h, 0E7h, 004h, 0E3h, 0FFh
        db   000h, 000h, 000h, 000h, 000h, 000h, 005h, 00Fh, 0FFh, 000h, 001h, 002h, 003h, 004h, 005h, 014h
        db   007h, 038h, 039h, 03Ah, 03Bh, 03Ch, 03Dh, 03Eh, 03Fh, 001h, 000h, 00Fh, 000h, 000h
*/

uint8_t *mode_table[] = 
{
    mode_320x200x256,
    mode_80x50,
  //  mode_640x480x16,
//    mode_640x400x256,
};

bool mode_t_table[] = 
{
    0,
    1,
//    0,
//    0,
};

unsigned int mode_t_len = sizeof (mode_t_table) / sizeof (bool);
void set_mode (uint8_t regs[]);
int vga_set_mode (int mode);
void load_font (uint8_t *font_ptr, unsigned font_bytes);

int main(void)
{
    vga_set_mode (1);
    
    while (1);
    
    return;
}
#if 0
int vga_set_mode (int mode)
{
    set_mode (mode_table[mode]);
/*    
    if(mode_t_table[mode])
    {
        load_font (font_8x8, 8);
    }
*/    
}

void set_mode (uint8_t regs[])
{
    unsigned int i,j;
    
    j = 0;                
    port_uint8_out (0x3C2, regs[j]);
    j++;
             
    port_uint8_out (0x3DA, regs[j]);
    j++;
    
    for (i=0;i<5;i++)
    {
        port_uint16_out (0x3C4, regs[j] << 8 | i);
        j++;
    }

    port_uint16_out (0x3D4, 0x0E11);

    for (i=0; i<25;i++)
    {
        port_uint16_out (0x3D4, regs[j] << 8 | i);
        j++;
    }

    for (i=0;i<9;i++)
    {
        port_uint16_out (0x3CE, regs[j] << 8 | i);
        j++;
    }

    port_uint8_in (0x3DA);        

    for (i=0;i<21;i++)
    {
        port_uint8_in (0x3C0);
        port_uint8_in (0x3C0);
        port_uint8_out (0x3C0, i);
        
        port_uint8_out (0x3C0, regs[j]);
        j++;
    }

    port_uint8_out (0x3C0, 0x20);
}


void load_font (uint8_t *font_ptr, unsigned font_bytes)
{
    uint8_t vga_buff[300];
    unsigned int i, j = 0;
    unsigned int tmp;
    uint8_t *video_memory = (uint8_t *) VGA_MEMORY;
           
    port_uint8_out (0x3CE, 5);

    tmp = port_uint8_in (0x3CE + 1);

    vga_buff[j] = tmp;
    j++;
                
    port_uint16_out (0x3CE, (tmp & 0xFC) << 8 | 5);

    port_uint16_out (0x3CE, 6);
                
    tmp = port_uint8_in (0x3CE + 1);

    vga_buff[j] = tmp;
    j++;

    port_uint16_out (0x3CE, ((tmp & 0xF1) | 4) << 8 | 6);

    port_uint8_out (0x3C4, 2);

    tmp = port_uint8_in (0x3C4 + 1);

    vga_buff[j] = tmp;
    j++;                

    port_uint16_out (0x3C4, 0x402);

    port_uint8_out (0x3C4, 0x4);

    tmp = port_uint8_in (0x3C4 + 1);

    vga_buff[j] = tmp;
    j++;                

    port_uint16_out (0x3C4, (tmp | 4) << 8 | 4);

    for (i=0;i<256;i++)
    {
        memory_copy (video_memory + i * 32, font_ptr + i * font_bytes, font_bytes);
        memory_set_uint8 (video_memory, 0, 32 - font_bytes);
    }
            
    j = 0;                

    port_uint16_out (0x3CE, (vga_buff[j] << 8) | 5);
    j++;

    port_uint16_out (0x3CE, (vga_buff[j] << 8) | 6);
    j++;

    port_uint16_out (0x3C4, (vga_buff[j] << 8) | 2);
    j++;

    port_uint16_out (0x3C4, (vga_buff[j] << 8) | 4);
    j++;
}

#endif
