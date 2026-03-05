#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

// ==============================
//  SAFE INPUT
// ==============================
void util_safeInput(char *buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        util_removeNewline(buffer);
    }
}

// ==============================
//  REMOVE NEWLINE
// ==============================
void util_removeNewline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n')
        s[len-1] = '\0';
}

// ==============================
//  STRING LOWERCASE
// ==============================
void util_strLower(char *s) {
    while (*s) {
        *s = tolower(*s);
        s++;
    }
}

// ==============================
//  STRING UPPERCASE
// ==============================
void util_strUpper(char *s) {
    while (*s) {
        *s = toupper(*s);
        s++;
    }
}

// ==============================
//  TRIM WHITESPACE (BOTH SIDES)
// ==============================
void util_trim(char *str) {
    char *start;
    char *end;
    start = str;
    while (isspace(*start)) start++;

    if (*start == 0) {
        str[0] = '\0';
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace(*end))
    {
        end--;
    }
    *(end + 1) = '\0';
    memmove(str, start, strlen(start) + 1);
}

// ==============================
//  REVERSE STRING
// ==============================
void util_reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

// ==============================
//  CHECK IF NUMBER
// ==============================
int util_isNumber(const char *s) {
    if (*s == '-' || *s == '+') s++;
    if (!*s) return 0;

    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

// ==============================
//  DEBUG PRINT ARGS
// ==============================
void util_debugArgs(char **args, int count) {
    printf("Args (%d):\n", count);
    for (int i = 0; i < count; i++)
        printf("[%d] %s\n", i, args[i]);
}

// ==============================
//  PROPER, FIXED TOKEN SPLIT
// ==============================
char **util_split(const char *input, int *count) {
    *count = 0;
    char *copy = strdup(input);
    util_trim(copy);

    char *token;
    int cap = 4;

    char **list = malloc(sizeof(char*) * cap);

    token = strtok(copy, " ");

    while (token != NULL) {
        if (*count >= cap) {
            cap *= 2;
            list = realloc(list, sizeof(char*) * cap);
        }

        list[*count] = strdup(token);
        (*count)++;

        token = strtok(NULL, " ");
    }

    free(copy);
    return list;
}

// ==============================
//  FREE ARG LIST
// ==============================
void util_freeArgs(char **args, int count) {
    for (int i = 0; i < count; i++)
        free(args[i]);
    free(args);
}
