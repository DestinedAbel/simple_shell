#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_prompt - prints the prompt string
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * free_args - free an array of strings
 * @av: an array of strings
 */
void free_args(char **av)
{
	int i = 0;

	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
}

/**
 * _getenv - gets an environment variable
 * @name: the environment variable name
 * @e: an array of environment variables
 * Return: the environment variable value
 */
char *_getenv(const char *name, char **e)
{
	int i = 0;
	size_t name_len = strlen(name);

	while (e[i] != NULL)
	{
		if (strncmp(e[i], name, name_len) == 0 && e[i][name_len] == '=')
			return &(e[i][name_len + 1]);
		i++;
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
	_exit(status);
}

/**
 * ignore_comments - ignore the comments
 * @lineptr : the given string
 */
void ignore_comments(char *lineptr)
{
	char *comment_pos = strchr(lineptr, '#');
	if (comment_pos != NULL)
		*comment_pos = '\0';
}

