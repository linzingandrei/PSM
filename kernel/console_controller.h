#pragma once
#include "string.h"
#include "screen.h"
#include "process_manager.h"


extern PROCESS consoleContext;

void InitConsole();
int ConsoleCommands(char* command);
void HandleScreen();