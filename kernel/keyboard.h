#pragma once
#include "scancode.h"
#include "screen.h"
#include "main.h"
#include "isr.h"
#include "string.h"
#include "console_controller.h"
#include "edit_mode_controller.h"


#define MAX_COMMAND_SIZE 255


void InitKeyboard();
void KeyboardHandler(struct registers_t* regs);