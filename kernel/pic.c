#include "pic.h"
#include "main.h"


void MapPIC() {
    // __magic();
// Send ICW 1 - Begin initialization -------------------------
 
	// Setup to initialize the primary PIC. Send ICW 1
 
    __outbyte(PIC_1_CTRL, ICW_1);
 
// Send ICW 2 - Map IRQ base interrupt numbers ---------------
 
	// Remember that we have 2 PICs. Because we are cascading with this second PIC, send ICW 1 to second PIC command register
 
    __outbyte(PIC_2_CTRL, ICW_1);
 
	// send ICW 2 to primary PIC
 
    __outbyte(PIC_1_DATA, IRQ_0);
 
	// send ICW 2 to secondary controller
 
    __outbyte(PIC_2_DATA, IRQ_8);
 
// Send ICW 3 - Set the IR line to connect both PICs ---------
 
	// Send ICW 3 to primary PIC
 
    __outbyte(PIC_1_DATA, 0x4);			// 0x04 => 0100, second bit (IR line 2)
	                                // write to data register of primary PIC
 
	// Send ICW 3 to secondary PIC
 
    __outbyte(PIC_2_DATA, 0x2);          // 010=> IR line 2
	                                // write to data register of secondary PIC
 
// Send ICW 4 - Set x86 mode --------------------------------
 
	// bit 0 enables 80x86 mode
	// send ICW 4 to both primary and secondary PICs

    __outbyte(PIC_1_DATA, 0x1);
    __outbyte(PIC_2_DATA, 0x1);
 
// All done. Null out the data registers
 
    __outbyte(PIC_1_DATA, 0x0);
    __outbyte(PIC_2_DATA, 0x0);
}

void MaskPIC() {
    // Mask all except keyboard and timer, both of which are on the master, that's why the slave has everything masked
    __outbyte(0x21, 0x00);
    __outbyte(0xA1, 0x00);
}