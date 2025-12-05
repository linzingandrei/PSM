#pragma once
#include "string.h"
#include "screen.h"
#include "process_manager.h"
#include "pio.h"


extern PROCESS consoleContext;

typedef struct _COMMAND_HISTORY {
    char command[10][100];
    BYTE startingIndex;
    BYTE numberOfCommands;
} COMMAND_HISTORY;

extern COMMAND_HISTORY commandHistoryInstance;
extern COMMAND_HISTORY* commandHistory;

void InitConsole();
int ConsoleCommands(char* command);
void HandleScreen();