#include "isr.h"
#include "logging.h"
#include "timer.h"
#include "keyboard.h"


void isr_install() {
    // Software interrupts
    set_idt_gate(0, (QWORD)(isr_stub_0));
    set_idt_gate(1, (QWORD)(isr_stub_1));
    set_idt_gate(2, (QWORD)(isr_stub_2));
    set_idt_gate(3, (QWORD)(isr_stub_3));
    set_idt_gate(4, (QWORD)(isr_stub_4));
    set_idt_gate(5, (QWORD)(isr_stub_5));
    set_idt_gate(6, (QWORD)(isr_stub_6));
    set_idt_gate(7, (QWORD)(isr_stub_7));
    set_idt_gate(8, (QWORD)(isr_stub_8));
    set_idt_gate(9, (QWORD)(isr_stub_9));
    set_idt_gate(10, (QWORD)(isr_stub_10));
    set_idt_gate(11, (QWORD)(isr_stub_11));
    set_idt_gate(12, (QWORD)(isr_stub_12));
    set_idt_gate(13, (QWORD)(isr_stub_13));
    set_idt_gate(14, (QWORD)(isr_stub_14));
    set_idt_gate(15, (QWORD)(isr_stub_15));
    set_idt_gate(16, (QWORD)(isr_stub_16));
    set_idt_gate(17, (QWORD)(isr_stub_17));
    set_idt_gate(18, (QWORD)(isr_stub_18));
    set_idt_gate(19, (QWORD)(isr_stub_19));
    set_idt_gate(20, (QWORD)(isr_stub_20));
    set_idt_gate(21, (QWORD)(isr_stub_21));
    set_idt_gate(22, (QWORD)(isr_stub_22));
    set_idt_gate(23, (QWORD)(isr_stub_23));
    set_idt_gate(24, (QWORD)(isr_stub_24));
    set_idt_gate(25, (QWORD)(isr_stub_25));
    set_idt_gate(26, (QWORD)(isr_stub_26));
    set_idt_gate(27, (QWORD)(isr_stub_27));
    set_idt_gate(28, (QWORD)(isr_stub_28));
    set_idt_gate(29, (QWORD)(isr_stub_29));
    set_idt_gate(30, (QWORD)(isr_stub_30));
    set_idt_gate(31, (QWORD)(isr_stub_31));

    // Hardware interrupts
    set_idt_gate(32, (QWORD)(isr_stub_32));
    set_idt_gate(33, (QWORD)(isr_stub_33));
    set_idt_gate(34, (QWORD)(isr_stub_34));
    set_idt_gate(35, (QWORD)(isr_stub_35));
    set_idt_gate(36, (QWORD)(isr_stub_36));
    set_idt_gate(37, (QWORD)(isr_stub_37));
    set_idt_gate(38, (QWORD)(isr_stub_38));
    set_idt_gate(39, (QWORD)(isr_stub_39));
    set_idt_gate(40, (QWORD)(isr_stub_40));
    set_idt_gate(41, (QWORD)(isr_stub_41));
    set_idt_gate(42, (QWORD)(isr_stub_42));
    set_idt_gate(43, (QWORD)(isr_stub_43));
    set_idt_gate(44, (QWORD)(isr_stub_44));
    set_idt_gate(45, (QWORD)(isr_stub_45));
    set_idt_gate(46, (QWORD)(isr_stub_46));
    set_idt_gate(47, (QWORD)(isr_stub_47));
}

char *exception_messages[32] = {
    "Divison By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out Of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(struct registers_t* regs) {
    // __magic();

    if (regs->int_no < 32) {
        ClearScreen();

        LogSerialAndScreen("ERROR: %s(%d)\nError code: %d\nRax: 0x%X\nRbx: 0x%X\nRcx: 0x%x\nRdx: 0x%X\nRdi: 0x%X\nRsi: 0x%X\nRbp: 0x%X\nRsp: 0x%X\nRip: 0x%X\nR8: 0x%X\nR9: 0x%X\nR10: 0x%X\nR11: 0x%X\nR12: 0x%X\nR13: 0x%X\nR14:0x%X\nR15:0x%X\n\nCS: 0x%X\nSS: 0x%X\n\nRFLAGS: 0x%X", 
            exception_messages[regs->int_no], regs->int_no,
            regs->err_code,
            regs->rax, regs->rbx, regs->rcx, regs->rdx, regs->rdi, regs->rsi, regs->rbp, regs->rsp, regs->rip, regs->r8, regs->r9, regs->r10, regs->r11, regs->r12, regs->r13, regs->r14, regs->r15,
            regs->cs, regs->ss,
            regs->rflags
        );
        // ScreenDisplay(exception_messages[regs->int_no]);
        // ScreenDisplay('\n');
        // ScreenDisplay(regs->rax);

        for (;;);
    }
    else if (regs->int_no == 32) {
        TimerHandler(regs);
        __outbyte(0x20, 0x20);
        return;
    }
    else if (regs->int_no == 33) {
        KeyboardHandler(regs);
        __outbyte(0x20, 0x20);
        return;
    }
}