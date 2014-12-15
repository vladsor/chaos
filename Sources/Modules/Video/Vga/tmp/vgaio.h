/* VGA index register ports */
#define CRT_IC  0x3D4		/* CRT Controller Index - color emulation */
#define CRT_IM  0x3B4		/* CRT Controller Index - mono emulation */
#define ATT_IW  0x3C0		/* Attribute Controller Index & Data Write Register */
#define GRA_I   0x3CE		/* Graphics Controller Index */
#define SEQ_I   0x3C4		/* Sequencer Index */
#define PEL_IW  0x3C8		/* PEL Write Index */
#define PEL_IR  0x3C7		/* PEL Read Index */

/* VGA data register ports */
#define CRT_DC  0x3D5		/* CRT Controller Data Register - color emulation */
#define CRT_DM  0x3B5		/* CRT Controller Data Register - mono emulation */
#define ATT_R   0x3C1		/* Attribute Controller Data Read Register */
#define GRA_D   0x3CF		/* Graphics Controller Data Register */
#define SEQ_D   0x3C5		/* Sequencer Data Register */
#define MIS_R   0x3CC		/* Misc Output Read Register */
#define MIS_W   0x3C2		/* Misc Output Write Register */
#define IS1_RC  0x3DA		/* Input Status Register 1 - color emulation */
#define IS1_RM  0x3BA		/* Input Status Register 1 - mono emulation */
#define PEL_D   0x3C9		/* PEL Data Register */
#define PEL_MSK 0x3C6		/* PEL mask register */

/* EGA-specific registers */
#define GRA_E0	0x3CC		/* Graphics enable processor 0 */
#define GRA_E1	0x3CA		/* Graphics enable processor 1 */

/* standard VGA indexes max counts */
#define CRT_C   24		/* 24 CRT Controller Registers */
#define ATT_C   21		/* 21 Attribute Controller Registers */
#define GRA_C   9		/* 9  Graphics Controller Registers */
#define SEQ_C   5		/* 5  Sequencer Registers */
#define MIS_C   1		/* 1  Misc Output Register */

/* VGA registers saving indexes */
#define CRT     0		/* CRT Controller Registers start */
#define ATT     (CRT+CRT_C)	/* Attribute Controller Registers start */
#define GRA     (ATT+ATT_C)	/* Graphics Controller Registers start */
#define SEQ     (GRA+GRA_C)	/* Sequencer Registers */
#define MIS     (SEQ+SEQ_C)	/* General Registers */
#define EXT     (MIS+MIS_C)	/* SVGA Extended Registers */

#define GRAPH_BASE 0xA0000
#define FONT_BASE  0xA0000
#define GRAPH_SIZE 0x10000
#define FONT_SIZE  (0x2000 * 4) /* 2.0.x kernel can use 2 512 char. fonts */
#define GPLANE16   G640x350x16

extern int vga_CRT_I;		/* current CRT index register address */
extern int vga_CRT_D;		/* current CRT data register address */
extern int vga_IS1_R;		/* current input status register address */

extern int  vga_misc_in (void);
extern void vga_misc_out (int i);
extern int  vga_crtc_in (int i);
extern void vga_crtc_out (int i, int d);
extern int  vga_seq_in (int i);
extern void vga_seq_out (int i, int d);
extern int  vga_gra_in (int i);
extern void vga_gra_out (int i, int d);
extern int  vga_is1_in (void);
extern int  vga_att_in (int i);
extern void vga_att_out (int i, int d);
extern void vga_attscreen (int i);
extern void vga_pal_in (int i, int *r, int *g, int *b);
extern void vga_pal_out (int i, int r, int g, int b);
