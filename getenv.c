#include "shell.h"
#include <string.h>


/**
 * _getenv - Function gets environment variable
 * @name: Input parameter.
 * Return: Environment variable.
 */

char *_getenv(const char *name)
{
	char **env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=')
		{
			return (&(*env)[strlen(name) + 1]);
		}
		env++;
	}

	return (NULL);
}

/**
 * _printexit - prints exit with status
 * @status: parameter
 * @argv: argv parameter
 * Return: Void
 */

void _printexit(int status, char **argv)
{
	status = atoi(argv[1]);
	exit(status);
}
