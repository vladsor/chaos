/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                irq.h
 * @brief               IRQ handling.
 */

#ifndef __COMMON_IRQ_H__
#define __COMMON_IRQ_H__

typedef struct
{
    /**
     * @brief           These are gently stored by a pusha. 
     */
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;

    /**
     * @brief           The current (or next) instruction. 
     */
    uint32_t eip;

    /**
     * @brief           The code segment selector.
     */
    uint32_t cs;

    /* @brief           EFLAGS get pushed first. 
     */
    uint32_t eflags;
} irq_cpu_registers_t;

typedef irq_cpu_registers_t * p_irq_cpu_registers_t;

/**
 * @brief               An IRQ handler.
 */
typedef void (irq_handler_t) (unsigned int irq_number, p_void_t parameter, 
    irq_cpu_registers_t irq_cpu_registers);

typedef irq_handler_t * p_irq_handler_t;

#endif /* !__COMMON_IRQ_H__ */
