#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

extern char **environ;

char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *func_read(void);
int func_exec(char **args);
void free_grid(char **grid);
char **func_split(char *line);
char *get_env(char *getcmd);
char *get_path(char *getcmd);
void _printenv(void);
void ctrl_c(int signal);
char **split_env(char *path);
char *trim(char *str);

#endif
