#include <enviroment.h>
#include "vgaio.h"

/* variables used to shift between monchrome and color emulation */

/* current CRT index register address */
int vga_CRT_I;                    

/* current CRT data register address */
int vga_CRT_D;                    

/* current input status register address */
int vga_IS1_R;                    

/* true if color text emulation */
static bool color_text = TRUE;          

void vga_io_init (void)
{
//  debug_print ("VGA IO init.\n");
    /* chose registers for color/monochrome emulation */
    if (color_text) 
    {
        vga_CRT_I = CRT_IC;
        vga_CRT_D = CRT_DC;
        vga_IS1_R = IS1_RC;
    } else 
    {
        vga_CRT_I = CRT_IM;
        vga_CRT_D = CRT_DM;
        vga_IS1_R = IS1_RM;
    }
}

void vga_delay (void)
{
    int i;
    for (i = 0; i < 10; i++);
}

int vga_misc_in (void)
{
   return port_uint8_in (MIS_R);
}

void vga_misc_out (int i)
{
   port_uint8_out(MIS_W, i);
}

int vga_crtc_in (int i)
{
   port_uint8_out (vga_CRT_I, i);
   return port_uint8_in (vga_CRT_D);
}

void vga_crtc_out (int i, int d)
{
    port_uint8_out (vga_CRT_I, i);
    port_uint8_out (vga_CRT_D, d);
}

int vga_seq_in (int index)
{
    port_uint8_out (SEQ_I, index);
    return port_uint8_in (SEQ_D);
}

void vga_seq_out (int index, int val)
{
    port_uint8_out (SEQ_I, index);
    port_uint8_out (SEQ_D, val);
}

int vga_gra_in (int index)
{
    port_uint8_out (GRA_I, index);
    return port_uint8_in(GRA_D);
}

void vga_gra_out (int index, int val)
{
    port_uint8_out (GRA_I, index);
    port_uint8_out (GRA_D, val);
}

int vga_is1_in (void)
{
   return port_uint8_in (vga_IS1_R);
}

#ifdef NO_DELAY

int __svgalib_vga_inatt(int index)
{
    __svgalib_vga_inis1();
    outb(ATT_IW, index);
    return port_in(ATT_R);
}

void __svgalib_vga_outatt(int index, int val)
{
    __svgalib_vga_inis1();
    outb(ATT_IW, index);
    outb(ATT_IW, val);
}

void __svgalib_vga_attscreen(int i)
{
    __svgalib_vga_inis1();
    outb(ATT_IW, i);
}

void __svgalib_vga_inpal(int i, int *r, int *g, int *b)
{
    outb(PEL_IR,i);
    *r=port_in(PEL_D);
    *g=port_in(PEL_D);
    *b=port_in(PEL_D);
}

void __svgalib_vga_outpal(int i, int r, int g, int b)
{

    outb(PEL_IW,i);
    outb(PEL_D,r);
    outb(PEL_D,g);
    outb(PEL_D,b);
}

#else /* NO_DELAY */

int vga_att_in (int index)
{
    vga_delay ();
    vga_is1_in ();
    vga_delay ();
    port_uint8_out (ATT_IW, index);
    vga_delay ();
    return port_uint8_in (ATT_R);
}

void vga_att_out (int index, int val)
{
    vga_delay ();
    vga_is1_in ();
    vga_delay ();
    port_uint8_out (ATT_IW, index);
    vga_delay ();
    port_uint8_out (ATT_IW, val);
}

void vga_attscreen(int i)
{
    vga_delay ();
    vga_is1_in ();
    vga_delay ();
    port_uint8_out (ATT_IW, i);
}

void vga_pal_in (int i, int *r, int *g, int *b)
{
    port_uint8_out (PEL_IR, i);
    vga_delay ();
    (*r) = port_uint8_in (PEL_D);
    vga_delay ();
    (*g) = port_uint8_in (PEL_D);
    vga_delay ();
    (*b) = port_uint8_in (PEL_D);
}

void vga_pal_out (int i, int r, int g, int b)
{
    port_uint8_out (PEL_IW, i);
    vga_delay ();
    port_uint8_out (PEL_D, r);
    vga_delay ();
    port_uint8_out (PEL_D, g);
    vga_delay ();
    port_uint8_out (PEL_D, b);
}

#endif /* NO_DELAY */
