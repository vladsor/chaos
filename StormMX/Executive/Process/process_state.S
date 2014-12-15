
.globl process_load_state
.extern dump_stack

process_load_state:
        pushl %esp
        pushl %ss
        call dump_stack
        addl $8, %esp

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
