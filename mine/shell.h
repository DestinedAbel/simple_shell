#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 100


 int i;

typedef struct info
{
	int argc;
    char argv[100];
} info_t;

typedef struct list
{
    int readfd;
} list_t;

int calculate_age(int birth_year);
const char *get_age_group(int age);
int main(void);
int is_interactive(info_t *info);
int is_separator(char c, char *delimiters);
int is_alpha_character(int c);
int string_to_integer(char *s);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
void remove_comments(char *buf);
void free_args(char **av);
void print_prompt(void);
char *_getenv(const char *name, char **e);
void execute_exit(int status, char **av, char *line);
void ignore_comments(char *lineptr);

char *convert_number(int n, int base, int upper_o_n);
int replace_variables(char **args, int s);

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\n'

#endif
