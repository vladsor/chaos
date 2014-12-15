        port_channel_0  equ 40h
        quarz_frequancy equ 1193180 

set_timer macro
        out port_channel_0, al
        xchg ah, al
        out port_channel_1, al
endm
read_timer macro
        in al, port_channel_0
        mov ah, al
        in al, port_channel_0
        xchg ah, al
endm
