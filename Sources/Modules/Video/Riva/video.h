enum
{
  DPMSModeOn,
  DPMSModeStandby,
  DPMSModeSuspend,
  DPMSModeOff,
};

extern void NV1DisplayPowerManagementSet (int mode);
extern void MapNvRegs(void *base);

struct riva_info_type;
struct riva_state_type;

/*
 * Virtialized chip interface. Makes RIVA 128 and TNT look alike.
 */
typedef struct
{
    /*
     * Chip specific settings.
     */
    unsigned Architecture;
    unsigned Version;
    unsigned CrystalFreqKHz;
    unsigned RamAmountKBytes;
    unsigned MaxVClockFreqKHz;
    unsigned RamBandwidthKBytesPerSec;
    unsigned EnableIRQ;
    unsigned IO;
    unsigned LockUnlockIO;
    unsigned LockUnlockIndex;
    unsigned VBlankBit;
    unsigned FifoFreeCount;
    unsigned FifoEmptyCount;
    /*
     * Non-FIFO registers.
     */
    volatile unsigned *PCRTC;
    volatile unsigned *PRAMDAC;
    volatile unsigned *PFB;
    volatile unsigned *PFIFO;
    volatile unsigned *PGRAPH;
    volatile unsigned *PEXTDEV;
    volatile unsigned *PTIMER;
    volatile unsigned *PMC;
    volatile unsigned *PRAMIN;
    volatile unsigned *FIFO;
    volatile unsigned *CURSOR;
    volatile unsigned *CURSORPOS;
    volatile unsigned *VBLANKENABLE;
    volatile unsigned *VBLANK;
    /*
     * Common chip functions.
     */
    int  (*Busy) (struct riva_info_type *);
    void (*CalcStateExt) (struct riva_info_type *, struct riva_state_type *,int,int,int,int,int,int,int,int,int,int,int,int,int);
    void (*LoadStateExt) (struct riva_info_type *, struct riva_state_type *);
    void (*UnloadStateExt)(struct riva_info_type *, struct riva_state_type *);
    void (*SetStartAddress)(struct riva_info_type *, unsigned);
    void (*SetSurfaces2D)(struct riva_info_type *, unsigned,unsigned);
    void (*SetSurfaces3D)(struct riva_info_type *, unsigned,unsigned);
    int  (*ShowHideCursor)(struct riva_info_type *, int);
    /*
     * Current extended mode settings.
     */
    struct _riva_hw_state *CurrentState;
    /*
     * FIFO registers.
     */
//    RivaRop                 *Rop;
//    RivaPattern             *Patt;
//    RivaClip                *Clip;
//    RivaPixmap              *Pixmap;
//    RivaScreenBlt           *Blt;
//    RivaBitmap              *Bitmap;
//    RivaTexturedTriangle03  *Tri03;
//    RivaTexturedTriangle05  *Tri05;

} riva_info_type;
/*
 * Extended mode state information.
 */
typedef struct
{
    unsigned bpp;
    unsigned width;
    unsigned height;
    unsigned repaint0;
    unsigned repaint1;
    unsigned screen;
    unsigned pixel;
    unsigned horiz;
    unsigned arbitration0;
    unsigned arbitration1;
    unsigned vpll;
    unsigned pllsel;
    unsigned general;
    unsigned config;
    unsigned cursor0;
    unsigned cursor1;
    unsigned cursor2;
    unsigned offset0;
    unsigned offset1;
    unsigned offset2;
    unsigned offset3;
    unsigned pitch0;
    unsigned pitch1;
    unsigned pitch2;
    unsigned pitch3;
} riva_state_type;
