#include "myshell.h"
/**
 * actual_path - give full path of command
 * @command: command parameter
 * Return: full path
 */
char *actual_path(char *command)
{
	struct stat buffer;
	char **path_tokens = tokenizePath(), *file_path;
	int i = 0, directory_length, command_length;

	command_length = _strlen(command);
	if (path_tokens != NULL)
	{
		while (path_tokens[i] != NULL)
		{
			directory_length = _strlen(path_tokens[i]);
			file_path = malloc(command_length + directory_length + 2);
			if (file_path == NULL)
			{
				perror("sh: memory allocation failed");
				free(file_path);
				free(path_tokens);
				exit(EXIT_FAILURE);
			}
			_strcpy(file_path, path_tokens[i]);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_tokens);
				return (file_path);
			}
			else
			{
				free(file_path);
				i++;
			}
		}
		free(path_tokens);
	}
	if (stat(command, &buffer) == 0)
	{
		return (command);
	}
	return (NULL);
}
