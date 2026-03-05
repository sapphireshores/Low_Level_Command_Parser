#ifndef UTIL_H
#define UTIL_H

// string helpers
void util_trim(char *str);
void util_removeNewline(char *s);
void util_strLower(char *s);
void util_strUpper(char *s);
void util_reverse(char *s);

// number helpers
int util_isNumber(const char *s);

// input helpers
void util_safeInput(char *buffer, int size);

// split helpers
char **util_split(const char *input, int *count);
void util_freeArgs(char **args, int count);

// debug
void util_debugArgs(char **args, int count);

#endif
