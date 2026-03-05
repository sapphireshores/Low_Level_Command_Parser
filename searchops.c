#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../UI/ui.h"
#include "../Util/util.h"
#include "searchops.h"
#include "../Command/command.h"


void cmd_search(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: search <file> <word>");
        return;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("Cannot open file."); return; }

    char line[256]; int lineNo = 1;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[2])) printf("%d: %s", lineNo, line);
        lineNo++;
    }
    fclose(fp);
}

void cmd_searchcount(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: searchcount <file> <word>");
        return;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("Cannot open file."); return; }

    char line[256]; int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[2])) count++;
    }
    printf("Count = %d\n", count);
    fclose(fp);
}

void cmd_searchprefix(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: searchprefix <file> <prefix>");
        return;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("Cannot open file."); return; }

    char line[256]; int len = strlen(argv[2]);
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, argv[2], len) == 0) printf("%s", line);
    }
    fclose(fp);
}

void cmd_searchsuffix(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: searchsuffix <file> <suffix>");
        return;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("Cannot open file."); return; }

    char line[256]; int slen = strlen(argv[2]);
    while (fgets(line, sizeof(line), fp)) {
        int len = strlen(line);
        if (len >= slen && strcmp(line + len - slen, argv[2]) == 0)
            printf("%s", line);
    }
    fclose(fp);
}

void cmd_findline(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: findline <file> <text>");
        return;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("Cannot open file."); return; }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        util_removeNewline(line);
        if (strcmp(line, argv[2]) == 0)
            printf("FOUND: %s\n", line);
    }
    fclose(fp);
}

void cmd_comparetext(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: comparetext <str1> <str2>");
        return;
    }
    printf("Result = %d\n", strcmp(argv[1], argv[2]));
}

void searchops_init() {
    command_register("search",       "Find lines containing a word",      cmd_search);
    command_register("searchcount",  "Count lines containing a word",     cmd_searchcount);
    command_register("searchprefix", "Lines starting with prefix",        cmd_searchprefix);
    command_register("searchsuffix", "Lines ending with suffix",          cmd_searchsuffix);
    command_register("findline",     "Find exact line",                   cmd_findline);
    command_register("comparetext",  "Compare exact strings",             cmd_comparetext);
}
