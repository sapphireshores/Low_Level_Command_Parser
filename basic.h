#ifndef BASIC_H
#define BASIC_H

void register_basic_commands(void);

// command functions
void cmd_echo(int argc, char **argv);
void cmd_repeat(int argc, char **argv);
void cmd_mathadd(int argc, char **argv);
void cmd_mathsub(int argc, char **argv);
void cmd_reverse(int argc, char **argv);
void cmd_upper(int argc, char **argv);
void cmd_lower(int argc, char **argv);

#endif
