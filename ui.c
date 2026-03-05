#include "ui.h"

// Clear terminal using ANSI escape
void ui_clearScreen() {
    printf("\033[2J\033[1;1H");
}

// Welcome banner
void ui_showWelcome() {
    ui_clearScreen();
    printf(C_CYAN "============================================\n" C_RESET);
    printf(C_MAGENTA "            WELCOME TO TERMINAL       \n" C_RESET);
    printf(C_CYAN "============================================\n\n" C_RESET);

    printf(C_GREEN "Type 'help' to see all available commands.\n\n" C_RESET);
}

// Dynamic input function
char* ui_getInput() {
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return NULL;
    }

    // allocate memory dynamically
    char *input = (char*)malloc(strlen(buffer) + 1);
    if (!input) {
        printf(C_RED "Memory allocation failed!\n" C_RESET);
        return NULL;
    }

    strcpy(input, buffer);

    // remove newline
    input[strcspn(input, "\n")] = '\0';

    return input;
}

// Colorful prompt
void ui_printPrompt() {
    printf(C_BLUE "user" C_RESET ":" C_GREEN "terminal" C_RESET "$ ");
}

// Error message
void ui_error(const char *msg) {
    printf(C_RED "[ERROR] %s\n" C_RESET, msg);
}

// Success message
void ui_success(const char *msg) {
    printf(C_GREEN "[OK] %s\n" C_RESET, msg);
}

// Warning message
void ui_warning(const char *msg) {
    printf(C_YELLOW "[WARNING] %s\n" C_RESET, msg);
}
