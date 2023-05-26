#include "shell.h"

/**
 * free_argv - free args vector
 * @argv: arguement parameter
 * Return: Void
 */

void free_argv(char **argv)
{
	int i;

	if (argv == NULL)
		return;
	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
		argv[i] = NULL;
	}
	free(argv);
	argv = NULL;
}

/**
 * main - main function
 * @ac: arguement count parameter
 * @argv: Arguement vector
 * Return: alway 0 on Success
 */

int main(int argc, char **argv)
{
	bool pipe = false;
	char *errorMessage = "Error parsing command.\n", *command = NULL;
	size_t command_size = 0;
	ssize_t num_chars = 0;
	FILE *file = NULL;

	if (argc > 1)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
	}
	while (1 && !pipe)
	{
		print_prompt();

		if (file)
		{
			num_chars = getline(&command, &command_size, file);
			if (num_chars == -1)
			{
				free(command);
				exit(0);
			}
		}
		else
		{
			num_chars = getline(&command, &command_size,stdin);
			if (num_chars == -1)
			{
				free(command);
				exit(0);
			}

		}
		if (num_chars == 0)
		{
			free(command);
			command = NULL;
			continue;
		}
		if (command[num_chars - 1] == '\n')
		{
			command[num_chars - 1] = '\0';
			num_chars--;
		}
		argv = parse_command(command, num_chars);
		if (argv == NULL)
		{
			write(STDERR_FILENO, errorMessage, strlen(errorMessage));
			free(command);
			command = NULL;
			continue;
		}
		execute_command(argv);
		free_argv(argv);
		free(command);
		command = NULL;
	}
	if (file)
	{
		fclose(file);
	}
	return (0);
}
