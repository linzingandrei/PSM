#include "edit_mode_controller.h"


PROCESS editModeContext;
SCREEN gEditModeBuffer[MAX_OFFSET];

void InitEditMode() {
    for (int i = 0; i < MAX_OFFSET; i++) {
        gEditModeBuffer[i].c = ' ';
        gEditModeBuffer[i].color = COLOR_WHITE;
    }

    editModeContext.processBuffer = gEditModeBuffer;
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

}