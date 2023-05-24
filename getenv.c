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
		if (_strncmp(*env, name, _strlen(name)) == 0 && (*env)[_strlen(name)] == '=')
		{
			return (&(*env)[_strlen(name) + 1]);
		}
		env++;
	}

	return (NULL);
}
