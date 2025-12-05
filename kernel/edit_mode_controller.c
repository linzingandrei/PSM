#include "edit_mode_controller.h"


PROCESS editModeContext;
SCREEN gEditModeBuffer[MAX_OFFSET * 2];
// SCREEN gEditModeScrollBuffer[MAX_OFFSET * 3];

void InitEditMode() {
    for (int i = 0; i < MAX_OFFSET * 2; i++) {
        gEditModeBuffer[i].c = ' ';
        gEditModeBuffer[i].color = COLOR_WHITE;
    }

    editModeContext.processBuffer = (gEditModeBuffer + MAX_OFFSET / 2);
    editModeContext.positionInProcess = 0;
    editModeContext.endPositionInProcess = 0; 
    editModeContext.processName = "EDIT\0";

    processArray[1] = &editModeContext;
}

int EditModeCommands(char* command) {
    // if (cl_strcmp(command, "clear") == 0) {
    //     ClearScreen();
    //     PutChar('>', global_pos, COLOR_WHITE);
    //     global_pos += 1;
    //     PutChar(' ', global_pos, COLOR_WHITE);
    //     global_pos += 1;
    //     return 0;
    // }
    // else if (cl_strcmp(command, "cls") == 0) {
    //     ClearScreen();
    //     PutChar('>', global_pos, COLOR_WHITE);
    //     global_pos += 1;
    //     PutChar(' ', global_pos, COLOR_WHITE);
    //     global_pos += 1;
    //     return 0;
    // }
    // else if (cl_strcmp(command, "edit") == 0) {
    //     SwitchContext("CONSOLE");
    //     return 0;
    // }
    // else {
    //     return 1;
    // }
    return 0;
}

void HandleScreen() {
    if (currentProcess->positionInProcess == 2000) {
        SCREEN* newStart = gEditModeBuffer + 80;
        editModeContext.processBuffer = newStart;
        gVideo = newStart;
    }
}