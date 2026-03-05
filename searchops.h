#ifndef SEARCHOPS_H
#define SEARCHOPS_H

void searchops_init();

/* Commands */
void cmd_search(int argc, char **argv);
void cmd_searchcount(int argc, char **argv);
void cmd_searchprefix(int argc, char **argv);
void cmd_searchsuffix(int argc, char **argv);
void cmd_findline(int argc, char **argv);
void cmd_comparetext(int argc, char **argv);

#endif
