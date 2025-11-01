
;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

;// Macros

[BITS 64]
segment .text

[extern isr_handler]

%macro isr_err_stub 1
global isr_stub_%+%1
isr_stub_%+%1:
    push 1
    push %1
    jmp exception_handler
%endmacro

%macro isr_noerr_stub 1
global isr_stub_%+%1
isr_stub_%+%1:
    push 0
    push %1
    jmp exception_handler
%endmacro

%macro push_all_registers 0
    push rdi
    push rsi
    push rdx
    push rcx
    push rax
    push r8
    push r9
    push r10
    push r11
    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro pop_all_registers 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
    pop r11
    pop r10
    pop r9
    pop r8
    pop rax
    pop rcx
    pop rdx
    pop rsi
    pop rdi
%endmacro

exception_handler:
    push_all_registers

    mov rcx, rsp
    call isr_handler 

    pop_all_registers

    add rsp, 0x10
    iretq

;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

isr_noerr_stub 0
isr_noerr_stub 1
isr_noerr_stub 2
isr_noerr_stub 3
isr_noerr_stub 4
isr_noerr_stub 5
isr_noerr_stub 6
isr_noerr_stub 7

isr_err_stub 8

isr_noerr_stub 9

isr_err_stub 10
isr_err_stub 11
isr_err_stub 12
isr_err_stub 13
isr_err_stub 14

isr_noerr_stub 15
isr_noerr_stub 16

isr_noerr_stub 17

isr_noerr_stub 18
isr_noerr_stub 19
isr_noerr_stub 20

isr_err_stub 21

isr_noerr_stub 22
isr_noerr_stub 23
isr_noerr_stub 24
isr_noerr_stub 25
isr_noerr_stub 26
isr_noerr_stub 27
isr_noerr_stub 28
isr_noerr_stub 29
isr_noerr_stub 30
isr_noerr_stub 31

;///////////////////////////////////////////////////////////

segment .data

global isr_stub_0
global isr_stub_1
global isr_stub_2
global isr_stub_3
global isr_stub_4
global isr_stub_5
global isr_stub_6
global isr_stub_7
global isr_stub_8
global isr_stub_9
global isr_stub_10
global isr_stub_11
global isr_stub_12
global isr_stub_13
global isr_stub_14
global isr_stub_15
global isr_stub_16
global isr_stub_17
global isr_stub_18
global isr_stub_19
global isr_stub_20
global isr_stub_21
global isr_stub_22
global isr_stub_23
global isr_stub_24
global isr_stub_25
global isr_stub_26
global isr_stub_27
global isr_stub_28
global isr_stub_29
global isr_stub_30
global isr_stub_31