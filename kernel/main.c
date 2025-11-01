#include "main.h"
#include "screen.h"
#include "logging.h"
#include "isr.h"


void _KernelMain()
{
    // __magic();    // break into BOCHS
    
    // __enableSSE();  // only for demo; in the future will be called from __init.asm


    idt_install();
    isr_install();

    // __magic();
    ClearScreen();

    // __magic();
    InitLogging();

    // __magic();
    Log("Logging initialized!");

    // __magic();
    HelloBoot();

    __magic();


    // DIVISION BY ZERO
    // int a = 3 / 0;

    // INVALID OPCODE
    // __asm__ __volatile__("ud2");

    // Double fault????
    // int* p = 0;
    // *p = 42;

    // Page fault
    volatile int *p = (int*)0xCAFEBABE;
    *p = 1;

    // extern void func1();

    // func1();
    __magic();

    asm("hlt");

    // __magic(); 

    // TODO!!! PIC programming; see http://www.osdever.net/tutorials/view/programming-the-pic
    // TODO!!! define interrupt routines and dump trap frame
    
    // TODO!!! Timer programming

    // TODO!!! Keyboard programming

    // TODO!!! Implement a simple console

    // TODO!!! read disk sectors using PIO mode ATA

    // TODO!!! Memory management: virtual, physical and heap memory allocators
}
