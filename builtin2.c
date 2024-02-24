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
if (access(commands, X_OK) == 0)
{
/*command exists and is exe fork and execv*/
pid_t pid = fork();
if (pid < 0)
{
/*fork error*/
perror("Error: Unable to fork process");
}
else if (pid == 0)
{
/* child process */
char *args[] = {commands, NULL};
execv(args[0], args);

/*Error if execv returns*/
perror("execv");
exit(EXIT_FAILURE);
}
else
{
/*Parent process*/
wait(NULL);
}
}
else
{
write(STDOUT_FILENO, "Invalid command\n", 16);
}

}
return (NULL);
}

