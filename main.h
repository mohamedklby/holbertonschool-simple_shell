#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

void token_input(char *input);
void executable(char **argv, char *input);
char *_getpath(char *cmd);
void print_env(void);

#endif
