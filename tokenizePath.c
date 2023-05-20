#include "myshell.h"
/**
 * tokenizePath - Tokenizes each directory in the environment variable PATH
 * Return: Full path
 */
char **tokenizePath()
{
	char *variable = "PATH", *value = _getenv(variable), *tokens;
	const char *delim = ":";
	int num_token = 0, i = 0;
	char *value_cpy = NULL, *val_copy = NULL, **PATH;

	value_cpy = _strdup(value);
	if (value_cpy == NULL)
	{
		perror("sh: memory allocation failed");
		free(value_cpy);
		exit(EXIT_FAILURE);
	}
	for (tokens = strtok(value_cpy, delim); tokens != NULL; tokens = strtok(NULL, delim))
	{
		num_token++;
	}
	PATH = malloc(sizeof(char *) * num_token);
	if (PATH == NULL)
	{
		perror("sh: memory allocation failed");
		free(PATH);
	}
	val_copy = _strdup(value);
	tokens = strtok(val_copy, delim);
	for (i = 0; tokens != NULL; i++)
	{
		PATH[i] = malloc(sizeof(char) * (_strlen(tokens) + 1));
		if (PATH[i] == NULL)
		{
			perror("sh: memory allocation failed");
			free(PATH[i]);
		}
		_strcpy(PATH[i], tokens);
		tokens = strtok(NULL, delim);
	}
	free(value_cpy);
	value_cpy = NULL;
	free(val_copy);
	val_copy = NULL;
	return (PATH);
}
