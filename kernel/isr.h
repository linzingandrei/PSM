#pragma once
#include "idt.h"
#include "main.h"
#include "screen.h"
#include "pio.h"

extern void isr_stub_0();
extern void isr_stub_1();
extern void isr_stub_2();
extern void isr_stub_3();
extern void isr_stub_4();
extern void isr_stub_5();
extern void isr_stub_6();
extern void isr_stub_7();
extern void isr_stub_8();
extern void isr_stub_9();
extern void isr_stub_10();
extern void isr_stub_11();
extern void isr_stub_12();
extern void isr_stub_13();
extern void isr_stub_14();
extern void isr_stub_15();
extern void isr_stub_16();
extern void isr_stub_17();
extern void isr_stub_18();
extern void isr_stub_19();
extern void isr_stub_20();
extern void isr_stub_21();
extern void isr_stub_22();
extern void isr_stub_23();
extern void isr_stub_24();
extern void isr_stub_25();
extern void isr_stub_26();
extern void isr_stub_27();
extern void isr_stub_28();
extern void isr_stub_29();
extern void isr_stub_30();
extern void isr_stub_31();

extern void isr_stub_32();
extern void isr_stub_33();
extern void isr_stub_34();
extern void isr_stub_35();
extern void isr_stub_36();
extern void isr_stub_37();
extern void isr_stub_38();
extern void isr_stub_39();
extern void isr_stub_40();
extern void isr_stub_41();
extern void isr_stub_42();
extern void isr_stub_43();
extern void isr_stub_44();
extern void isr_stub_45();
extern void isr_stub_46();
extern void isr_stub_47();

struct registers_t {
    QWORD r15, r14, r13, r12, rbp, rbx;
    QWORD r11, r10, r9, r8, rax, rcx, rdx, rsi, rdi;
    QWORD int_no, err_code;
    QWORD rip, cs, rflags, rsp, ss;
} __attribute__((packed));;

void isr_install();
void isr_handler(struct registers_t *regs);