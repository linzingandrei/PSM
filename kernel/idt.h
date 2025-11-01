#include "main.h"
#include "screen.h"

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

struct idt_entry {
    WORD low_offset;
    WORD segment_selector;
    BYTE always0;
    BYTE flags;
    WORD mid_offset;
    DWORD high_offset;
    DWORD reserved;
} __attribute__((packed));

struct idt_ptr {
    WORD limit;
    QWORD base; 
} __attribute__((packed));

void set_idt_gate(int n, QWORD handler);
void idt_install();