#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exitcheck;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = atoi(info->argv[1]);
        if (exitcheck == 0 && info->argv[1][0] != '0')
        {
            info->status = 2;
            printf("Illegal number: %s\n", info->argv[1]);
            return 1;
        }
        info->status = exitcheck;
        return exitcheck;
    }

    return 0;
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        printf("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            printf("%s\n", s);
            return 1;
        }
        printf("%s\n", _getenv(info, "OLDPWD="));
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        printf("can't cd to %s\n", info->argv[1]);
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * _myhelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    printf("Help information:\n");
    printf("This is a placeholder function. Help information is not yet available.\n");
    if (0)
        printf("%s\n", *arg_array); /* temp att_unused workaround */
    return 0;
}

