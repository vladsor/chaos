; Filename: cpuid3a.asm
; Copyright 1993, 1994, 1995, 1996, 1997 by Intel Corp.
;
 jumps ;
TITLE cpuid3a
;
; comment this line for 32-bit segments
;
DOSSEG
;
; uncomment the following 2 lines for 32-bit segments
;
; .386
; .model flat
;
; comment this line for 32-bit segments
;

.model small

CPU_ID MACRO
        db 0fh                  ; Hardcoded CPUID instruction
        db 0a2h
ENDM

RD_TSC MACRO
        db 0fh
        db 031h
ENDM

        TSC equ 10h

RD_MSR MACRO
        db 0fh
        db 32h
ENDM

M_RD_MSR MACRO N
        mov ecx,N
        RD_MSR
ENDM

WR_MSR MACRO
        db 0fh
        db 30h
ENDM

M_WR_MSR MACRO N
        mov ecx,N
        WR_MSR
ENDM

include timer.asm
.data

        public _cpu_type
        public _v86_flag
        public _fpu_type
        public _vendor_id
        public _cpu_signature
        public _ext_features
        public _features_ecx
        public _features_edx
        public _features_ebx

        public _timer_count
        public _timer_scale

        public _cpu_name_string
        public _proc_cache_l1
        public _proc_cache_l2


        _cpu_type       db 0
        _v86_flag       db 0
        _fpu_type       db 0
        _vendor_id       db "------------",0
        _cpu_name_string db 49 dup (0)
        _cpu_signature  dd 0
        _ext_features   dd 0
        _features_ecx   dd 0
        _features_edx   dd 0
        _features_ebx   dd 0
        fp_status dw    0

        _proc_cache_l1  db 16 dup (0)
        _proc_cache_l2  db 16 dup (0)

        _timer_count    dd 0,0
        _timer_scale    dd 0,0

        begin_time      dw 0,0
	timer_ticks     equ 1000
        
        TIMER_TICK_LOW  equ 046Ch
        TIMER_TICK_HIGH equ 046Eh
 
.code
;
; comment this line for 32-bit segments
;
.8086
;
; uncomment this line for 32-bit segments
;
; .386
;*********************************************************************
public _CPU_is_8086
public _CPU_is_80286
public _CPU_is_80386
public _CPU_is_80486
public _get_CPU_ID
public _read_tsc
;*********************************************************************
public _get_fpu_type
_get_fpu_type proc
; This procedure determines the type of FPU in a system
; and sets the _fpu_type variable with the appropriate value.
; All registers are used by this procedure, none are preserved.
; Coprocessor check
; The algorithm is to determine whether the floating-point
; status and control words are present. If not, no
; coprocessor exists. If the status and control words can
; be saved, the correct coprocessor is then determined
; depending on the processor type. The Intel386 processor can
; work with either an Intel287 NDP or an Intel387 NDP.
; The infinity of the coprocessor must be checked to determine
; the correct coprocessor type.
        fninit                  ; reset FP status word
        mov fp_status, 5a5ah    ; initialize temp word to non-zero
        fnstsw fp_status        ; save FP status word
        mov ax, fp_status       ; check FP status word
        cmp al, 0               ; was correct status written
        mov _fpu_type, 0        ; no FPU present
        jne end_fpu_type
        check_control_word:
        fnstcw fp_status        ; save FP control word
        mov ax, fp_status       ; check FP control word
        and ax, 103fh           ; selected parts to examine
        cmp ax, 3fh             ; was control word correct
        mov _fpu_type, 0
        jne end_fpu_type        ; incorrect control word, no FPU
        mov _fpu_type, 1
; 80287/80387 check for the Intel386 processor
check_infinity:
        cmp _cpu_type, 3
        jne end_fpu_type
        fld1                    ; must use default control from FNINIT
        fldz                    ; form infinity
        fdiv                    ; 8087/Intel287 NDP say +inf = -inf
        fld st                  ; form negative infinity
        fchs                    ; Intel387 NDP says +inf <> -inf
        fcompp                  ; see if they are the same
        fstsw fp_status         ; look at status from FCOMPP
        mov ax, fp_status
        mov _fpu_type, 2        ; store Intel287 NDP for FPU type
        sahf                    ; see if infinities matched
        jz end_fpu_type         ; jump if 8087 or Intel287 is present
        mov _fpu_type, 3        ; store Intel387 NDP for FPU type
end_fpu_type:
        ret
_get_fpu_type endp
;-----------------------------------------------
; This procedure determines the type of processor in a system
; and sets the _cpu_type variable with the appropriate
; value. If the CPUID instruction is available, it is used
; to determine more specific details about the processor.
; All registers are used by this procedure, none are preserved.
; To avoid AC faults, the AM bit in CR0 must not be set.
; Intel 8086 processor check
; Bits 12-15 of the FLAGS register are always set on the
; 8086 processor.
;
; For 32-bit segments comment the following lines down to the next
; comment line that says "STOP"
;
_CPU_is_8086 proc
        pushf                   ; push original FLAGS
        pop ax                  ; get original FLAGS
        mov cx, ax              ; save original FLAGS
        and ax, 0fffh           ; clear bits 12-15 in FLAGS
        push ax                 ; save new FLAGS value on stack
        popf                    ; replace current FLAGS value
        pushf                   ; get new FLAGS
        pop ax                  ; store new FLAGS in AX
        and ax, 0f000h          ; if bits 12-15 are set, then
        cmp ax, 0f000h          ; processor is an 8086/8088
        mov _cpu_type, 0        ; turn on 8086/8088 flag
        jne ishigher86          ; go check for 80286
        push sp                 ; double check with push sp
        pop dx                  ; if value pushed was different
        cmp dx, sp              ; means it's really not an 8086
        jne is8086              ; jump if processor is 8086/8088
isUnknown:
        mov _cpu_type, 10h      ; indicate unknown processor
        mov ax,-1
        ret
is8086:
        mov ax,1
        ret
ishigher86:
        xor ax,ax
        ret
_CPU_is_8086 endp
;--------------------------------------------------------------------
; Intel 286 processor check
; Bits 12-15 of the FLAGS register are always clear on the
; Intel 286 processor in real-address mode.
.286P
_CPU_is_80286 proc
        smsw ax                 ; save machine status word
        and ax, 1               ; isolate PE bit of MSW
        mov _v86_flag, al       ; save PE bit to indicate V86
        or cx, 0f000h           ; try to set bits 12-15
        push cx                 ; save new FLAGS value on stack
        popf                    ; replace current FLAGS value
        pushf                   ; get new FLAGS
        pop ax                  ; store new FLAGS in AX
        and ax, 0f000h          ; if bits 12-15 are clear
        mov _cpu_type, 2        ; processor=80286, turn on 80286 flag
        jnz ishigher286         ; jump if processor is 80286
is286:
        mov ax,1
        ret
ishigher286:
        xor ax,ax
        ret
_CPU_is_80286 endp
;--------------------------------------------------------------------
; Intel386 processor check
; The AC bit, bit #18, is a new bit introduced in the EFLAGS
; register on the Intel486 processor to generate alignment
; faults.
; This bit cannot be set on the Intel386 processor.
.386
;
; "STOP"
;
; ; it is safe to use 386 instructions
_CPU_is_80386 proc
        pushfd                  ; push original EFLAGS
        pop eax                 ; get original EFLAGS
        mov ecx, eax            ; save original EFLAGS
        xor eax, 40000h         ; flip AC bit in EFLAGS
        push eax                ; save new EFLAGS value on stack
        popfd                   ; replace current EFLAGS value
        pushfd                  ; get new EFLAGS
        pop eax                 ; store new EFLAGS in EAX
        xor eax, ecx            ; can't toggle AC bit, processor=80386
        mov _cpu_type, 3        ; turn on 80386 processor flag
        jz is386                ; jump if 80386 processor
        push ecx
        popfd                   ; restore AC bit in EFLAGS first
ishigher386:
        xor ax,ax
        ret
is386:
        mov ax,1
        ret
_CPU_is_80386 endp
;--------------------------------------------------------------------
; Intel486 processor check
; Checking for ability to set/clear ID flag (Bit 21) in EFLAGS
; which indicates the presence of a processor with the CPUID
; instruction.
.486
_CPU_is_80486 proc
        mov _cpu_type, 4        ; turn on 80486 processor flag
        mov eax, ecx            ; get original EFLAGS
        xor eax, 200000h        ; flip ID bit in EFLAGS
        push eax                ; save new EFLAGS value on stack
        popfd                   ; replace current EFLAGS value
        pushfd                  ; get new EFLAGS
        pop eax                 ; store new EFLAGS in EAX
        xor eax, ecx            ; can't toggle ID bit,
        jne ishigher486         ; processor=80486
is486:
        mov ax,1
        ret
ishigher486:
        xor ax,ax
        ret
_CPU_is_80486 endp
;--------------------------------------------------------------------
; Execute CPUID instruction to not determine vendor, family,
; model, stepping and features. For the purpose of this
; code, only the initial set of CPUID information is saved.
_get_CPU_ID proc
        push ebx                ; save registers
        push esi
        push edi
        mov eax, 0              ; set up for CPUID instruction
        CPU_ID                  ; get and save vendor ID

        mov dword ptr _vendor_id, ebx
        mov dword ptr _vendor_id[+4], edx
        mov dword ptr _vendor_id[+8], ecx

        cmp eax, 1              ; make sure 1 is valid input for CPUID
        jl end_cpuid_type       ; if not, jump to end
        mov eax, 1
        CPU_ID                  ; get family/model/stepping/features
        mov _cpu_signature, eax
        mov _features_ebx, ebx
        mov _features_ecx, ecx
        mov _features_edx, edx
        shr eax, 8 ; isolate family
        and eax, 0fh
        mov _cpu_type, al       ; set _cpu_type with family

        mov     eax,080000000h      ; Check for support of extended functions.
        CPU_ID

        ; Check which extended functions can be called
        cmp     eax,080000001h      ; Extended Feature Bits
        jb      no_features         ; jump if not supported
        cmp     eax, 080000004h     ; CPU Name string
        jb      just_extfeat        ; jump if not supported
        cmp     eax, 080000005h     ; L1 Cache information
        jb      short just_name     ; jump if not supported
        cmp     eax, 080000006h     ; L2 Cache information
        jb      short just_L1       ; jump if not supported

        ; Query and save L2 cache information
        mov     eax,080000006h      ; L2 Cache Information
        CPU_ID                       ; Interpretation is CPU specific, but
                                    ; fetching is not.
        mov     DWORD PTR [_proc_cache_l2+0],eax
        mov     DWORD PTR [_proc_cache_l2+4],ebx
        mov     DWORD PTR [_proc_cache_l2+8],ecx
        mov     DWORD PTR [_proc_cache_l2+12],edx


just_L1:
        ; Query and save L1 cache informatin
        mov     eax,080000005h      ; L1 Cache Information
        CPU_ID                       ; Interpretation is CPU specific, but
                                    ; fetching is not.
        mov     DWORD PTR [_proc_cache_l1+0],eax
        mov     DWORD PTR [_proc_cache_l1+4],ebx
        mov     DWORD PTR [_proc_cache_l1+8],ecx
        mov     DWORD PTR [_proc_cache_l1+12],edx


just_name:
        ; Query and save the CPU name string
        mov     eax,080000002h
        CPU_ID
        mov     DWORD PTR [_cpu_name_string+0],eax
        mov     DWORD PTR [_cpu_name_string+4],ebx
        mov     DWORD PTR [_cpu_name_string+8],ecx
        mov     DWORD PTR [_cpu_name_string+12],edx
        mov     eax,080000003h
        CPU_ID
        mov     DWORD PTR [_cpu_name_string+16],eax
        mov     DWORD PTR [_cpu_name_string+20],ebx
        mov     DWORD PTR [_cpu_name_string+24],ecx
        mov     DWORD PTR [_cpu_name_string+28],edx
        mov     eax,080000004h
        CPU_ID
        mov     DWORD PTR [_cpu_name_string+32],eax
        mov     DWORD PTR [_cpu_name_string+36],ebx
        mov     DWORD PTR [_cpu_name_string+40],ecx
        mov     DWORD PTR [_cpu_name_string+44],edx

just_extfeat:
        ; Query and save the extended features bits
        mov     eax,080000001h      ; Select function 0x80000001
        CPU_ID
        mov     [_ext_features],edx  ; Store extended features bits

no_features:


end_cpuid_type:
        pop edi                 ; restore registers
        pop esi
        pop ebx
        ret
_get_CPU_ID endp
;--------------------------------------------------------------------
.586P
_read_tsc proc
	cli

       read_timer
       mov bx,ax
l1:
       read_timer
       cmp bx,ax
       je l1

       xor edx,edx
       xor eax,eax
       M_WR_MSR TSC

       mov word ptr begin_time, ax
lp:
       read_timer

       sub ax, word ptr begin_time
       cmp ax, timer_ticks
       jne lp

l2:
       read_timer
       cmp bx,ax
       je l2


       mov word ptr [_timer_scale], timer_ticks

       xor edx,edx
       xor eax,eax
       M_RD_MSR TSC
       mov [_timer_count+0],eax
       mov [_timer_count+4],edx

       sti

       ret
_read_tsc endp
end
