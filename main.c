#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UI/ui.h"
#include "Command/command.h"
#include "Commands/basic.h"
#include "FileOps/fileops.h"
#include "DirOps/dirops.h"
#include "TextOps/textops.h"
#include "SearchOps/searchops.h"
#include "MathOps/mathops.h"
#include "SysOps/sysops.h"

int main() {
    ui_showWelcome();
    command_init();

    /* Register all modules */
    register_basic_commands();
    fileops_init();
    dirops_init();
    textops_init();
    searchops_init();
    mathops_init();
    sysops_init();

    while (1) {
        ui_printPrompt();
        char *input = ui_getInput();
        command_run(input);
        free(input);
    }

    return 0;
}
