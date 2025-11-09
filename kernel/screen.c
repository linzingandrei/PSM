#include "screen.h"

static PSCREEN gVideo = (PSCREEN)(0x000B8000);

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

    len = 0;
    while (buffer[len] != 0) {
        len += 1;
    }

    int aux;
    for (i = 0, aux = 0; i < MAX_OFFSET && aux < len; i++, aux++) {
        if (buffer[aux] == '\n') {
            for (; i % MAX_COLUMNS < MAX_COLUMNS - 1; i++) {
                gVideo[i].color = COLOR_BLACK;
                gVideo[i].c = ' ';
            }
        }
        else {
            gVideo[i].color = COLOR_BB_RF;
            gVideo[i].c = buffer[aux]; 
        }
        CursorPosition(i);
    }
}

void ScreenDisplayTimer(char* buffer, BYTE color) {
    int len;

    len = 0;
    while (buffer[len] != 0) {
        len += 1;
    }

    for (int i = MAX_COLUMNS - len - 1, j = 0; i < MAX_COLUMNS && j < len; i++, j++) {
        gVideo[i].color = 10;
        gVideo[i].c = buffer[j];
    }
}

void ClearScreen()
{
    int i;

    for (i = 0; i < MAX_OFFSET; i++)
    {
        gVideo[i].color = 10;
        gVideo[i].c = ' ';
    }

    CursorMove(0, 0);
}

void PutChar(char C, int Pos) {
    gVideo[Pos].color = 10;
    gVideo[Pos].c = C;

    CursorPosition(Pos + 1);
}

