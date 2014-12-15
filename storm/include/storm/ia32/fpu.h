#ifndef __STORM_IA32_FPU_H__
#define __STORM_IA32_FPU_H__

/*
 *	Floating point registers and status, as saved
 *	and restored by FP save/restore instructions.
 */
typedef struct
{
  u16 fp_control;   /* control */
  u16 fp_unused_1;
  u16 fp_status;    /* status */
  u16 fp_unused_2;
  u16 fp_tag;       /* register tags */
  u16 fp_unused_3;
  u32 fp_eip;       /* eip at failed instruction */
  u16 fp_cs;        /* cs at failed instruction */
  u16 fp_opcode;    /* opcode of failed instruction */
  u32 fp_dp;        /* data address */
  u16 fp_ds;        /* data segment */
  u16 fp_unused_4;
} i386_fp_save;

typedef struct
{
  u16 fp_reg_word[5][8]; /* space for 8 80-bit FP registers */
} i386_fp_regs;

typedef struct
{
  i386_fp_save fp_save;
  i386_fp_regs fp_regs;
} i386_fpu_state;


static inline void fpu_save_state (u8 *state)
{
  asm volatile (
  "
    fsave %0
  "
  :
  : "m" (state));
}

static inline void fpu_restore_state (u8 *state)
{
  asm volatile (
  "
    frstor %0
  "
  :
  : "m" (state));
}


void fpu_init (void);

#endif /* __STORM_IA32_FPU_H__ */
