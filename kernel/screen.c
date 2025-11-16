#include "screen.h"


PSCREEN gVideo = (PSCREEN)(0x000B8000);
int global_pos = 0;
// static PSCREEN gBuffer = (PSCREEN)(0x50000);

void CursorMove(int row, int col)
{
    unsigned short location = (row * MAX_COLUMNS) + col;       /* Short is a 16bit type , the formula is used here*/

    //Cursor Low port
    __outbyte(0x3D4, 0x0F);                                    //Sending the cursor low byte to the VGA Controller
    __outbyte(0x3D5, (unsigned char)(location & 0xFF));

    //Cursor High port
    __outbyte(0x3D4, 0x0E);                                    //Sending the cursor high byte to the VGA Controller
    __outbyte(0x3D5, (unsigned char)((location >> 8) & 0xFF)); //Char is a 8bit type
}

void CursorPosition(int pos)
{
    int row, col;

    if (pos > MAX_OFFSET)
    {
        pos = pos % MAX_OFFSET;
    }

    row = pos / MAX_COLUMNS;
    col = pos % MAX_COLUMNS;

    CursorMove(row, col);
}

// void Screen() {
//     global_pos = 
// }

void HelloBoot()
{
    int i, len;
	char boot[] = "Hell0 Boot! Greetings from C...";

	len = 0;
	while (boot[len] != 0)
	{
		len++;
	}

	for (i = 0; (i < len) && (i < MAX_OFFSET); i++)
	{
		gVideo[i].color = 10;
		gVideo[i].c = boot[i];
	}
    CursorPosition(i);
}

void ScreenDisplay(char* buffer, BYTE color) {
    int i, len;
    int start = global_pos;

    len = 0;
    while (buffer[len] != 0) {
        len += 1;
    }

    int aux;
    for (i = start, aux = 0; i < MAX_OFFSET && aux < len; i++, aux++) {
        PutChar(buffer[aux], i, COLOR_WHITE);
        global_pos = i + 1;
        // CursorPosition(i);
    }
}

void ScreenDisplayTimer(char* buffer, BYTE color) {
    int len;

    len = 0;
    while (buffer[len] != 0) {
        len += 1;
    }

    for (int i = MAX_COLUMNS * 25 - len - 1, j = 0; i < MAX_COLUMNS * 25 && j < len; i++, j++) {
        gVideo[i].color = 10;
        gVideo[i].c = buffer[j];
    }
}

void ClearScreen()
{
    int i;
    global_pos = 0;

    for (i = 0; i < MAX_OFFSET; i++)
    {
        gVideo[i].color = COLOR_WHITE;
        gVideo[i].c = ' ';
    }

    CursorMove(0, 0);
}

void PutChar(char C, int Pos, BYTE color) {
    gVideo[Pos].color = color;
    gVideo[Pos].c = C;

    CursorPosition(Pos + 1);
}

void Newline() {
    global_pos = (global_pos / MAX_COLUMNS + 1) * MAX_COLUMNS;
    CursorPosition(global_pos);
}

void Backspace() {
    if (global_pos > 0) {
        if (global_pos >= 2 && gVideo[global_pos - 2].c != '>') {
            global_pos -= 1;

            gVideo[global_pos].color = COLOR_WHITE;
            gVideo[global_pos].c = ' ';

            CursorPosition(global_pos);
        }
    }
}