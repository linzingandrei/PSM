#include "process_manager.h"


PROCESS* currentProcess; 
PROCESS* processArray[10];

void InitProcesses() {
    currentProcess = processArray[0]; 
}

void SaveStates() {
    for (int i = 0; i < 2000; i++) {
        currentProcess->processBuffer[i] = gVideo[i];
    }
    currentProcess->positionInProcess = global_pos;
    ClearScreen();
}

void SwitchContext(char* processToSwitchToName) {
    SaveStates();

    if (cl_strcmp(processToSwitchToName, "CONSOLE") == 0) {
        currentProcess = processArray[0];
        Log("CONSOLE!");
    }
    else if (cl_strcmp(processToSwitchToName, "EDIT") == 0) {
        currentProcess = processArray[1];
        Log("EDIT!");
    }

    if (cl_strcmp(currentProcess->processName, "CONSOLE") == 0) {
        global_pos = currentProcess->positionInProcess;

        for (int i = 0; i < 2000; i++) {
            gVideo[i] = currentProcess->processBuffer[i];
        }
        
        CursorPosition(global_pos);
    }
    else if (cl_strcmp(currentProcess->processName, "EDIT") == 0) {
        global_pos = currentProcess->positionInProcess;

        for (int i = 0; i < 2000; i++) {
            gVideo[i] = currentProcess->processBuffer[i];
        }

        CursorPosition(global_pos);
    }
}