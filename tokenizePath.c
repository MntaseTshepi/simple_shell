#include "myshell.h"
/**
 * tokenizePath - Tokenizes each directory in the environment variable PATH
 * Return: Full path
 */
char **tokenizePath()
{
	char *variable = "PATH", *value = _getenv(variable), *tok;
	const char *del = ":";
	int num_token = 0, i;
	char *value_cpy = _strdup(value), *val_copy = NULL, **PATH = NULL;

	if (value_cpy == NULL)
	{
		perror("sh: memory allocation failed");
		exit(EXIT_FAILURE);
	}
	for (tok = strtok(value_cpy, del); tok != NULL; tok = strtok(NULL, del))
		num_token++;
	PATH = malloc(sizeof(char *) * (num_token + 1));
	if (PATH == NULL)
	{
		perror("sh: memory allocation failed");
		free(PATH);
		exit(EXIT_FAILURE);
	}
	val_copy = _strdup(value);
	tok = strtok(val_copy, del);
	for (i = 0; tok != NULL; i++)
	{
		PATH[i] = _strdup(tok);
		if (PATH[i] == NULL)
		{
			perror("sh: memory allocation failed");
			while (i-- > 0)
				free(PATH[i]);
			free(PATH);
			free(value_cpy);
			free(val_copy);
			exit(EXIT_FAILURE);
		}
		tok = strtok(NULL, del);
	}
	PATH[i] = NULL;
	free(value_cpy);
	free(val_copy);
	return (PATH);
}
