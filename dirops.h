#ifndef DIROPS_H
#define DIROPS_H

void dirops_init();
void register_dirops_commands(void);

// commands
void cmd_mkdir(int argc, char **argv);
void cmd_rmdir(int argc, char **argv);
void cmd_ls(int argc, char **argv);
void cmd_pwd(int argc, char **argv);
void cmd_cd(int argc, char **argv);
void cmd_touch(int argc, char **argv);
void cmd_rmtouch(int argc, char **argv);

#endif
