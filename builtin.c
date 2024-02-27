#include "main.h"

/**
 * commands_arguments - Tokenize a string into an array of arguments.
 * @commands: The string to be tokenized.
 *
 * Return: A dynamically allocated array of arguments (strings).
 */

char **commands_arguments(char *commands)
{
	char **args = malloc(100 * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	args_index = 0;

	token = strtok(commands, " ");

	while (token != NULL && args_index < 99)
	{

		args[args_index] = strdup(token);

		if (args[args_index] == NULL)
		{
			perror("strdup");
			for (i = 0; i < args_index; i++)
			{
				free(args[i]);
			}
			free(args);
			exit(EXIT_FAILURE);
		}
		args_index++;
		token = strtok(NULL, " ");
	}
	args[args_index] = NULL;

	return (args);
}

/**
 * env_command - Display the environment variables.
 * @commands: input commands.
 *
 * Return: Nothing.
 */

void env_command()
{
	if (environ == NULL)
	{
		perror("environ");
	}
	for (env = environ; *env != NULL; env++)
	{
		size_t len = 0;
		while ((*env)[len] != '\0')
		{
			len++;
		}

		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * my_strcmp - Compare two strings for equality.
 * @string1: The first string to compare.
 * @string2: The second string to compare.
 *
 * Return: 1 if strings are equal, 0 otherwise.
 */

bool my_strcmp(const char *string1, const char *string2)
{
	while (*string1 != '\0' && *string2 != '\0')
	{
		if (*string1 != *string2)
			return (false);
		string1++;
		string2++;
	}

	return (*string1 == *string2);
}

/**
 * get_path - Get the directory path of the currently executing program.
 *
 * Return: A dynamically allocated string containing the directory path.
 *         NULL on failure.
 */

char *get_path(void)
{
	char *path = getenv("PATH");
	if (path == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}

	return (path);
}

/**
 * handle_path - Execute a command by searching for its executable in the PATH.
 * @commands: The command to be executed, along with any arguments.
 *
 * Return: NULL on success, or an error message on failure.
 */

void handle_path(char *commands)
{
	char *path = get_path();
	char *path_copy = strdup(path);
	char *token_path = strtok(path_copy, ":");

	while (token_path != NULL)
	{
		if (token_path != NULL && commands != NULL)
		{
			char *full_path = malloc(strlen(token_path) + strlen(commands) + 2);

			if (full_path == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}

			strcpy(full_path, token_path);
			strcat(full_path, "/");
			strcat(full_path, commands);

			if (access(full_path, X_OK) == 0)
			{

				/*The command exists at this path*/

				char **args = commands_arguments(commands);
				execve(full_path, args, environ);
				perror("execve");
				for (k = 0; k < args_index; k++)
				{
					free(args[k]);
				}
				free(args);
			}

			free(full_path);
			token_path = strtok(NULL, ":");
		}

		/* the command not found in path */

		write(STDOUT_FILENO, "Command not found\n", 18);

		free(path_copy);
	}
}
