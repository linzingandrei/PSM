#include "console_controller.h"


PROCESS consoleContext;
SCREEN gConsoleBuffer[MAX_OFFSET];

void InitConsole() {
    for (int i = 0; i < MAX_OFFSET; i++) {
        gConsoleBuffer[i].c = ' ';
        gConsoleBuffer[i].color = COLOR_WHITE;
    }

    consoleContext.processBuffer = gConsoleBuffer;
    consoleContext.positionInProcess = 0;
    consoleContext.endPositionInProcess = 0; 
    consoleContext.processName = "CONSOLE\0";

    processArray[0] = &consoleContext;
}

int ConsoleCommands(char* command) {
    if (cl_strcmp(command, "clear") == 0) {
        ClearScreen();
        PutChar('>', global_pos, COLOR_WHITE);
        global_pos += 1;
        PutChar(' ', global_pos, COLOR_WHITE);
        global_pos += 1;
        return 0;
    }
    else if (cl_strcmp(command, "cls") == 0) {
        ClearScreen();
        PutChar('>', global_pos, COLOR_WHITE);
        global_pos += 1;
        PutChar(' ', global_pos, COLOR_WHITE);
        global_pos += 1;
        return 0;
    }
    else if (cl_strcmp(command, "edit") == 0) {
        SwitchContext("EDIT");
        return 0;
    }
    else {
        return 1;
    }
}