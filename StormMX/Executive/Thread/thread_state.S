
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
