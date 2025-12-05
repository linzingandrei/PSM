#include "console_controller.h"
#include "timer.h"


PROCESS consoleContext;
SCREEN gConsoleBuffer[MAX_OFFSET];
// SCREEN gConsoleScrollBuffer[MAX_OFFSET * 3];

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
    else if(cl_strcmp(command, "dmpmem") == 0) {
        BYTE buffer[1024] = { 0 };
        BYTE buffer2[1024] = { 0 };

        AtaPioRead28(0, 2, buffer);

        DWORD nr = 0;
        DWORD itemsPerRow = 5;
        DWORD address = 0;
        for (int i = 380; i < 512; i++, nr += 1, address += 1) {
            // LogSerialAndScreen("%d", i + 250);
            if (nr % itemsPerRow == 0) {
                LogSerialAndScreen("0x%x ", address);
            }

            if (nr % itemsPerRow == 0 && nr > 0)  {
                for (int j = 0; j < itemsPerRow; j++) {
                    LogSerialAndScreen("%c ", (BYTE)buffer2[j]);
                }

                for (int j = 0; j < itemsPerRow; j++) {
                    buffer2[j] = '\x00';
                }

                Newline();
            }

            buffer2[i % itemsPerRow] = buffer[i];
            LogSerialAndScreen("%x ", (BYTE)buffer[i]);
        }

        Newline();

        return 0;
    }
    else {
        return 1;
    }
}