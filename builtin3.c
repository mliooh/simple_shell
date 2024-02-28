#include "main.h"

/**
 * update_pwd - Updates the PWD environment variable with the current working directory.
 */

void update_pwd()
{
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    if (setenv("PWD", cwd, 1) == -1)
    {
        perror("setenv");
        free(cwd);
        exit(EXIT_FAILURE);
    }

    free(cwd);
}

/**
 * cd_command - Implements the 'cd' command to change the current directory.
 * @directory: The target directory to change to, or NULL for the home directory.
 */

#include <unistd.h>

void cd_command(char *directory)
{
    char *home = getenv("HOME");

    if (directory == NULL || strcmp(directory, "~") == 0 || strcmp(directory, "") == 0)
    {
        /* if argument null, "~", or empty, change to home directory */
        char *message = "Changing to home directory: ";
        write(STDOUT_FILENO, message, strlen(message));
        write(STDOUT_FILENO, home, strlen(home));
        write(STDOUT_FILENO, "\n", 1);

        if (chdir(home) == -1)
        {
            perror("chdir");
        }
    }
    else
    {
        /* Change to the specified directory */
        char *newline = strchr(directory, '\n');
        if (newline)
            *newline = '\0';

        if (chdir(directory) == -1)
        {
            perror("chdir");
        }
    }

    /* Update the PWD and OLDPWD environment variables */
    update_pwd();
    setenv("OLDPWD", getenv("PWD"), 1);
}
