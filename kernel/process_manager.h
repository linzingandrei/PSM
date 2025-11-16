#pragma once
#include "string.h"
#include "screen.h"


#pragma pack(push)
#pragma pack(1)
typedef struct _PROCESS
{
    SCREEN* processBuffer;
    int positionInProcess;
    int endPositionInProcess;
    char* processName;
}PROCESS;
#pragma pack(pop)

extern PROCESS* currentProcess;
extern PROCESS* processArray[10];

void InitProcesses();
void SwitchContext(char* processToSwitchToName);