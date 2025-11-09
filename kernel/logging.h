#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "main.h"
#include "screen.h"

#define LOG_BUF_MAX_SIZE 512
#define COLOR_BLACK 30

void InitLogging();

void Log(char * Message);
void LogSerialAndScreen(char* FormatBuffer, ...);
void LogScreen(char* Format, ...);


#endif // _LOGGING_H_