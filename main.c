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
			/* command not found */
			write(STDERR_FILENO, result, strlen(result));
			continue;
		}

		/*handle env*/
		input[strcspn(input, "\n")] = 0;
		if (strcmp(input, "env") == 0)
		{
			env_command(input);
		}
		
		/*handle commands*/


		free(input);
	}
}
