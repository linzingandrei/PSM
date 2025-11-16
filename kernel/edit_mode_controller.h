#pragma once
#include "string.h"
#include "screen.h"
#include "process_manager.h"


extern PROCESS editModeContext;

void InitEditMode();
int EditModeCommands(char* command);
void HandleScreen();