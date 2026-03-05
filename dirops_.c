#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../UI/ui.h"
#include "../Util/util.h"
#include "dirops.h"

void dirops_init();
void cmd_mkdir(int argc, char **argv);
void cmd_rmdir(int argc, char **argv);
void cmd_ls(int argc, char **argv);
void cmd_pwd(int argc, char **argv);
void cmd_cd(int argc, char **argv);
void cmd_touch(int argc, char **argv);
void cmd_rmtouch(int argc, char **argv);

// Static Helper Functions (Internal use only)
static void make_path(char *out, const char *name);
static int read_entries(const char *path, char ***list);
static void write_entries(const char *path, char **list, int count);
static void free_list(char **list, int count);

static char currentPath[256];

/* =======================================================
   Initialize Virtual Filesystem Root
   ======================================================= */
void dirops_init() {
    strcpy(currentPath, "filesystem/nebula");
}

/* Build "<currentPath>/<name>" */
static void make_path(char *out, const char *name) {
    snprintf(out, 256, "%s/%s", currentPath, name);
}

/* =======================================================
   Read .dirinfo entries
   ======================================================= */
static int read_entries(const char *path, char ***list) {
    char info[256];
    snprintf(info, 256, "%s/.dirinfo", path);

    FILE *fp = fopen(info, "r");
    if (!fp) {
        *list = NULL;
        return 0;
    }

    int cap = 8;
    int count = 0;
    char **arr = malloc(sizeof(char*) * cap);

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        util_removeNewline(line);
        if (strlen(line) == 0) continue;

        if (count >= cap) {
            cap *= 2;
            arr = realloc(arr, sizeof(char*) * cap);
        }

        arr[count] = malloc(strlen(line) + 1);
        strcpy(arr[count], line);
        count++;
    }

    fclose(fp);
    *list = arr;
    return count;
}

/* =======================================================
   Write entries back to .dirinfo
   ======================================================= */
static void write_entries(const char *path, char **list, int count) {
    char info[256];
    snprintf(info, 256, "%s/.dirinfo", path);

    FILE *fp = fopen(info, "w");
    if (!fp) return;

    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", list[i]);

    fclose(fp);
}

/* =======================================================
   Free list
   ======================================================= */
static void free_list(char **list, int count) {
    if (!list) return;
    for (int i = 0; i < count; i++)
        free(list[i]);
    free(list);
}

/* =======================================================
   mkdir <folder>
   ======================================================= */
void cmd_mkdir(int argc, char **argv) {
    if (argc != 2) {
        ui_warning("Usage: mkdir <folder>");
        return;
    }

    /* Create folder file */
    char dirPath[256];
    snprintf(dirPath, sizeof(dirPath), "%s/%s.dir", currentPath, argv[1]);

    FILE *fp = fopen(dirPath, "w");
    if (!fp) {
        ui_error("Could not create directory.");
        return;
    }
    fclose(fp);

    /* Create its .dirinfo */
    char infoPath[256];
    snprintf(infoPath, sizeof(infoPath), "%s/.dirinfo", dirPath);
    fp = fopen(infoPath, "w");
    if (fp) fclose(fp);

    /* Add to parent directory list */
    char **list;
    int count = read_entries(currentPath, &list);

    list = realloc(list, sizeof(char*) * (count + 1));
    list[count] = malloc(strlen(argv[1]) + 5);
    sprintf(list[count], "%s.dir", argv[1]);
    count++;

    write_entries(currentPath, list, count);
    free_list(list, count);

    ui_success("Directory created.");
}

/* =======================================================
   rmdir <folder>
   ======================================================= */
void cmd_rmdir(int argc, char **argv) {
    if (argc != 2) {
        ui_warning("Usage: rmdir <folder>");
        return;
    }

    /* Remove folder file */
    char dirPath[256];
    snprintf(dirPath, sizeof(dirPath), "%s/%s.dir", currentPath, argv[1]);

    char infoPath[256];
    snprintf(infoPath, sizeof(infoPath), "%s/.dirinfo", dirPath);

    remove(infoPath);
    remove(dirPath);

    /* Remove entry from parent list */
    char **list;
    int count = read_entries(currentPath, &list);

    char **newList = malloc(sizeof(char*) * count);
    int newCount = 0;

    char target[64];
    snprintf(target, sizeof(target), "%s.dir", argv[1]);

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], target) == 0) continue;

        newList[newCount] = malloc(strlen(list[i]) + 1);
        strcpy(newList[newCount], list[i]);
        newCount++;
    }

    write_entries(currentPath, newList, newCount);

    free_list(list, count);
    free_list(newList, newCount);

    ui_success("Directory removed.");
}

/* =======================================================
   ls
   ======================================================= */
void cmd_ls(int argc, char **argv) {
    char **list;
    int count = read_entries(currentPath, &list);

    if (count == 0) {
        ui_warning("Directory empty.");
        return;
    }

    for (int i = 0; i < count; i++)
        printf("%s\n", list[i]);

    free_list(list, count);
}

/* =======================================================
   pwd
   ======================================================= */
void cmd_pwd(int argc, char **argv) {
    printf("%s\n", currentPath);
}

/* =======================================================
   cd <folder>
   ======================================================= */
void cmd_cd(int argc, char **argv) {
    if (argc != 2) {
        ui_warning("Usage: cd <folder>");
        return;
    }

    char newPath[256];
    snprintf(newPath, sizeof(newPath), "%s/%s.dir", currentPath, argv[1]);

    /* Check if folder exists */
    char infoPath[256];
    snprintf(infoPath, sizeof(infoPath), "%s/.dirinfo", newPath);

    FILE *fp = fopen(infoPath, "r");
    if (!fp) {
        ui_error("Folder does not exist.");
        return;
    }
    fclose(fp);

    strcpy(currentPath, newPath);
    ui_success("Directory changed.");
}

/* =======================================================
   touch <file>
   ======================================================= */
void cmd_touch(int argc, char **argv) {
    if (argc != 2) {
        ui_warning("Usage: touch <file>");
        return;
    }

    char filePath[256];
    make_path(filePath, argv[1]);

    /* Create file */
    FILE *fp = fopen(filePath, "w");
    if (fp) fclose(fp);

    /* Add entry */
    char **list;
    int count = read_entries(currentPath, &list);

    list = realloc(list, sizeof(char*) * (count + 1));
    list[count] = malloc(strlen(argv[1]) + 1);
    strcpy(list[count], argv[1]);
    count++;

    write_entries(currentPath, list, count);
    free_list(list, count);

    ui_success("File created.");
}

/* =======================================================
   rmtouch <file>
   ======================================================= */
void cmd_rmtouch(int argc, char **argv) {
    if (argc != 2) {
        ui_warning("Usage: rmtouch <file>");
        return;
    }

    char filePath[256];
    make_path(filePath, argv[1]);
    remove(filePath);

    /* Remove from entry list */
    char **list;
    int count = read_entries(currentPath, &list);

    char **newList = malloc(sizeof(char*) * count);
    int newCount = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], argv[1]) == 0) continue;

        newList[newCount] = malloc(strlen(list[i]) + 1);
        strcpy(newList[newCount], list[i]);
        newCount++;
    }

    write_entries(currentPath, newList, newCount);

    free_list(list, count);
    free_list(newList, newCount);

    ui_success("File removed.");
}
