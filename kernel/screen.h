#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "main.h"
#include "logging.h"
#include "string.h"
// #include "process_manager.h"

#define MAX_LINES       25
#define MAX_COLUMNS     80
#define MAX_OFFSET      2000 //25 lines * 80 chars
#define COLOR_BLACK     0x00
#define COLOR_BB_RF     0x04
#define COLOR_WHITE     0x0F
#define FORCE_NEWLINE   -1


#pragma pack(push)
#pragma pack(1)
typedef struct _SCREEN
{
    char c;
    BYTE color;
}SCREEN, *PSCREEN;
#pragma pack(pop)

extern PSCREEN gVideo;

// when implementing processes I guess this will go in a struct for each process
extern int global_pos;
// extern int aux_global_pos_buffer;
// extern int aux_global_pos_console;
// extern char* context;
// from 3500-6999 the colors of characters from 0-3499

void InitBuffersAndContexts();
void CursorMove(int row, int col);
void CursorPosition(int pos);
void HelloBoot();
void SetColor(BYTE Color);
void ClearScreen();
void PutChar(char C, int Pos, BYTE color);
void PutString(char* String, int Pos);
void PutStringLine(char* String, int Line);
void ScreenDisplay(char* buffer, BYTE color);
void ScreenDisplayTimer(char*buffer, BYTE color);
void Newline();
void Backspace();


#endif // _SCREEN_H_