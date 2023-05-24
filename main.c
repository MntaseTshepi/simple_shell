#include "myshell.h"

/**
 * main - main function
 * @ac: argument count parameter
 * @argv: argument vector parameter
 * Return: Always 0 (success)
 */

int main(int ac, char **argv)
{
	bool pipe;
	int i = 0;
	char *command = NULL;
	size_t command_size = 0;
	ssize_t num_chars;

	(void)ac;
	pipe = false;

	while (1 && !pipe)
	{
		print_prompt();
		if (isatty(STDIN_FILENO) == 0)
		{
			pipe = true;
		}
		num_chars = getline(&command, &command_size, stdin);
		if (num_chars == -1)
		{
			free(command);
			exit(0);
		}
		argv = parse_command(command, num_chars);
		execute_command(argv);
		if (argv != NULL)
		{
			for (i = 0; argv[i] != NULL; i++)
			{
				free(argv[i]);
				argv[i] = NULL;
			}
			free(argv);
			argv = NULL;
		}
	}
	free(command);
	command = NULL;
	return (0);
}
