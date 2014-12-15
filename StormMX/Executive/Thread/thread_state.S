
.globl thread_yield

.extern thread_switch_to_next
.extern current_stack_pointer    

thread_yield:
    pushfl 
    pushl $0
    pushl %eax
    movl 12(%esp), %eax
    movl %eax, 4(%esp)
    movl 8(%esp), %eax
    movl %eax, 12(%esp)
    movl $8, %eax
    movl %eax, 8(%esp)
    popl %eax
    pushal ;
    movl %esp, current_stack_pointer ;

    call thread_switch_to_next ;

    movl current_stack_pointer, %esp ;
    popal;
    iret

.globl thread_exit_lowlevel
.extern thread_exit

thread_exit_lowlevel:
    pushl %eax

    call thread_exit

.globl thread_load_state
.globl thread_load_state2
.extern dump_stack
.extern current_stack_pointer

thread_load_state2:
   movl current_stack_pointer, %esp ;
   
thread_load_state:
        popl    %edi
        popl    %esi
        popl    %ebp

        /* %esp can't be popped for obvious reasons. */
        addl    $4, %esp

        popl    %ebx
        popl    %edx
        popl    %ecx
        popl    %eax

        iret
