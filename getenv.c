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

/**
 * setenv_function - used to modify or initialize environment
 * @argv: argument vectors parameter
 * Return: void
*/

void setenv_function(char **argv)
{
	char *variable, *value;

	variable = argv[1];
	value = argv[2];

	if (variable == NULL || value == NULL)
	{
		write(STDERR_FILENO, "setenv: Missing variable or value\n\n", 34);
		return;
	}
	else if (setenv(variable, value, 1) == -1)
	{
		perror("setenv fail");
		return;
	}
	else
	{
		return;
	}
}
/**
 * unsetenv_function - Function removes an environment variable.
 * @argv: Argument vectors
 * Return: Void
 */
void unsetenv_function(char **argv)
{
	char *variable;

	variable = argv[1];

	if (variable == NULL)
	{
		write(STDERR_FILENO, "unsetenv: Missing variable\n\n", 28);
		return;
	}
	if (unsetenv(variable) == -1)
	{
		perror("unsetenv");
		return;
	}
}
/**
 * cd_builtin - changes directory builtin
 * @argv: arguements parameter
 * Return: void
*/

void cd_builtin(char **argv)
{
	char *path = argv[1];
	char *home = getenv("HOME");
	char *current_dir = getenv("PWD");
	char cwd[1024];

	if (path == NULL)
	{

		if (home == NULL)
		{
			write(STDERR_FILENO, "cd: No home directory found\n", 28);
			return;
		}
		path = home;
	}
	else if (strcmp(path, "-") == 0)
	{

		if (current_dir == NULL)
		{
			write(STDERR_FILENO, "cd: No previous directory\n", 26);
			return;
		}
		path = current_dir;
	}

	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, "error", 6);
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		perror("getcwd");
}

