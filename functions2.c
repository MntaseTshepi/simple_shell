#include "myshell.h"

/**
 * _printexit - Function exits the shell.
 * @status: Exit status parameter
 * @argv: Args parameter
 * Return: void
 */

void _printexit(int status, char **argv)
{
	status = atoi(argv[1]);
	exit(status);
}

/**
 * _strncmp - Function compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * @n: Integer parameter.
 * Return: The compared string difference.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int u;
	size_t diff;

	for (u = 0; u < n; u++)
	{
		if (s1[u] == '\0' || s2[u] == '\0' || s1[u] != s2[u])
		{
			diff = s1[u] - s2[u];
			return (diff);
		}
	}
	return (0);
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
	char *home = _getenv("HOME");
	char *current_dir = _getenv("PWD");
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
	else if (_strcmp(path, "-") == 0)
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
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
	}
}

