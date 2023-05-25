#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h> 
#include <dirent.h>
#include "shell.h"

/**
 * buildPath - build the command path
 * @dirPath: the given directory path
 * @cmd: the given command
 * @path: the command path
 */
void buildPath(char *dirPath, char *cmd, char *path)
{
    strcpy(path, dirPath);
    strcat(path, "/");
    strcat(path, cmd);
    path[strlen(dirPath) + strlen(cmd) + 1] = '\0';
}

/**
 * _which - locate a command
 * @cmd: the given command
 * @envPath: the value of the PATH environment variable
 * Return: the path of the command or NULL if it doesn't exist
 */
char *_which(char *cmd, char *envPath)
{
    char *path, *token = NULL, *copyPath;
    struct stat st;

    if (stat(cmd, &st) == 0)
    {
        path = malloc(strlen(cmd) + 1);
        strcpy(path, cmd);
        return path;
    }
    copyPath = malloc(strlen(envPath) + 1);
    if (!copyPath)
        return NULL;
    strcpy(copyPath, envPath);
    /* store the dir path in an array */
    token = strtok(copyPath, ":");
    while (token)
    {
        path = malloc(strlen(token) + strlen(cmd) + 2);
        if (!path)
        {
            perror("malloc");
            free(copyPath);
            return NULL;
        }
        buildPath(token, cmd, path);
        if (stat(path, &st) == 0)
        {
            free(copyPath);
            return path;
        }
        token = strtok(NULL, ":");
        free(path);
    }
    free(copyPath);
    return NULL;
}

