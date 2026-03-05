#ifndef TEXTOPS_H
#define TEXTOPS_H

void textops_init();
void register_textops_commands(void);

// commands
void cmd_countchars(int argc, char **argv);
void cmd_countlines(int argc, char **argv);
void cmd_countwords(int argc, char **argv);

void cmd_readtext(int argc, char **argv);
void cmd_writetext(int argc, char **argv);
void cmd_appendtext(int argc, char **argv);

void cmd_findword(int argc, char **argv);
void cmd_replaceword(int argc, char **argv);

void cmd_reversetext(int argc, char **argv);
void cmd_uppercase(int argc, char **argv);
void cmd_lowercase(int argc, char **argv);

void cmd_copytext(int argc, char **argv);

#endif
