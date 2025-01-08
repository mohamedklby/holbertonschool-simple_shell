#ifndef SHELL_H
#define SHELL_H

#define TOK_DELIM " \t\r\n\a\""

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char *read_line(void);
char **parse_line(char *line);
int execute_args(char **args);
char *is_a_command(char *args);
void print_env(void);
void print_prompt(void);
int main(void);
char *_getenv(const char *name);
#endif
