.globl jump_lowlevel

jump_lowlevel:
    movl %esp, %eax

    movl 0x04(%eax), %ebx
    movl %ebx, %esp

    movl 0x08(%eax), %ebx
    push %ebx
    movl 0x0C(%eax), %ebx
    push %ebx
    movl 0x10(%eax), %ebx
    push %ebx

    movl 0x14(%eax), %edi
    movl 0x18(%eax), %esi
    movl 0x1C(%eax), %ebp
    movl 0x20(%eax), %ebx
    movl 0x24(%eax), %edx
    movl 0x28(%eax), %ecx

    push %ebx
    movl %eax, %ebx
    movl 0x2C(%ebx), %eax
    pop %ebx

    iret

.globl iret_to_func

iret_to_func:
    addl $4, %esp

    movl $0, %edi
    movl $0, %esi
    movl $0, %ebp
    movl $0, %ebx
    movl $0, %edx
    movl $0, %ecx
    movl $0, %eax

    lret
