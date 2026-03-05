#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../UI/ui.h"
#include "../Util/util.h"
#include "../Command/command.h"
#include "textops.h"

// Register all commands
void textops_init() {
    command_register("countchars",  "Count characters in a file",            cmd_countchars);
    command_register("countlines",  "Count lines in a file",                 cmd_countlines);
    command_register("countwords",  "Count words in a file",                 cmd_countwords);

    command_register("readtext",    "Read file and print",                   cmd_readtext);
    command_register("writetext",   "Overwrite file with new text",          cmd_writetext);
    command_register("appendtext",  "Append text to file",                   cmd_appendtext);

    command_register("findword",    "Search word in file",                   cmd_findword);
    command_register("replaceword", "Replace word in file",                  cmd_replaceword);

    command_register("reversetext", "Reverse file text",                     cmd_reversetext);
    command_register("uppercase",   "Convert file text to uppercase",        cmd_uppercase);
    command_register("lowercase",   "Convert file text to lowercase",        cmd_lowercase);

    command_register("copytext",    "Copy one file to another",              cmd_copytext);
}

/* =====================================================
   BASIC TEXT OPERATIONS BELOW
   =====================================================*/

// Count characters
void cmd_countchars(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: countchars <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    int count = 0;
    while (fgetc(fp) != EOF) count++;

    fclose(fp);
    printf("Characters: %d\n", count);
}

// Count lines
void cmd_countlines(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: countlines <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    int lines = 0;  
    int ch;
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n') lines++;

    fclose(fp);
    printf("Lines: %d\n", lines);
}

// Count words
void cmd_countwords(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: countwords <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    int words = 0;
    char word[256];

    while (fscanf(fp, "%255s", word) == 1)
        words++;

    fclose(fp);
    printf("Words: %d\n", words);
}

// Read file
void cmd_readtext(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: readtext <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    char line[256];
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}

// Write file
void cmd_writetext(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: writetext <file>"); return; }

    FILE *fp = fopen(argv[1], "w");
    if (!fp) { ui_error("Cannot open file."); return; }

    printf("Enter text (end with an empty line):\n");

    char buffer[256];
    while (1) {
        util_safeInput(buffer, sizeof(buffer));
        if (strlen(buffer) == 0) break;
        fprintf(fp, "%s\n", buffer);
    }

    fclose(fp);
    ui_success("File written.");
}

// Append text
void cmd_appendtext(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: appendtext <file>"); return; }

    FILE *fp = fopen(argv[1], "a");
    if (!fp) { ui_error("Cannot open file."); return; }

    printf("Enter text to append (end with empty line):\n");

    char buffer[256];
    while (1) {
        util_safeInput(buffer, sizeof(buffer));
        if (strlen(buffer) == 0) break;
        fprintf(fp, "%s\n", buffer);
    }

    fclose(fp);
    ui_success("Text appended.");
}

// Find word
void cmd_findword(int argc, char **argv) {
    if (argc != 3) { ui_warning("Usage: findword <file> <word>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    int lineNum = 1;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[2])) {
            printf("Found at line %d: %s", lineNum, line);
        }
        lineNum++;
    }

    fclose(fp);
}

// Replace word
void cmd_replaceword(int argc, char **argv) {
    if (argc != 4) { ui_warning("Usage: replaceword <file> <old> <new>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    FILE *temp = fopen("temp.txt", "w");

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *pos;
        while ((pos = strstr(line, argv[2])) != NULL) {
            *pos = '\0';
            fprintf(temp, "%s%s%s", line, argv[3], pos + strlen(argv[2]));
            strcpy(line, pos + strlen(argv[2]));
        }
        fprintf(temp, "%s", line);
    }

    fclose(fp);
    fclose(temp);

    remove(argv[1]);
    rename("temp.txt", argv[1]);

    ui_success("Word replaced.");
}

// Reverse file content
void cmd_reversetext(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: reversetext <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    char content[5000] = "";
    char line[256];

    while (fgets(line, sizeof(line), fp))
        strcat(content, line);

    fclose(fp);

    util_reverse(content);

    fp = fopen(argv[1], "w");
    fprintf(fp, "%s", content);
    fclose(fp);

    ui_success("File reversed.");
}

// uppercase file
void cmd_uppercase(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: uppercase <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    char content[5000] = "";
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        util_strUpper(line);
        strcat(content, line);
    }

    fclose(fp);

    fp = fopen(argv[1], "w");
    fprintf(fp, "%s", content);
    fclose(fp);

    ui_success("Converted to UPPERCASE.");
}

// lowercase file
void cmd_lowercase(int argc, char **argv) {
    if (argc != 2) { ui_warning("Usage: lowercase <file>"); return; }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { ui_error("File not found."); return; }

    char content[5000] = "";
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        util_strLower(line);
        strcat(content, line);
    }

    fclose(fp);

    fp = fopen(argv[1], "w");
    fprintf(fp, "%s", content);
    fclose(fp);

    ui_success("Converted to lowercase.");
}

// Copy file
void cmd_copytext(int argc, char **argv) {
    if (argc != 3) {
        ui_warning("Usage: copytext <src> <dest>");
        return;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) { ui_error("Source file not found."); return; }

    FILE *dest = fopen(argv[2], "w");
    if (!dest) { ui_error("Cannot create destination file."); fclose(src); return; }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), src))
        fputs(buffer, dest);

    fclose(src);
    fclose(dest);

    ui_success("File copied.");
}
