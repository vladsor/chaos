/* $Id: vga.h,v 1.1 2001/02/10 22:58:38 jojo Exp $ */
/* Abstract: VGA header file. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __VGA_H__
#define __VGA_H__

#define VGA_PORT_BASE           0x3C0
#define VGA_PORTS               32
#define VGA_PALETTE_READ        (VGA_PORT_BASE + 7)
#define VGA_PALETTE_WRITE       (VGA_PORT_BASE + 8)
#define VGA_PALETTE_DATA        (VGA_PORT_BASE + 9)
#define VGA_SEQUENCER_REGISTER  0x3C4
#define VGA_SEQUENCER_DATA      0x3C5
#define VGA_GRAPHIC_REGISTER    0x3CE
#define VGA_GRAPHIC_DATA        0x3CF

#define VGA_CRT_CR_REGISTER    0x3D4
#define VGA_CRT_CR_DATA     0x3D5

#define VGA_CRT_CR_HTR          0x00
#define VGA_CRT_CR_HDER         0x01
#define VGA_CRT_CR_SHBR         0x02
#define VGA_CRT_CR_EHBR         0x03
#define VGA_CRT_CR_SHRR         0x04  
#define VGA_CRT_CR_EHRR         0x05
#define VGA_CRT_CR_VTR          0x06
#define VGA_CRT_CR_OVR          0x07
#define VGA_CRT_CR_PRSR         0x08
#define VGA_CRT_CR_MSLR         0x09
#define VGA_CRT_CR_CSR          0x0A
#define VGA_CRT_CR_CER          0x0B
#define VGA_CRT_CR_SAR_HIGH     0x0C
#define VGA_CRT_CR_SAR_LOW      0x0D
#define VGA_CRT_CR_CLR_HIGH     0x0E
#define VGA_CRT_CR_CLR_LOW      0x0F
#define VGA_CRT_CR_VRSR         0x10
#define VGA_CRT_CR_VRER         0x11
#define VGA_CRT_CR_LPAR_HIGH    0x10
#define VGA_CRT_CR_LPAR_LOW     0x11
#define VGA_CRT_CR_VDER         0x12
#define VGA_CRT_CR_OFR          0x13
#define VGA_CRT_CR_ULR          0x14
#define VGA_CRT_CR_SVBR         0x15
#define VGA_CRT_CR_EVBR         0x16 
#define VGA_CRT_CR_MCR          0x17
#define VGA_CRT_CR_LCR          0x18

#define VGA_MEMORY              0xA0000
#define VGA_MEMORY_SIZE         (64 * KIB)

extern video_palette_t text_palette[];

extern void vga_cursor_place (int x, int y);
extern uint8_t *graphic_video_memory;
extern bool mode_set (unsigned int width, unsigned int height,
                      unsigned int bpp, unsigned int type);

#endif /* !__VGA_H__ */
