#include "main.h"

/**
 * user_input - function to take input
 * capture users input commands
 * @commands: user input commands
 * Return: User input commands or NULL on EOF or error.
 */

char *user_input()
{
	char *commands = NULL;

	size_t len;
	ssize_t read = getline(&commands, &len, stdin);
	/*error handling*/
	if (read == -1)
	{
		/*EOF or error occured*/
		free(commands);
		return (NULL);
	}
	/* handle exit*/
	if (exit_command(commands) == 1)
	{
		exit(EXIT_FAILURE);
	}
	/*(else if (strcmp(commands, "env") == 0)
	{
		write(STDOUT_FILENO, "t", 1);
	}*/
	return (commands);
}

/**
 * exit_command - function to check for exit command from user input
 * @commands: - user input command
 * Return: 1 if the command is the exit command 0 if not
 *
 * EXIT_COMMAND "exit\n". It iterates through the characters of both strings,
 */
int exit_command(const char *commands)
{
	const char EXIT_COMMAND[] = "exit";

	size_t i;
	bool is_digit = true;
	int exit_code = 0;

	for (i = 0; EXIT_COMMAND[i] != '\0'; i++)
	{
		/* Not equal */
		if (commands[i] != EXIT_COMMAND[i])
		{
			return (0);
		}
		/*handle exit argements by checking if [i] is " " and convert to int*/
		if (commands[i] == ' ')
		{
			size_t j;
			const char *exit_argument = &commands[i + 1];

			for (j = 0; exit_argument[j] != '\0'; j++)
			{
				/*Check if the character is a digit*/
				if (exit_argument[j] >= '0' && exit_argument[j] <= '9')
				{
					/*Convert the character to an integer and add it to exit_code*/
					exit_code = exit_code * 10 + (exit_argument[j] - '0');
				}
				else
				{
					/*if exit_code is not an int  */
					is_digit = false;
					break;
				}
				if (!is_digit || exit_code < 0 || exit_code > 255)
				{
					write(STDOUT_FILENO, "invalid exit code\n", 18);
					exit_code = 2;
				}
			};
			/*end of commands string reached*/
			if (commands[i] != '\0')
			{
				return (0);
			}
		};
		return (1);
	};
	exit(exit_code);
}

/**
 * command_exists - Checks if a command exists and is executable.
 * @commands: The command to check for existence.
 *
 * Return: If the command exists and is executable, returns a pointer to
 *         the full path of the command. If the command does not exist or
 *         is not executable, prints an error message and returns NULL.
 */

char *command_exists(char *commands)
{
	if (commands != NULL)
	{
		args = malloc(2 * sizeof(char *));

		if (args == NULL)
		{
			perror("Error allocating memory");
			exit(EXIT_FAILURE);
		}
		args[0] = commands;
		args[1] = NULL;

		/*command exists and is exe fork and execv*/
		pid = fork();
		if (pid < 0)
		{
			/*fork error*/
			free(args);
			perror("Error: Unable to fork process");
			return "Error: Unable to fork process";
		}
		else if (pid == 0)
		{
			/* child process */

			execv(args[0], args);

			/*Error if execv returns*/
			perror("Error");
			free(args);
			exit(EXIT_FAILURE);
		}
		else
		{
			/*Parent process*/
			int status;
			waitpid(pid, &status, 0);
			free(args);

			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{
					/* The command did not execute successfully */
					char error_message[100];
					snprintf(error_message, sizeof(error_message), "Error: Command returned exit status %d\n", exit_status);
					return strdup(error_message);
				}
			}
		}
	}

	return (NULL);
}
