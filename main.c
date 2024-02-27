#include "main.h"

/**
 * main - shell initialisation
 * Return: Always 0.
 */

int main(void)
{

	/* loop to prompt the user for input and shell initialisation*/
	while (1)
	{
		const char prompt[] = "shell$ ";

		ssize_t initial_prompt = write(STDOUT_FILENO, prompt, strlen(prompt));

		if (initial_prompt < 0)
		{
			perror("Error printing prompt");
			exit(EXIT_FAILURE);
		};

		input = user_input();

		if (input == NULL)
		{
			/*newline after EOF */
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}

		/* Check if the command exists */

		result = command_exists(input);

		if (result == NULL)
		{
			if (strcmp(input, "env\n") == 0)
			{
				env_command();
			}
			else if (strncmp(input, "cd", 2) == 0)
			{
				char *space_pos = strchr(input, ' ');

				/* Check if there is a space after "cd" */
				if (space_pos != NULL)
				{
					char *directory = space_pos + 1;
					cd_command(directory);
				}
				else
				{
					/* If no space after "cd", change to home directory */
					cd_command(NULL);
				}
			}
		}
		else
		{
			/* command not found */
			write(STDERR_FILENO, result, strlen(result));
		}

		/* Free the input after processing */
		free(input);
	}
}
