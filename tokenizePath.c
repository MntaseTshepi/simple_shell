#include "shell.h"

/**
 * tokenizePath - Tokenizes each directory in the environment variable PATH
 * Return: Full path
 */

char **tokenizePath()
{
	char *variable = "PATH", *value = getenv(variable), *tokens;
	const char *delim = ":";
	int num_token = 0, i = 0;
	char *value_cpy = NULL, *val_copy = NULL, **PATH;

	value_cpy = _strdup(value);
	if (value_cpy == NULL)
	{
		perror("sh: memory allocation failed");
		exit(EXIT_FAILURE);
	}
	tokens = strtok(value_cpy, delim);
	while (tokens != NULL)
	{
		num_token++;
		tokens = strtok(NULL, delim);
	}
	num_token++;
	PATH = malloc(sizeof(char *) * num_token);
	if (PATH == NULL)
	{
		perror("sh: memory allocation failed");
		free(PATH);
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
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
/**
 * findCommandPath - Finds the command path.
 * @pathTokens: Token parameters.
 * @command: command parameter.
 * Return: commandPath
 */
char *findCommandPath(char **pathTokens, char *command)
{
	char *commandPath = NULL;
	size_t commandLen = _strlen(command);
	size_t pathLen;
	size_t fullPathLen;
	int i;
	char *fullPath = NULL;

	for (i = 0; pathTokens[i] != NULL; i++)
	{
		pathLen = _strlen(pathTokens[i]);
		fullPathLen = pathLen + commandLen + 2;
		fullPath = malloc(fullPathLen);
		if (fullPath == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		_strcpy(fullPath, pathTokens[i]);
		_strcat(fullPath, "/");
		_strcat(fullPath, command);
		if (access(fullPath, X_OK) == 0)
		{
			commandPath = fullPath;
			break;
		}
		free(fullPath);
	}
	return (commandPath);
}
/**
 * freeTokenizedPath - Frees tokenized path
 * @pathTokens: Tokens parameters.
 * Return: Void
 */
void freeTokenizedPath(char **pathTokens)
{
	int i;

	if (pathTokens == NULL)
	{
		return;
	}

	for (i = 0; pathTokens[i] != NULL; i++)
	{
		free(pathTokens[i]);
	}
	free(pathTokens);
}
/**
 * getCommandPath - Gets the full file path.
 * @command: command parameter.
 * Return: Full path
 */
char *getCommandPath(char *command)
{
	char **pathTokens = tokenizePath();
	char *commandPath = findCommandPath(pathTokens, command);

	freeTokenizedPath(pathTokens);
	return (commandPath);
}
