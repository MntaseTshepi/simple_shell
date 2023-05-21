#include "myshell.h"
/**
 * tokenizePath - Tokenizes each directory in the environment variable PATH
 * Return: Full path
 */
char **tokenizePath()
{
	char *variable = "PATH", *value = _getenv(variable), *tok;
	const char *del = ":";
	int num_token = 0, i = 0;
	char *value_cpy = NULL, *val_copy = NULL, **PATH;

	value_cpy = _strdup(value);
	if (value_cpy == NULL)
	{
		perror("sh: memory allocation failed");
		free(value_cpy);
		free(value);
		exit(EXIT_FAILURE);
	}
	for (tok = strtok(value_cpy, del); tok != NULL; tok = strtok(NULL, del))
	{
		num_token++;
	}
	PATH = malloc(sizeof(char *) * num_token + 1);
	if (PATH == NULL)
	{
		perror("sh: memory allocation failed");
		free(PATH);
		free(value_cpy);
	}
	val_copy = _strdup(value);
	tok = strtok(val_copy, del);
	for (i = 0; tok != NULL; i++)
	{
		PATH[i] = malloc(sizeof(char) * (_strlen(tok) + 1));
		if (PATH[i] == NULL)
		{
			perror("sh: memory allocation failed");
			free(PATH[i]);
		}
		_strcpy(PATH[i], tok);
		tok = strtok(NULL, del);
	}
	free(value_cpy);
	value_cpy = NULL;
	free(val_copy);
	val_copy = NULL;
	return (PATH);
}
