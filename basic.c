#include <stdio.h>
#include <string.h>
#include "../UI/ui.h"
#include "../Util/util.h"
#include "../Command/command.h"
#include "basic.h"

// ===============================
// PRINT TEXT BACK
// ===============================
void cmd_echo(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: echo <text>");
        return;
    }

    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

// ===============================
// REPEAT TEXT TWICE
// ===============================
void cmd_repeat(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: repeat <text>");
        return;
    }

    for (int rep = 0; rep < 2; rep++) {
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
    }
    printf("\n");
}

// ===============================
// ADD TWO INTEGERS
// ===============================
void cmd_mathadd(int argc, char **argv) {
    if (argc < 3) {
        ui_warning("Usage: add <num1> <num2>");
        return;
    }

    if (!util_isNumber(argv[1]) || !util_isNumber(argv[2])) {
        ui_error("Arguments must be numbers.");
        return;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d\n", a + b);
}

// ===============================
// SUBTRACT TWO INTEGERS
// ===============================
void cmd_mathsub(int argc, char **argv) {
    if (argc < 3) {
        ui_warning("Usage: sub <num1> <num2>");
        return;
    }

    if (!util_isNumber(argv[1]) || !util_isNumber(argv[2])) {
        ui_error("Arguments must be numbers.");
        return;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d\n", a - b);
}

// ===============================
// REVERSE A STRING
// ===============================
void cmd_reverse(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: reverse <text>");
        return;
    }

    char text[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(text, argv[i]);
        if (i != argc - 1) strcat(text, " ");
    }

    util_reverse(text);  
    printf("%s\n", text);
}

// ===============================
// CONVERT TO UPPERCASE
// ===============================
void cmd_upper(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: upper <text>");
        return;
    }

    char text[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(text, argv[i]);
        if (i != argc - 1) strcat(text, " ");
    }

    util_strUpper(text);  
    printf("%s\n", text);
}

// ===============================
// CONVERT TO LOWERCASE
// ===============================
void cmd_lower(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: lower <text>");
        return;
    }

    char text[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(text, argv[i]);
        if (i != argc - 1) strcat(text, " ");
    }

    util_strLower(text);  
    printf("%s\n", text);
}

// ===============================
// REGISTER BASIC COMMANDS
// ===============================
void register_basic_commands(void) {
    command_register("echo",   "Print text",                 cmd_echo);
    command_register("repeat", "Repeat text twice",          cmd_repeat);
    command_register("add",    "Add two numbers",            cmd_mathadd);
    command_register("sub",    "Subtract two numbers",       cmd_mathsub);
    command_register("reverse","Reverse text",               cmd_reverse);
    command_register("upper",  "Convert to uppercase",       cmd_upper);
    command_register("lower",  "Convert to lowercase",       cmd_lower);
}
