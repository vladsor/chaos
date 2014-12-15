/**
 * @file                fpu.h
 * @brief               FPU data structs and lowlevel routines.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2001-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_FPU_H__
#define __SYSTEM_ENVIROMENT_IA32_FPU_H__

/**
 * @brief               FPU Status Register.
 *
 * The 16-bit FPU status register indicates the current state of the FPU. The
 * flags in the FPU status register include the FPU busy flag, top-of-stack
 * (TOP) pointer, condition code flags, error summary status flag, stack fault
 * flag, and exception flags. The FPU sets the flags in this register to show
 * the results of operations.<BR>
 * The contents of the FPU status register (referred to as the FPU status word)
 * can be stored in memory using the FSTSW/FNSTSW, FSTENV/FNSTENV, and
 * FSAVE/FNSAVE instructions. It can also be stored in the AX register of the
 * integer unit, using the FSTSW/FNSTSW instructions.
 */
typedef struct
{
    /**
     * @brief           IE (bit 0) Exception Flag: Invalid Operand.
     */
    uint32_t            IE : 1;

    /**
     * @brief           DE (bit 1) Exception Flag: Denormalized Operand.
     */
    uint32_t            DE : 1;

    /**
     * @brief           ZE (bit 2) Exception Flag: Zero Divide.
     */
    uint32_t            ZE : 1;

    /**
     * @brief           OE (bit 3) Exception Flag: Overflow.
     */
    uint32_t            OE : 1;

    /**
     * @brief           UE (bit 4) Exception Flag: Underflow.
     */
    uint32_t            UE : 1;

    /**
     * @brief           PE (bit 5) Exception Flag: Precision.
     */
    uint32_t PE : 1;

    /**
     * @brief           SF (bit 6) Stack Fault.
     *
     * The stack fault flag (bit 6 of the FPU status word) indicates that stack 
     * overflow or stack underflow has occurred. The FPU explicitly sets the SF 
     * flag when it detects a stack overflow or underflow condition, but it does 
     * not explicitly clear the flag when it detects an invalid-arithmetic-operand
     * condition. When this flag is set, the condition code flag C1 indicates the
     * nature of the fault: overflow (C1 = 1) and underflow (C1 = 0). The SF flag
     * is a "sticky" flag, meaning that after it is set, the processor does not 
     * clear it until it is explicitly instructed to do so (for example, by an 
     * FINIT/FNINIT, FCLEX/FNCLEX, or FSAVE/FNSAVE instruction). Refer to Section
     * 7.3.6., "FPU Tag Word" for more information on FPU stack faults.
     */
    uint32_t            stack_fault : 1;

    /**
     * @brief           ES (bit 7) Error Summary Status.
     */
    uint32_t            error_summary_status : 1;

    /**
     * @brief           Condition Code (bit 8, 9, 10 and 14)
     */
    uint32_t            C0 : 1;

    /**
     * @brief           Condition Code (bit 8, 9, 10 and 14)
     */
    uint32_t            C1 : 1;

    /**
     * @brief           Condition Code (bit 8, 9, 10 and 14)
     */
    uint32_t            C2 : 1;

    /**
     * @brief           TOP (bit 11, 12 and 13) Top of Stack Pointer.
     */
    uint32_t            top_of_stack_pointer : 3;

    /**
     * @brief           Condition Code (bit 8, 9, 10 and 14)
     */
    uint32_t            C3 : 1;

    /**
     * @brief           B (bit 15) FPU Busy.
     */
    uint32_t            busy : 1;
    
} fpu_status_word_t PACKED;

/** 
 * @defgroup group_fpu_precision FPU precision flags
 *
 * @brief     
 *
 * @{
 */

/**
 * @brief               Single Precision (24-Bits)
 *
 * @note Includes the implied integer bit.
 */
#define FPU_PRECISION_SINGLE                  00B

/**
 * @brief               Double Precision (53-Bits)
 *
 * @note Includes the implied integer bit.
 */
#define FPU_PRECISION_DOUBLE                  10B

/**
 * @brief               Extended Precision (64-Bits)
 */
#define FPU_PRECISION_EXTENDED                11B

/**
 * @} // end of group_fpu_precision
 */

/** 
 * @defgroup group_fpu_round FPU round flags
 *
 * @brief     
 *
 * @{
 */

/**
 * @brief               Round to nearest (even)
 *
 * Rounded result is the closest to the infinitely precise result. If two
 * values are equally close, the result is the even value (that is, the one
 * with the least-significant bit of zero).
 */
#define FPU_ROUND_TO_NEAREST                  00B

/**
 * @brief               Round down
 *
 * Rounded result is close to but no greater than the infinitely precise result.
 */
#define FPU_ROUND_DOWN                        01B

/**
 * @brief               Round up
 *
 * Rounded result is close to but no less than the infinitely precise result.
 */
#define FPU_ROUND_UP                          10B

/**
 * @brief               Round toward zero (Truncate)
 *
 * Rounded result is close to but no greater in absolute value than the
 * infinitely precise result.
 */
#define FPU_ROUND_TOWARD                      11B

/**
 * @} // end of group_fpu_round
 */

/**
 * @brief               FPU Control Word
 *
 * The 16-bit FPU control word (refer to Figure 7-10) controls the precision of
 * the FPU and rounding method used. It also contains the exception-flag mask
 * bits. The control word is cached in the FPU control register. The contents
 * of this register can be loaded with the FLDCW instruction and stored in
 * memory with the FSTCW/FNSTCW instructions.<BR>
 * When the FPU is initialized with either an FINIT/FNINIT or FSAVE/FNSAVE
 * instruction, the FPU control word is set to 037FH, which masks all
 * floating-point exceptions, sets rounding to nearest, and sets the FPU
 * precision to 64 bits.
 */
typedef struct
{
    /**
     * @brief           IM (bit 0) Exception mask: Invalid Operation.
     */
    uint32_t            IM : 1;

    /**
     * @brief           DM (bit 1) Exception mask: Denormalized Operand.
     */
    uint32_t            DM : 1;

    /**
     * @brief           ZM (bit 2) Exception mask: Zero Devide.
     */
    uint32_t            ZM : 1;

    /**
     * @brief           OM (bit 3) Exception mask: Overflow.
     */
    uint32_t            OM : 1;

    /**
     * @brief           UM (bit 4) Exception mask: Enderfow.
     */
    uint32_t UM : 1;

    /**
     * @brief           PM (bit 5) Exception mask: Precision.
     */
    uint32_t            PM : 1;

    /* Not used. */
    uint32_t : 1;

    /* Not used. */
    uint32_t : 1;

    /**
     * @brief           PC (bit 8 and 9) Precision Control field.
     */
    uint32_t            precision_control : 2;

    /**
     * @brief           RC (bit 10 and 11) Rounding Control field.
     */
    uint32_t            rounding_control : 2;

    /**
     * @brief           X (bit 12) Infinity Control Flag
     *
     * The infinity control flag (bit 12 of the FPU control word) is provided
     * for compatibility with the Intel 287 Math Coprocessor; it is not
     * meaningful for the Pentium® Pro processor FPU or for the Pentium®
     * processor FPU, the Intel486™ processor FPU, or Intel 387 processor NPX.
     * Refer to Section 7.2.3.3., “Signed Infinities”, for information on how
     * the IA FPUs handle infinity values.
     */
    uint32_t            infinity_control : 1;

    /* Not used. */
    uint32_t : 1;

    /* Not used. */
    uint32_t : 1;

    /* Not used. */
    uint32_t : 1;
    
} fpu_control_word_t PACKED;


#define FPU_TAG_VALID                         00B

#define FPU_TAG_ZERO                          01B

/* Special: invalid (NaN, unsupported), infinity, or denormal */
#define FPU_TAG_SPECIAL                       10B

#define FPU_TAG_EMPTY                         11B

/**
 * @brief            FPU Tag Word
 *
 * The 16-bit tag word indicates the contents of each the 8 registers in the 
 * FPU data-register stack (one 2-bit tag per register). The tag codes indicate
 * whether a register contains a valid number, zero, or a special floating-point
 * number (NaN, infinity, denormal, or unsupported format), or whether it is
 * empty. The FPU tag word is cached in the FPU in the FPU tag word register.
 * When the FPU is initialized with either an FINIT/FNINIT or FSAVE/FNSAVE
 * instruction, the FPU tag word is set to FFFFH, which marks all the FPU data
 * registers as empty.
 */
typedef struct
{
    uint16_t         tag0 : 2;
    uint16_t         tag1 : 2;
    uint16_t         tag2 : 2;
    uint16_t         tag3 : 2;
    uint16_t         tag4 : 2;
    uint16_t         tag5 : 2;
    uint16_t         tag6 : 2;
    uint16_t         tag7 : 2;
} fpu_tag_word_t PACKED;

/**
 * @brief               Protected Mode FPU State Image in Memory, 32-Bit Format.
 */
typedef struct
{

  fpu_control_word_t control_word;
  uint16_t reserved0;

  fpu_status_word_t status_word;
  uint16_t reserved1;

  fpu_tag_word_t tag_word;
  uint16_t reserved2;

  uint32_t fpu_instruction_pointer_offset;

  uint16_t fpu_instruction_pointer_selector;
  uint16_t opcode : 11;
  uint16_t zero   : 5;

  uint32_t fpu_operand_pointer_offset;

  uint16_t fpu_operand_pointer_selector;
  uint16_t reserved3;

  long double st[8];  
} fpu_state_t PACKED;


static inline void fpu_enable (void)
{
    cpu_cr0_disable (CPU_CR0_EM);
}

static inline void fpu_disable (void)
{
    cpu_cr0_enable (CPU_CR0_EM);
}

static inline void fpu_init (void)
{
    asm volatile ("fninit");
}

/**
 * @brief               Save state of FPU.
 */
#define fpu_state_save(fpu_state)      \
    asm volatile ("fnsave %0"          \
                  :                    \
                  "=m" (fpu_state))

/**
 * @brief               Restore state of FPU.
 */
#define fpu_state_restore(fpu_state)   \
    asm volatile ("frstor %0"          \
                  : /* no output */    \
                  : "m" (fpu_state))

#endif /* !__SYSTEM_ENVIROMENT_IA32_FPU_H__ */

