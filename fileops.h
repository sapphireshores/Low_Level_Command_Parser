#ifndef FILEOPS_H
#define FILEOPS_H

/* initialize all file operation commands */
void fileops_init();

/* file ops command functions */
void cmd_mkfile(int argc, char **argv);
void cmd_delfile(int argc, char **argv);
void cmd_readfile(int argc, char **argv);
void cmd_writefile(int argc, char **argv);
void cmd_appendfile(int argc, char **argv);
void cmd_copyfile(int argc, char **argv);
void cmd_movefile(int argc, char **argv);
void cmd_renamefile(int argc, char **argv);
void cmd_fileexists(int argc, char **argv);
void cmd_filesize(int argc, char **argv);
void cmd_fileclear(int argc, char **argv);
void cmd_filelines(int argc, char **argv);
void cmd_filewords(int argc, char **argv);
void cmd_filechars(int argc, char **argv);
void cmd_filemerge(int argc, char **argv);

#endif
