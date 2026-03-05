#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C_RESET   "\033[0m"
#define C_RED     "\033[31m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"

void ui_clearScreen();
void ui_showWelcome();
void ui_printPrompt();
char* ui_getInput();

void ui_error(const char *msg);
void ui_success(const char *msg);
void ui_warning(const char *msg);

#endif
