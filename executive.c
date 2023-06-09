#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"

/**
 * sigign - prints a new line when a signal SIGINT is sent
 * @signal: the sent signal
 */
void sigign(int signal)
{
    if (signal == SIGINT)
        write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * execmd - executes the giving command
 * @exe: executable name
 * @av: an array of arguments
 * @e: an array of environment variables
 * Return: status code
 */
int execmd(char *exe, char **av, char **e)
{
    pid_t child;
    int st;
    char *path, *cmd;

    if (av)
    {
        path = _getenv("PATH");
        cmd = _which(av[0], path);
        if (cmd)
        {
            child = fork();
            if (child == -1)
            {
                print_error(exe, "Fork fails");
                return (1);
            }
            else if (child == 0)
            {
                if (execve(cmd, av, e) == -1)
                {
                    perror(exe);
                    exit(errno);
                }
            }
            wait(&st);
            free(path);
            free(cmd);
            return (WEXITSTATUS(st));
        }
        free(path);
        free(cmd);
        return (print_cmd_not_found(exe, av));
    }
    return (0);
}

/**
 * print_error - print error message
 * @exe: executable name
 * @desc: error message
 */
void print_error(char *exe, char *desc)
{
    char *error;

    error = malloc(strlen(exe) + strlen(desc) + 5);
    if (error == NULL)
    {
        write(STDERR_FILENO, "Not enough space", 16);
        return;
    }
    strcpy(error, exe);
    strcat(error, ": ");
    strcat(error, desc);
    strcat(error, "\n\0");
    write(STDERR_FILENO, error, strlen(error));
    free(error);
}

/**
 * print_cmd_not_found - prints command not found error
 * @exe: executable name
 * @av: an array of pointers to arguments
 * Return: 127
 */
int print_cmd_not_found(char *exe, char **av)
{
    char *error;

    error = malloc(strlen(exe) + strlen(av[0]) + 24);
    if (error == NULL)
    {
        write(STDERR_FILENO, "Not enough space", 16);
        return (1);
    }
    strcpy(error, exe);
    strcat(error, ": ");
    strcat(error, av[0]);
    strcat(error, ": ");
    strcat(error, "command not found");
    strcat(error, "\n\0");
    write(STDERR_FILENO, error, strlen(error));
    free(error);
    return (127);
}

