#include "main.h"
#include "screen.h"
#include "logging.h"


void _KernelMain()
{
    // __magic();    // break into BOCHS
    
    // __enableSSE();  // only for demo; in the future will be called from __init.asm



    // __magic();
    ClearScreen();

    // __magic();
    InitLogging();

    // __magic();
    Log("Logging initialized!");

    // __magic();
    HelloBoot();

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
