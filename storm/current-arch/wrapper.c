
/* Generated automatically by system_calls.pl */

#include <storm/ia32/defines.h>
#include <storm/ia32/wrapper.h>

void wrapper_init (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */


                call	init

                addl	$4 * 0, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 0
  ");
}

void wrapper_kernelfs_entry_read (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	kernelfs_entry_read

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_mailbox_create (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)

                call	mailbox_create

                addl	$4 * 5, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 5
  ");
}

void wrapper_mailbox_destroy (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	mailbox_destroy

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_mailbox_flush (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	mailbox_flush

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_mailbox_send (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 2 * 4(%esp)
                pushl  32 + 4 + 2 * 4(%esp)

                call	mailbox_send

                addl	$4 * 2, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 2
  ");
}

void wrapper_mailbox_receive (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 2 * 4(%esp)
                pushl  32 + 4 + 2 * 4(%esp)

                call	mailbox_receive

                addl	$4 * 2, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 2
  ");
}

void wrapper_service_create (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	service_create

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_service_destroy (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	service_destroy

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_service_get (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	service_get

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_dma_transfer (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)
                pushl  32 + 4 + 5 * 4(%esp)

                call	dma_transfer

                addl	$4 * 5, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 5
  ");
}

void wrapper_dma_transfer_cancel (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	dma_transfer_cancel

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_dma_register (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 2 * 4(%esp)
                pushl  32 + 4 + 2 * 4(%esp)

                call	dma_register

                addl	$4 * 2, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 2
  ");
}

void wrapper_dma_unregister (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	dma_unregister

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_irq_register (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 2 * 4(%esp)
                pushl  32 + 4 + 2 * 4(%esp)

                call	irq_register

                addl	$4 * 2, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 2
  ");
}

void wrapper_irq_unregister (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	irq_unregister

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_irq_wait (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	irq_wait

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_irq_acknowledge (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	irq_acknowledge

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_memory_allocate (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	memory_allocate

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_memory_deallocate (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	memory_deallocate

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_memory_reserve (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	memory_reserve

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_memory_virtual_map (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 4 * 4(%esp)
                pushl  32 + 4 + 4 * 4(%esp)
                pushl  32 + 4 + 4 * 4(%esp)
                pushl  32 + 4 + 4 * 4(%esp)

                call	memory_virtual_map

                addl	$4 * 4, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 4
  ");
}

void wrapper_memory_get_physical_address (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 2 * 4(%esp)
                pushl  32 + 4 + 2 * 4(%esp)

                call	memory_get_physical_address

                addl	$4 * 2, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 2
  ");
}

void wrapper_port_range_register (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	port_range_register

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_port_range_unregister (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	port_range_unregister

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_debug_print_simple (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	debug_print_simple

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_process_create (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	process_create

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_process_name_set (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	process_name_set

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_process_parent_unblock (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */


                call	process_parent_unblock

                addl	$4 * 0, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 0
  ");
}

void wrapper_thread_create (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */


                call	thread_create

                addl	$4 * 0, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 0
  ");
}

void wrapper_thread_control (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)
                pushl  32 + 4 + 3 * 4(%esp)

                call	thread_control

                addl	$4 * 3, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 3
  ");
}

void wrapper_thread_name_set (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	thread_name_set

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_timer_read (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */

                pushl  32 + 4 + 1 * 4(%esp)

                call	timer_read

                addl	$4 * 1, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 1
  ");
}

void wrapper_dispatch_next (void)
{
  asm ("
                pushal

                /* Push all arguments. This is pretty smart... */


                call	dispatch_next

                addl	$4 * 0, %esp

		/* Simulate a popa, without overwriting EAX. */

		popl	%edi
		popl	%esi
		popl	%ebp

		/* ESP can't be popped for obvious reasons. */

		addl	$4, %esp
		popl	%ebx
		popl	%edx
		popl	%ecx

		/* EAX shall not be changed, since it is our return
          	  value. */

		addl	$4, %esp
		lret	$4 * 0
  ");
}
