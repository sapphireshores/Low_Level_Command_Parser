#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
    char *name;
    char *description;
    void (*execute)(int, char**);
} Command;

void command_init();
void command_register(const char *name, const char *desc, void (*func)(int, char**));
void command_run(char *input);
void command_list(int argc, char **argv);

#endif
