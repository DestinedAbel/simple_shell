#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: pointer to the info struct
 * @info_t: pointer
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

#define MAX_INPUT_LENGTH 100
#define MAX_COMMAND_LENGTH 50

int is_interactive(info_t *info);

int is_interactive(info_t *info)
{
	info_t *info;
    info->readfd = 1;

	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return 1;
	else
		return 0;
}

/**
 * is_separator - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_separator(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters == c)
			return 1;
		delimiters++;
	}
	return 0;
}

/**
 * is_alpha_character - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha_character(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int string_to_integer(char *s)
{
	int sign = 1;
	int result = 0;
	int i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}

    for (; s[i] != '\0'; i++)
    {
	    if (s[i] >= '0' && s[i] <= '9')
	    {
		    result = (result * 10) + (s[i] - '0');
	    }
	    else
	    {
		    return 0;
	    }
    }
    
    return sign * result;
}

extern char **environ;

int main(void)
{
    	char command[MAX_COMMAND_LENGTH];
	pid_t pid;
    	pid = fork();
	 size_t command_length;


    while (1) 
    {
        printf("Shell> ");

        if (fgets(command, sizeof(command), stdin) == NULL) 
	{
            printf("\n");
            break;
        }

        size_t command_length = strlen(command);

        if (command[command_length - 1] == '\n') 
	{
            command[command_length - 1] = '\0'; 
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) 
	{
            char *args[] = {command, NULL};
            execve(command, args, environ);

            perror("exec error");
            exit(EXIT_FAILURE);
        } 
	else 
	{
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Child process exited with status: %d\n", exit_status);
            } else if (WIFSIGNALED(status)) {
                int signal_number = WTERMSIG(status);
                printf("Child process terminated by signal: %d\n", signal_number);
            }
        }

        printf("\n");
    }

    return 0;
}
