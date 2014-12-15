/* $chaos: irq_handlers.S,v 1.6 2002/10/04 19:01:21 per Exp $ */
/* Abstract: IRQ management. */

/* Author: Per Lundberg <per@chaosdev.org>, Vladimir Sorokin */
    
/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* One interrupt handler for each interrupt, thank you verymuch. */

.extern irq_handlers
.extern irq_handlers_data
.extern current_stack_pointer
.extern pic_acknowledge
    
#define IRQ_HANDLER(x) \
.globl irq ## x ## _handler ;\
irq ## x ## _handler: \
   pushal ;\
   movl %esp, current_stack_pointer ;\
   movl (irq_handlers + x * 4), %eax ;\
   cmpl $0, %eax ;\
   je end_irq##x ;\
   movl (irq_handlers_data + x * 4), %ebx ;\
   pushl %ebx ;\
   call *%eax ;\
   addl $4, %esp ;\
   pushl $ x ;\
   call pic_acknowledge ;\
   movl current_stack_pointer, %esp ;\
   popal ;\
   iret; \
end_irq##x: \
   pushl $ x ;\
   call pic_acknowledge ;\
   addl $4, %esp ;\
   popal ;\
   iret


IRQ_HANDLER (0);
IRQ_HANDLER (1);
IRQ_HANDLER (3);
IRQ_HANDLER (4);
IRQ_HANDLER (5);
IRQ_HANDLER (6);
IRQ_HANDLER (7);
IRQ_HANDLER (8);
IRQ_HANDLER (9);
IRQ_HANDLER (10);
IRQ_HANDLER (11);
IRQ_HANDLER (12);
IRQ_HANDLER (13);
IRQ_HANDLER (14);
IRQ_HANDLER (15);
