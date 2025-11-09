#pragma once
#include "scancode.h"
#include "screen.h"
#include "main.h"
#include "isr.h"


void InitKeyboard();
void KeyboardHandler(struct registers_t* regs);