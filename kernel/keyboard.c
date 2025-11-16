#include "keyboard.h"

char text_buffer[MAX_COMMAND_SIZE];
int shift_pressed = 0;
void InitKeyboard() {
    __outbyte(0x64, 0x75);
    ScreenDisplay("> ", COLOR_WHITE);

    for (int i = 0; i < MAX_COMMAND_SIZE; i++) {
        text_buffer[i] = '\x00';
    }
    shift_pressed = 0;
}

void KeyboardHandler(struct registers_t* regs) {
    WORD scancode = __inbyte(0x60);

    int released;
    if ((scancode & 0x80) == 0x80) {
        released = 1;
    }
    else {
        released = 0;
    }

    scancode &= 0x7F;

    if (scancode < 128) {
        if (_kkybrd_scancode_std[scancode] == KEY_LSHIFT || _kkybrd_scancode_std[scancode] == KEY_RSHIFT) {
            shift_pressed = !released;
            return;
        }

        if (released) return;
        if (_kkybrd_scancode_ext[scancode] == KEY_KP_ENTER) {
            // Log("Newline function got called");
            // if (released) return;
            Newline();

            if (cl_strcmp(currentProcess->processName, "CONSOLE") == 0) {
                if (cl_strlen(text_buffer) > 0) {
                    int status = ConsoleCommands(text_buffer);

                    if (status == 1) {
                        ScreenDisplay("Command now known!", COLOR_WHITE);
                        Newline();
                        ScreenDisplay("> ", COLOR_WHITE);
                    }
                }
                else {
                    ScreenDisplay("> ", COLOR_WHITE);
                }

                for (int i = cl_strlen(text_buffer) - 1; i >= 0; i--) {
                    text_buffer[i] = '\x00';
                }
            }
        }
        else if (_kkybrd_scancode_std[scancode] == KEY_BACKSPACE) {
            Backspace();
        }
        else if (_kkybrd_scancode_std[scancode] == KEY_ESCAPE && cl_strcmp(currentProcess->processName, "EDIT") == 0) {
            SwitchContext("CONSOLE");

            ScreenDisplay("> ", COLOR_WHITE);
        }
        else if (_kkybrd_scancode_ext[scancode] == KEY_UP) {
            if (cl_strcmp(currentProcess->processName, "EDIT") == 0 && global_pos / MAX_COLUMNS > 0) {
                CursorMove(global_pos / MAX_COLUMNS - 1, global_pos % MAX_COLUMNS);
                global_pos -= MAX_COLUMNS; // global_pos is local to the edit_mode process, this is why it doesnt matter how we change it since the console has its own global_pos (currentPosition in the specific process that is active)
            }
            else if (cl_strcmp(currentProcess->processName, "CONSOLE") == 0) {
                // Maybe some ifs are not neccessary, idk yet. Will look into it later on
                if (commandHistory->startingIndex >= 9 - commandHistory->numberOfCommands + 1) {
                    if (commandHistory->startingIndex >= 0) {
                        for (int i = 0; i < cl_strlen(commandHistory->command[commandHistory->startingIndex + 1]); i++) {
                            Backspace();
                        }
                    }
                    // commandHistory->startingIndex -= 1;
                    ScreenDisplay(commandHistory->command[commandHistory->startingIndex], COLOR_WHITE);

                    if (commandHistory->startingIndex - 1 >= 0) {
                        commandHistory->startingIndex -= 1;
                    }
                }
            }
        }
        else if (_kkybrd_scancode_ext[scancode] == KEY_DOWN) {
            if (cl_strcmp(currentProcess->processName, "EDIT") == 0 && global_pos / MAX_COLUMNS < MAX_OFFSET / MAX_COLUMNS) {
                CursorMove(global_pos / MAX_COLUMNS + 1, global_pos % MAX_COLUMNS);
                global_pos += MAX_COLUMNS;
            }
            else if (cl_strcmp(currentProcess->processName, "CONSOLE") == 0) {
                // Maybe some ifs are not neccessary, idk yet. Will look into it later on
                if (commandHistory->startingIndex <= 9) {
                    // if (commandHistory->startingIndex != 9) {
                        for (int i = 0; i < cl_strlen(commandHistory->command[commandHistory->startingIndex + 1]); i++) {
                            Backspace();
                        }
                    // }
                    currentProcess->positionInProcess -= cl_strlen(commandHistory->command[commandHistory->startingIndex - 1]);
                    if (commandHistory->startingIndex + 1 < 10) {
                        commandHistory->startingIndex += 1; 
                        ScreenDisplay(commandHistory->command[commandHistory->startingIndex], COLOR_WHITE);
                    } 
                    else {
                        ScreenDisplay("", COLOR_WHITE);
                    }
                }
            }
        }
        else if (_kkybrd_scancode_ext[scancode] == KEY_LEFT) {
            if (cl_strcmp(currentProcess->processName, "EDIT") == 0) {
                CursorMove(global_pos / MAX_COLUMNS, global_pos % MAX_COLUMNS - 1);
                global_pos -= 1;
            }
        }
        else if (_kkybrd_scancode_ext[scancode] == KEY_RIGHT) {
            if (cl_strcmp(currentProcess->processName, "EDIT") == 0) {
                CursorMove(global_pos / MAX_COLUMNS, global_pos % MAX_COLUMNS + 1);
                global_pos += 1;
            }
        }

        // if (released) return;
        else {
            if (released) return;

            BYTE chr;
            chr = shift_pressed ? _kkybrd_scancode_std_shift[scancode] : _kkybrd_scancode_std[scancode];

            text_buffer[cl_strlen(text_buffer)] = chr;
            // Log(text_buffer);
            // LogSerialAndScreen("%d", cl_strlen(text_buffer));
            // ScreenDisplay(text_buffer, COLOR_BLACK);
            PutChar(chr, global_pos, COLOR_WHITE);
            global_pos += 1;
            // pos += 1;

            commandHistory->startingIndex = 9;
        }
    }
}