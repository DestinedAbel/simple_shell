#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "shell.h"
/**
 * convert_number - converts an integer to a specific base
 * @n: the giving integer
 * @base: the base to be converted to
 * @upper_o_n: indicates if output upper or lower case
 * Return: the conversion string
 */
char *convert_number(int n, int base, int upper_o_n)
{
	static char *base_digits;
	static char buffer[50];
	char *p_convert;

	base_digits = upper_o_n ? "0123456789ABCDEF" :
			"0123456789abcdef";

	p_convert = &buffer[49];
	*p_convert = '\0';

	do {
		*--p_convert = base_digits[n % base];
		n /= base;
	} while (n != 0);
	return (p_convert);
}

/**
 * replace_variables - handle variables
 * @args: an array of pointers to arguments
 * @e: an array of environment variables
 * @s: the previous status
 * Return: 0 Success
 */
int replace_variables(char **args, int s)
{
	int i;
	char *value;
	char cwd[1024];

	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i][0] == '$' && args[i][1] == '\0')
			continue;
		else if (strcmp(args[i], "$?") == 0)
		{
			free(args[i]);
			args[i] = strdup(convert_number(s, 10, 0));
			continue;
		}
		else if (strcmp(args[i], "$$") == 0)
		{
			free(args[i]);
			args[i] = strdup(convert_number(getpid(), 10, 0));
			continue;
		}
		else if (args[i][0] == '$')
		{
			value = getenv(&args[i][1]);
			free(args[i]);
			if (value)
			{
				args[i] = strdup(value);
				continue;
			}
			args[i] = strdup("");
		}
		else if (strcmp(args[i], "$PWD") == 0)
		{
			free(args[i]);
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				args[i] = strdup(cwd);
				continue;
			}
			else
			{
				perror("getcwd error");
				args[i] = strdup("");
			}
		}
	}
	return (0);
}

