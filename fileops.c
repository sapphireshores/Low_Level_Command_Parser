#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../UI/ui.h"
#include "../Command/command.h"
#include "../Util/util.h"
#include "fileops.h"

/* ============================
   REGISTER ALL FILE COMMANDS
   ============================ */
void fileops_init() {
    command_register("mkfile",     "Create file",                 cmd_mkfile);
    command_register("delfile",    "Delete file",                 cmd_delfile);
    command_register("readfile",   "Read file contents",          cmd_readfile);
    command_register("writefile",  "Write (overwrite) file",      cmd_writefile);
    command_register("appendfile", "Append to file",              cmd_appendfile);
    command_register("copyfile",   "Copy file",                   cmd_copyfile);
    command_register("movefile",   "Move file",                   cmd_movefile);
    command_register("renamefile", "Rename file",                 cmd_renamefile);
    command_register("fileexists", "Check if file exists",        cmd_fileexists);
    command_register("filesize",   "Get file size",               cmd_filesize);
    command_register("fileclear",  "Clear a file",                cmd_fileclear);
    command_register("filelines",  "Count lines in file",         cmd_filelines);
    command_register("filewords",  "Count words in file",         cmd_filewords);
    command_register("filechars",  "Count characters in file",    cmd_filechars);
    command_register("filemerge",  "Merge two files",             cmd_filemerge);
}

/* check if file exists */
static int f_exists(const char *name) {
    FILE *f = fopen(name, "r");
    if (!f) return 0;
    fclose(f);
    return 1;
}

/* ============================
   CREATE FILE
   ============================ */
void cmd_mkfile(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: mkfile <name>"); return; }

    FILE *f = fopen(argv[1], "w");
    if (!f) { ui_error("Unable to create file."); return; }
    fclose(f);

    ui_success("File created.");
}

/* ============================
   DELETE FILE
   ============================ */
void cmd_delfile(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: delfile <name>"); return; }

    if (remove(argv[1]) == 0)
        ui_success("File deleted.");
    else
        ui_error("Could not delete file.");
}

/* ============================
   READ FILE
   ============================ */
void cmd_readfile(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: readfile <name>"); return; }

    FILE *f = fopen(argv[1], "r");
    if (!f) { ui_error("Cannot open file."); return; }

    char line[256];
    while (fgets(line, sizeof(line), f))
        printf("%s", line);

    fclose(f);
}

/* ============================
   WRITE FILE (overwrite)
   ============================ */
void cmd_writefile(int argc, char **argv) {
    if (argc < 3) { 
        ui_warning("Usage: writefile <name> <text>");
        return;
    }

    FILE *f = fopen(argv[1], "w");
    if (!f) { ui_error("Cannot write to file."); return; }

    for (int i = 2; i < argc; i++)
        fprintf(f, "%s ", argv[i]);
    fclose(f);

    ui_success("Write complete.");
}

/* ============================
   APPEND FILE
   ============================ */
void cmd_appendfile(int argc, char **argv) {
    if (argc < 3) { 
        ui_warning("Usage: appendfile <name> <text>");
        return;
    }

    FILE *f = fopen(argv[1], "a");
    if (!f) { ui_error("Cannot append to file."); return; }

    for (int i = 2; i < argc; i++)
        fprintf(f, "%s ", argv[i]);
    fclose(f);

    ui_success("Append complete.");
}

/* ============================
   COPY FILE
   ============================ */
void cmd_copyfile(int argc, char **argv) {
    if (argc < 3) { 
        ui_warning("Usage: copyfile <src> <dest>");
        return;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) { ui_error("Cannot open source file."); return; }

    FILE *dest = fopen(argv[2], "w");
    if (!dest) { fclose(src); ui_error("Cannot open destination."); return; }

    int c;
    while ((c = fgetc(src)) != EOF)
        fputc(c, dest);

    fclose(src);
    fclose(dest);

    ui_success("Copy complete.");
}

/* ============================
   MOVE FILE
   ============================ */
void cmd_movefile(int argc, char **argv) {
    if (argc < 3) { 
        ui_warning("Usage: movefile <old> <new>");
        return;
    }

    if (rename(argv[1], argv[2]) == 0)
        ui_success("Move complete.");
    else
        ui_error("Move failed.");
}

/* ============================
   RENAME FILE
   ============================ */
void cmd_renamefile(int argc, char **argv) {
    if (argc < 3) {
        ui_warning("Usage: renamefile <old> <new>");
        return;
    }

    if (rename(argv[1], argv[2]) == 0)
        ui_success("Rename complete.");
    else
        ui_error("Rename failed.");
}

/* ============================
   FILE EXISTS
   ============================ */
void cmd_fileexists(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: fileexists <name>"); return; }

    if (f_exists(argv[1])) printf("YES\n");
    else printf("NO\n");
}

/* ============================
   FILE SIZE
   ============================ */
void cmd_filesize(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: filesize <name>"); return; }

    FILE *f = fopen(argv[1], "r");
    if (!f) { ui_error("Cannot open file."); return; }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);

    printf("%ld bytes\n", size);
}

/* ============================
   CLEAR FILE
   ============================ */
void cmd_fileclear(int argc, char **argv) {
    if (argc < 2) {
        ui_warning("Usage: fileclear <name>");
        return;
    }

    FILE *f = fopen(argv[1], "w");
    if (!f) { ui_error("Cannot clear file."); return; }
    fclose(f);

    ui_success("File cleared.");
}

/* ============================
   COUNT LINES
   ============================ */
void cmd_filelines(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: filelines <name>"); return; }

    FILE *f = fopen(argv[1], "r");
    if (!f) { ui_error("Cannot open file."); return; }

    int lines = 0;
    char buf[256];

    while (fgets(buf, sizeof(buf), f))
        lines++;

    fclose(f);
    printf("%d\n", lines);
}

/* ============================
   COUNT WORDS      
   ============================ */
void cmd_filewords(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: filewords <name>"); return; }

    FILE *f = fopen(argv[1], "r");
    if (!f) { ui_error("Cannot open file."); return; }

    int words = 0;
    char w[128];

    while (fscanf(f, "%127s", w) == 1)
        words++;

    fclose(f);
    printf("%d\n", words);
}

/* ============================
   COUNT CHARS
   ============================ */
void cmd_filechars(int argc, char **argv) {
    if (argc < 2) { ui_warning("Usage: filechars <name>"); return; }

    FILE *f = fopen(argv[1], "r");
    if (!f) { ui_error("Cannot open file."); return; }

    int count = 0;
    int c;

    while ((c = fgetc(f)) != EOF)
        count++;

    fclose(f);
    printf("%d\n", count);
}

/* ============================
   MERGE FILES
   ============================ */
void cmd_filemerge(int argc, char **argv) {
    if (argc < 4) {
        ui_warning("Usage: filemerge <file1> <file2> <out>");
        return;
    }

    FILE *a = fopen(argv[1], "r");
    FILE *b = fopen(argv[2], "r");

    if (!a || !b) {
        ui_error("Cannot open input files.");
        if (a) fclose(a);
        if (b) fclose(b);
        return;
    }

    FILE *out = fopen(argv[3], "w");
    if (!out) { ui_error("Cannot open output file."); return; }

    int c;
    while ((c = fgetc(a)) != EOF)
        fputc(c, out);

    while ((c = fgetc(b)) != EOF)
        fputc(c, out);

    fclose(a);
    fclose(b);
    fclose(out);

    ui_success("Merge complete.");
}
