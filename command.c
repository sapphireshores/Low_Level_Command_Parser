#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../UI/ui.h"
#include "../Util/util.h"
#include "command.h"

#define MAX_COMMANDS 100

static Command commands[MAX_COMMANDS];
static int commandCount = 0;

/* ============================================================
   Register a command
   ============================================================ */
void command_register(const char *name, const char *desc, void (*func)(int, char **))
{
    if (commandCount >= MAX_COMMANDS)
        return;

    /* strdup ensures memory is allocated */
    commands[commandCount].name = malloc(strlen(name) + 1);
    strcpy(commands[commandCount].name, name);

    commands[commandCount].description = malloc(strlen(desc) + 1);
    strcpy(commands[commandCount].description, desc);

    commands[commandCount].execute = func;
    commandCount++;
}

/* ============================================================
   Built-in help
   ============================================================ */
void command_list(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\nAvailable commands:\n\n");
    for (int i = 0; i < commandCount; i++)
    {
        printf("  %-12s - %s\n",
               commands[i].name,
               commands[i].description);
    }
    printf("\n");
}

/* ============================================================
   Initialize command system (resets & adds HELP)
   ============================================================ */
void command_init()
{
    for (int i = 0; i < commandCount; i++)
    {
        free(commands[i].name);
        free(commands[i].description);
    }

    commandCount = 0;

    /* Register built-in help */
    command_register("help", "Show all commands", command_list);
}

/* ============================================================
   Execute a command line
   ============================================================ */
void command_run(char *input)
{
    if (!input)
        return;

    int argc = 0;
    char **argv = util_split(input, &argc);

    if (argc == 0)
    {
        util_freeArgs(argv, argc);
        return;
    }

    /* Normalize command name */
    util_strLower(argv[0]);

    /* Search for command */
    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(argv[0], commands[i].name) == 0)
        {
            commands[i].execute(argc, argv);
            util_freeArgs(argv, argc);
            return;
        }
    }

    ui_warning("Unknown command. Type 'help' to see available commands.");
    util_freeArgs(argv, argc);
}
