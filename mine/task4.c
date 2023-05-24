#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return 0;
}
/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;

    while (node)
    {
        if (_starts_with(node->str, name))
            return node->str;
        node = node->next;
    }
    return NULL;
}
/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc <= 1)
    {
        printf("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
    {
        if (_unsetenv(info, info->argv[i]) != 0)
        {
		printf("Failed to unset environment variable: %d\n", info->argv[100]);
        }
    }

    return 0;
}
/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i = 0;

    while (environ[i] != NULL)
    {
        add_node_end(&node, environ[i], 0);
        i++;
    }

    info->env = node;
    return 0;
}

