#include "myshell.h"
/**
 * actual_path - give full path of command
 * @command: command parameter
 * Return: full path
 */
char *actual_path(char *command)
{
	struct stat buffer;
	char **path_tokens = tokenizePath();
	char *file_path = NULL;
	int i = 0;
	int directory_length;
	int command_length;

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
				break;
			}
			_strcpy(file_path, path_tokens[i]);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			if (stat(file_path, &buffer) == 0)
				break;
			free(file_path);
			file_path = NULL;
			i++;
		}
		free(path_tokens);
	}
	if (file_path == NULL && stat(command, &buffer) == 0)
	{
		file_path = _strdup(command);
	}
	return (file_path);
}
