#include "idt.h"


struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void set_idt_gate(int n, QWORD handler) {
    idt[n].low_offset = (WORD) (handler & 0xFFFF);
    idt[n].mid_offset = (WORD) ((handler >> 16) & 0xFFFF);
    idt[n].high_offset = (DWORD) ((handler >> 32) & 0xFFFFFFFF);
    idt[n].segment_selector = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].reserved = 0;
    idt[n].flags = 0x8E;
}

void idt_install() {
    __magic();
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;
    idtp.base = (QWORD) &idt;
    
    __asm__ __volatile__("lidt (%0)" : : "r" (&idtp));
    __asm__ __volatile__("sti");
}