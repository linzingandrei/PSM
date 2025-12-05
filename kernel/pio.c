#include "pio.h"


void insw(WORD port, void *addr, DWORD count) {
    asm volatile ("rep insw" : "+D"(addr), "+c"(count) : "d"(port) : "memory");
}

void outsw(WORD port, void *addr, DWORD count) {
    asm volatile ("rep outsw" : "+S"(addr), "+c"(count) : "d"(port));
}

/*
An example of a 28 bit LBA PIO mode read on the Primary bus:
1. Send 0xE0 for the "master" or 0xF0 for the "slave", ORed with the highest 4 bits of the LBA to port 0x1F6: outb(0x1F6, 0xE0 | (slavebit << 4) | ((LBA >> 24) & 0x0F))
2. Send a NULL byte to port 0x1F1, if you like (it is ignored and wastes lots of CPU time): outb(0x1F1, 0x00)
3. Send the sectorcount to port 0x1F2: outb(0x1F2, (unsigned char) count)
4. Send the low 8 bits of the LBA to port 0x1F3: outb(0x1F3, (unsigned char) LBA))
5. Send the next 8 bits of the LBA to port 0x1F4: outb(0x1F4, (unsigned char)(LBA >> 8))
6. Send the next 8 bits of the LBA to port 0x1F5: outb(0x1F5, (unsigned char)(LBA >> 16))
7. Send the "READ SECTORS" command (0x20) to port 0x1F7: outb(0x1F7, 0x20)
8. Wait for an IRQ or poll.
9. Transfer 256 16-bit values, a uint16_t at a time, into your buffer from I/O port 0x1F0. (In assembler, REP INSW works well for this.)
10. Then loop back to waiting for the next IRQ (or poll again -- see next note) for each successive sector.
*/
void AtaPioRead28(DWORD LBA, BYTE sector_count, BYTE *target) {
    Log("Start Read");

    __outbyte(IO_BASE + 6, 0xE0 | ((LBA >> 24) & 0x0F));

    __outbyte(IO_BASE + 2, sector_count);
    __outbyte(IO_BASE + 3, LBA & 0xFF); 
    __outbyte(IO_BASE + 4, (LBA >> 8) & 0xFF);
    __outbyte(IO_BASE + 5, (LBA >> 16) & 0xFF);

    __outbyte(IO_BASE + 7, 0x20);

    for (BYTE i = 0; i < sector_count; i++) {
        BYTE status;

        do {
            status = __inbyte(IO_BASE + 7);
        } while ((status & 0x80) || !(status & 0x08));

        if (status & 0x01) {
            Log("ATA read error");
            return;
        }
        if (status & 0x20) {
            Log("ATA device fault");
            return;
        }

        insw(IO_BASE + 0, target, 256);
        target += 512;
    }

    Log("Read complete");
}

/*
To write sectors in 28 bit PIO mode, send command "WRITE SECTORS" (0x30) to the Command port. Do not use REP OUTSW to transfer data. There must be a tiny delay between each OUTSW output uint16_t. A jmp $+2 size of delay. Make sure to do a Cache Flush (ATA command 0xE7) after each write command completes.
*/
// void ata_pio_write28(DWORD LBA, BYTE sector_count, BYTE *target) {
//     __outbyte(0x1F6, 0xE0 | ((LBA >> 24) & 0x0F));
//     __outbyte(0x1F1, 0x00);
//     __outbyte(0x1F2, sector_count);
//     __outbyte(0x1F3, LBA & 0xFF);
//     __outbyte(0x1F4, (LBA >> 8) & 0xFF);
//     __outbyte(0x1F5, (LBA >> 16) & 0xFF);
//     __outbyte(0x1F7, 0x30);

//     for (BYTE i = 0; i < sector_count; i++) {
//         while (1) {
//             BYTE status = __inbyte(0x1F7);
//             if (status & (1 << 3)) {
//                 break;
//             }
//         }
//         outsw(0x1F0, (void *)target, 256);
//         target += 256;
//     }

//     __outbyte(0x1F7, 0xE7);
//     while (__inbyte(0x1F7) & (1 << 7)) {}
// }