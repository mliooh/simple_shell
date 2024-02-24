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

		char *input = user_input();

		if (input == NULL)
		{
			/*newline after EOF */
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}
		/* Check if the command exists */

		char *result = command_exists(input);

		if (result == NULL)
		{
			/* command not found */
			continue;
		}

		/*handle env*/
		env_command(input);
		/*handle commands*/
		write(STDOUT_FILENO, "we good\n", 8);

		free(input);
	}
}

