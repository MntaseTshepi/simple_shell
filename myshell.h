#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>

extern char **environ;

void print_prompt(void);
int main(int ac, char **argv);
char **parse_command(char *command, ssize_t num_chars);
char *_getenv(const char *name);
char **tokenizePath();
char *actual_path(char *command);
void execute_command(char **argv);
void _printenviron(void);
int is_builtin(char *command);
void execute_builtin_command(char *command, char **argv);
void execute_binary_command(char *command, char **argv);
void _printexit(void);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif
