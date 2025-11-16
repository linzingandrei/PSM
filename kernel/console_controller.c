#include "console_controller.h"
#include "timer.h"


PROCESS consoleContext;
SCREEN gConsoleBuffer[MAX_OFFSET];

COMMAND_HISTORY commandHistoryInstance;
COMMAND_HISTORY* commandHistory;

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

    commandHistory = &commandHistoryInstance;

    commandHistory->startingIndex = 9;
    commandHistory->numberOfCommands = 0;

    for (int i = 0; i < 10; i++) {
        commandHistory->command[i][0] = '\0';
    }
}

int ConsoleCommands(char* command) {

    for (int i = 0; i < 9; i++) {
        cl_strcpy(commandHistory->command[i], commandHistory->command[i + 1]);
    }
    cl_strcpy(commandHistory->command[9], command);
    commandHistory->numberOfCommands += 1;

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
    else if (cl_strcmp(command, "time") == 0) {
        QWORD clock_ticks_since_boot = read_tsc();
        char clock_ticks[32];
        kitoa(&clock_ticks_since_boot, TRUE, clock_ticks, 10, TRUE); 
        // Newline();
        ScreenDisplay(clock_ticks, COLOR_WHITE);
        Newline();
        ScreenDisplay("> ", COLOR_WHITE);
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