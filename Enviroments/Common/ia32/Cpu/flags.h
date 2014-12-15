/**
 * @file                Common/ia32/Cpu/flags.h
 * @brief               Definitions of the bits in the flag field and some 
 *                      usefull functions to operate with flags.
 * @author              Per Lundberg <plundis@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.2
 * @date                2000-2004
 */

/* Copyright: chaos development. */

/** 
 * @addtogroup group_cpu
 *
 * @{
 */

#ifndef __ENVIROMENT_COMMON_IA32_CPU_FLAGS_H__
#define __ENVIROMENT_COMMON_IA32_CPU_FLAGS_H__

/**
 *  @brief              Structure of EFLAGS register.
 */
typedef struct
{
    /**
     * @brief           CF (bit 0) Carry flag. 
     *
     * Set if an arithmetic operation generates a carry or a borrow out of the 
     * most-significant bit of the result; cleared otherwise. This flag 
     * indicates an overflow condition for unsigned-integer arithmetic. It is 
     * also used in multiple-precision arithmetic.
     */
    uint32_t            carry : 1;

    /* Not used. */
    uint32_t : 1;
        
    /**
     * @brief           PF (bit 2) Parity flag.
     *
     * Set if the least-significant byte of the result contains an even number
     * of 1 bits; cleared otherwise.
     */
    uint32_t            parity : 1;

    /* Not used. */
    uint32_t : 1;

    /**
     * @brief           AF (bit 4) Adjust flag. 
     *
     * Set if an arithmetic operation generates a carry or a borrow out of bit 3 
     * of the result; cleared otherwise. This flag is used in binary-coded
     * decimal (BCD) arithmetic.
     */
    uint32_t            adjust : 1;

    /* Not used. */
    uint32_t : 1;

    /**
     * @brief           ZF (bit 6) Zero flag. 
     *
     * Set if the result is zero; cleared otherwise.
     */
    uint32_t            zero : 1;

    /**
     * @brief           SF (bit 7) Sign flag.
     *
     * Set equal to the most-significant bit of the result, which is the sign
     * bit of a signed integer. (0 indicates a positive value and 1 indicates a 
     * negative value.)
     */
    uint32_t            sign : 1;

    /**
     * @brief           TF (bit 8) Trap flag.
     *
     * Set to enable single-step mode for debugging; clear to disable
     * single-step mode.
     */
    uint32_t            trap : 1;

    /**
     * @brief           IF (bit 9) Interrupt enable flag.
     *
     * Controls the response of the processor to maskable interrupt requests.
     * Set to respond to maskable interrupts; cleared to inhibit maskable
     * interrupts.
     */
    uint32_t            interrupt_enable : 1;

    /**
     * @brief           DF (bit 10) Direction flag. 
     *
     * Controls the string instructions (MOVS, CMPS, SCAS, LODS, and STOS). 
     * Setting the DF flag causes the string instructions to auto-decrement
     * (that is, to process strings from high addresses to low addresses).
     * Clearing the DF flag causes the string instructions to auto-increment
     * (process strings from low addresses to high addresses).
     */
    uint32_t            direction : 1;

    /**
     * @brief           OF (bit 11) Overflow flag.
     *
     * Set if the integer result is too large a positive number or too small a 
     * negative number (excluding the sign-bit) to fit in the destination
     * operand; cleared otherwise. This flag indicates an overflow condition for
     * signed-integer (two's complement) arithmetic.
     */
    uint32_t            overflow : 1;

    /**
     * @brief           IOPL (bits 12, 13) I/O privilege level field.
     *
     * Indicates the I/O privilege level of the currently running program or
     * task. The current privilege level (CPL) of the currently running program
     * or task must be less than or equal to the I/O privilege level to access
     * the I/O address space. This field can only be modified by the POPF and
     * IRET instructions when operating at a CPL of 0.
     */
    uint32_t            io_privilege_level : 2;

    /**
     * @brief           NT (bit 14) Nested task flag.
     *
     * Controls the chaining of interrupted and called tasks. Set when the
     * current task is linked to the previously executed task; cleared when the
     * current task is not linked to another task.
     */
    uint32_t            nested : 1;

    /* Not used. */
    uint32_t : 1;

    /**
     * @brief           RF (bit 16) Resume flag.
     *
     * Controls the processor's response to debug exceptions.
     */
    uint32_t            resume : 1;

    /**
     * @brief           VM (bit 17) Virtual-8086 mode flag.
     *
     * Set to enable virtual-8086 mode; clear to return to protected mode.
     */
    uint32_t            virtual_8086_mode : 1;

    /**
     * @brief           AC (bit 18) Alignment check flag.
     *
     * Set this flag and the AM bit in the CR0 register to enable alignment 
     * checking of memory references; clear the AC flag and/or the AM bit to 
     * disable alignment checking. 
     */
    uint32_t            alignment_check : 1;

    /**
     * @brief           VIF (bit 19) Virtual interrupt flag.
     *
     * Virtual image of the IF flag. Used in conjunction with the VIP flag. (To 
     * use this flag and the VIP flag the virtual mode extensions are enabled by 
     * setting the VME flag in control register CR4.)
     */
    uint32_t            virtual_interrupt : 1;

    /**
     * @brief           VIP (bit 20) Virtual interrupt pending flag.
     *
     * Set to indicate pending interrupts; or clear when no interrupts are 
     * pending. (Software sets and clears this flag; the processor only reads
     * it.) Used in conjunction with the VIF flag.
     */
    uint32_t            virtual_interrupt_pending : 1;

    /**
     * @brief           ID (bit 21) Identification flag.
     *
     * The ability of a program to set or clear this flag indicates support for 
     * the CPUID instruction.
     */
    uint32_t            identification : 1;

    /* Not used. */
    uint32_t : 10;

} cpu_flags_t;

/**
 * @brief               Flags in the EFLAGS register. See the Intel
 *                      documentation for more information about what
 *                      those does.
 */
enum cpu_flag_t
{
    /**
     * @brief           CF (bit 0) Carry flag. 
     */
    CPU_FLAG_CARRY                     = (BIT_VALUE (0)),
    
    /**
     * @brief            Reserved (bit 1) Must be setted.
     */
    CPU_FLAG_SET                       = (BIT_VALUE (1)),
    
    /**
     * @brief           PF (bit 2) Parity flag.
     */
    CPU_FLAG_PARITY                    = (BIT_VALUE (2)),
    
    /**
     * @brief           AF (bit 4) Adjust flag. 
     */
    CPU_FLAG_ADJUST                    = (BIT_VALUE (4)),
    
    /**
     * @brief           ZF (bit 6) Zero flag. 
     */
    CPU_FLAG_ZERO                      = (BIT_VALUE (6)),

    /**
     * @brief           SF (bit 7) Sign flag.
     */
    CPU_FLAG_SIGN                      = (BIT_VALUE (7)),

    /**
     * @brief           TF (bit 8) Trap flag.
     */
    CPU_FLAG_TRAP                      = (BIT_VALUE (8)),

    /**
     * @brief           IF (bit 9) Interrupt enable flag.
     */
    CPU_FLAG_INTERRUPT_ENABLE          = (BIT_VALUE (9)),
    
    /**
     * @brief           DF (bit 10) Direction flag. 
     */
    CPU_FLAG_DIRECTION                 = (BIT_VALUE (10)),

    /**
     * @brief           OF (bit 11) Overflow flag.
     */
    CPU_FLAG_OVERFLOW                  = (BIT_VALUE (11)),
    
    /**
     * @brief           IOPL (bits 12, 13) I/O privilege level field.
     */
    CPU_FLAG_IOPL_LOW                  = (BIT_VALUE (12)),

    /**
     * @brief           IOPL (bits 12, 13) I/O privilege level field.
     */
    CPU_FLAG_IOPL_HIGH                 = (BIT_VALUE (13)),

    /**
     * @brief           NT (bit 14) Nested task flag.
     */
    CPU_FLAG_NESTED_TASK               = (BIT_VALUE (14)),

    /**
     * @brief           RF (bit 16) Resume flag.
     */
    CPU_FLAG_RESUME_TASK               = (BIT_VALUE (16)),
    
    /**
     * @brief           VM (bit 17) Virtual-8086 mode flag.
     */
    CPU_FLAG_V8086_MODE                = (BIT_VALUE (17)),

    /**
     * @brief           AC (bit 18) Alignment check flag.
     */
    CPU_FLAG_ALIGNMENT_CHECK           = (BIT_VALUE (18)),

    /**
     * @brief           VIF (bit 19) Virtual interrupt flag.
     */
    CPU_FLAG_VIRTUAL_INTERRUPT         = (BIT_VALUE (19)),

    /**
     * @brief           VIP (bit 20) Virtual interrupt pending flag.
     */
    CPU_FLAG_VIRTUAL_INTERRUPT_PENDING = (BIT_VALUE (20)),

    /**
     * @brief           ID (bit 21) Identification flag.
     */
    CPU_FLAG_ID                        = (BIT_VALUE (21))
};

/**
 * @brief               Save flags register.
 */
#define cpu_flags_save(save_flags)       \
    asm volatile ("pushf\n"              \
                  "popl %0"              \
                  :                      \
                  "=rm" (save_flags))

/**
 * @brief               Load flags register.
 */
#define cpu_flags_load(load_flags)       \
    asm volatile ("pushl %0\n"           \
                  "popf"                 \
                  : /* no output */      \
                  :                      \
                  "g" (load_flags))

/**
 * @brief               Enable flags.
 * @param enable_flags  Enabled flags.
 */
static inline void cpu_flags_enable (uint32_t enable_flags)
{                                    
    register uint32_t temp_flags;    
    
    cpu_flags_save (temp_flags);
    
    temp_flags |= enable_flags;
    
    cpu_flags_load (temp_flags);
}

/**
 * @brief               Disable flags.
 * @param mask_flags    Disabled flags.
 */
static inline void cpu_flags_disable (uint32_t mask_flags)
{                                        
    register uint32_t temp_flags;        
    
    cpu_flags_save (temp_flags);
    
    temp_flags &= mask_flags;
    
    cpu_flags_load (temp_flags);
}

/**
 * @brief               Toggle flags.
 * @param mask_flags    Toggled flags.
 */
static inline void cpu_flags_toggle (uint32_t mask_flags)
{                                        
    register uint32_t temp_flags;        
    
    cpu_flags_save (temp_flags);
    
    temp_flags ^= mask_flags;
    
    cpu_flags_load (temp_flags);
}

/**
 * @brief               Testing flags.
 * @param test_flags    test mask.
 * @return              TRUE if flags toggled successfull, FALSE otherwise.
 */
static inline bool cpu_flags_test (uint32_t test_flags)
{
    register uint32_t masked_flags;
    register uint32_t old_flags;

    cpu_flags_save (old_flags);
    old_flags ^= test_flags;
    cpu_flags_load (old_flags);
    cpu_flags_save (old_flags);
    masked_flags = old_flags;
    old_flags ^= test_flags;
    cpu_flags_load (old_flags);

    return ((masked_flags ^ old_flags) == test_flags);
}

#endif /* !__ENVIROMENT_COMMON_I32_CPU_FLAGS_H__ */

/**
 * }@ // end of group group_cpu
 */

