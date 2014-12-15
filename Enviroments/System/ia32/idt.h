/* $chaos: idt.h,v 1.7 2002/10/24 21:37:41 per Exp $ */

/**
 * @file                idt.h
 * @brief               Function prototypes for IDT functions. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.8
 * @date                1998-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_IDT_H__
#define __SYSTEM_ENVIROMENT_IA32_IDT_H__

/**
 * @brief               The IDT (Interrupt Descriptors Table).
 */
extern descriptor_t     idt[];

/**
 * @brief               Create a trap gate in the IDT. 
 * @param entry         The number of the IDT entry.
 * @param selector      The selector to point at.
 * @param address       The address of the function to call as the
 *                      exception handler.
 * @param rpl           The RPL (Requestors Privilege Level) of this gate.
 */
static inline void idt_setup_trap_gate (uint16_t entry, uint16_t selector, 
    address_t address, uint8_t rpl)
{
  ((uint64_t *) idt)[entry] = DESCRIPTOR_TRAP_GATE (selector, 
      (uint32_t) address, rpl, SEGMENT_PRESENT);
}

/**
 * @brief               Create an interrupt gate in the IDT. 
 * @param entry         The number of the IDT entry.
 * @param selector      The selector to point at.
 * @param address       The address of the function to call as the
 *                      exception handler.
 * @param rpl           The RPL (Requestors Privilege Level) of this gate.
 */
static inline void idt_setup_interrupt_gate (uint16_t entry, uint16_t selector,
    address_t address, uint8_t rpl)
{
  ((uint64_t *) idt)[entry] = DESCRIPTOR_INTERRUPT_GATE (selector, 
      (uint32_t) address, rpl, SEGMENT_PRESENT);
}

#endif /* !__SYSTEM_ENVIROMENT_IA32_IDT_H__ */

