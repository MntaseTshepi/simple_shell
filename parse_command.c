#include "myshell.h"
/**
 * parse_command - parse the command
 * @command: command parameter
 * @num_chars: number of characters parameter
 * Return: Parsed code
 */
char **parse_command(char *command, ssize_t num_chars)
{
	int i = 0, num_token = 0;
	char **argv, *tokens, *command_cpy = NULL;
	const char *delim = " \n";

	command_cpy = malloc(num_chars + 1);
	if (command_cpy == NULL)
	{
		perror("sh: memory allocation failed");
		free(command_cpy);
		free(command);
		exit(EXIT_FAILURE);
	}
	_strcpy(command_cpy, command);
	tokens = strtok(command, delim);
	while (tokens != NULL)
	{
		num_token++;
		tokens = strtok(NULL, delim);
	}
	argv = malloc(sizeof(char *) * num_token);
	if (argv == NULL)
	{
		perror("tsh: memory allocation failed");
		free(argv);
		free(command_cpy);
		free(command);
	}
	tokens = strtok(command_cpy, delim);
	for (i = 0; tokens != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * _strlen(tokens) + 1);
		if (argv[i] == NULL)
		{
			perror("sh: memory allocation failed");
			free(argv[i]);
		}
		_strcpy(argv[i], tokens);
		tokens = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(command_cpy);
	command_cpy = NULL;
	return (argv);
}
