#include "keyboard.h"

int pos;
void InitKeyboard() {
    __outbyte(0x64, 0x75);
    pos = 0;
}

void KeyboardHandler(struct registers_t* regs) {
    WORD scancode = __inbyte(0x60);

    if (scancode < 128) {
        BYTE chr = _kkybrd_scancode_std[scancode];
        PutChar(chr, pos);
        pos += 1;
    }
}