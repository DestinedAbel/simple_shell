#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * print_prompt - prints the prompt string
 */
void print_prompt(void)
{
    if (isatty(STDIN_FILENO) == 1)
        write(STDOUT_FILENO, "$ ", 2);
}

/**
 * free_args - free an array of string
 * @av: an array of strings
 */
void free_args(char **av)
{
    char **ptr = av;

    while (*ptr)
    {
        free(*ptr);
        ptr++;
    }
    free(av);
}

/**
 * _getenv - gets an environment variable
 * @name: the environment variable name
 * Return: the environment variable value
 */
char *_getenv(const char *name)
{
    extern char **environ;
    char *variable, *token, *path;
    char **envp = environ;

    while (*envp)
    {
        variable = malloc(strlen(*envp) + 1);
        if (variable == NULL)
            return NULL;
        strcpy(variable, *envp);
        token = strtok(variable, "=");
        if (token != NULL && strcmp(token, name) == 0)
        {
            token = strtok(NULL, "\0");
            path = malloc(strlen(token) + 1);
            if (path == NULL)
                return NULL;
            strcpy(path, token);
            free(variable);
            return path;
        }
        envp++;
        free(variable);
    }
    return NULL;
}

/**
 * execute_exit - launch exit command
 * @status: the exit status
 * @av: an array of arguments
 * @line: the line
 */
void execute_exit(int status, char **av, char *line)
{
    free_args(av);
    free(line);
    if (status == 200)
        exit(0);
    exit(status);
}

/**
 * ignore_comments - ignore the comments
 * @lineptr : the giving string
 */
void ignore_comments(char *lineptr)
{
    int i;

    for (i = 0; lineptr[i] != '\0'; i++)
    {
        if (lineptr[i] == '#' && (i == 0 || lineptr[i - 1] == ' '))
        {
            lineptr[i] = '\0';
            return;
        }
    }
}

