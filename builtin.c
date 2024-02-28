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

	int index = 0;

	token = strtok(commands, " ");
	while (token != NULL)
	{
		args[index] = token;
		index++;
		token = strtok(NULL, " ");
	}
	args[index] = NULL;
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
	env = environ;
	while (*env != NULL)
	{
		current = 0;

		while ((*env)[current] != '\0')
		{
			current++;
		}
		
		write(STDOUT_FILENO, *env, current);
        write(STDOUT_FILENO, "\n", 1);
        env++;
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

char *handle_path(char *commands)
{
	if (commands == NULL)
	{
		perror("Error: NULL command");
	}

	path = getenv("PATH");

	if (path == NULL)
	{
		perror("Error: PATH environment variable not found");
	}

	token_path = strtok(path, ":");

	while (token_path != NULL)
	{
		char *full_path = malloc(strlen(token_path) + strlen(commands) + 2);

		if (full_path == NULL)
		{
			perror("Error: Unable to allocate memory for full_path");
			exit(EXIT_FAILURE);
		}

		strcpy(full_path, token_path);
		strcat(full_path, "/");
		strcat(full_path, commands);

		if (access(commands, X_OK) == 0)
		{
			/* command exists and is exeutable */
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("Fork failed");
				free(full_path);
			}

			else if (pid == 0)
			{
				/*child process*/
				char **args = commands_arguments(full_path);

				if (args == NULL)
				{
					perror("Error: Unable to tokenize command");
					free(full_path);
					exit(EXIT_FAILURE);
				}

				execv(args[0], args);

				perror("execve");
				free(full_path);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, NULL, 0);
				free(full_path);
				return (NULL);
			}
		}
		free(full_path);
		token_path = strtok(NULL, ":");
	}

	perror("Error: Command not found in PATH");
	return (NULL);
}
