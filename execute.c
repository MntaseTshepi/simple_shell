#include "myshell.h"

/**
 * execute_command - Function checks if command is a builtin or executable.
 * @argv: Argument vectors
 * Return: Void
 */

void execute_command(char **argv)
{
	char *command;

	command = argv[0];

	if (command == NULL)
	{
		return;
	}
	if (is_builtin(command) == 1)
	{
		execute_builtin_command(command, argv);
	}
	else
	{
		execute_binary_command(command, argv);
	}
}

/**
 * is_builtin - Function checks for builtin commands.
 * @command: Command input
 * Return: 1 on success or 0 on failure
 */

int is_builtin(char *command)
{
	const char *builtins[] = {"printenv", "env", "exit", "echo"};
	size_t num_builtins, i;

	num_builtins = sizeof(builtins) / sizeof(builtins[0]);

	for (i = 0; i < num_builtins; i++)
	{
		if (_strcmp(command, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _printenviron - Function prints out the current environment.
 * Return: Void
 */

void _printenviron(void)
{
	int i;
	char **env = environ;

	for (i = 0; env[i]; i++)
	{
		printf("%s\n", env[i]);
	}
}

/**
 * execute_builtin_command - Function executes the builtin command.
 * @command: Command input.
 * @argv: Argument vectors.
 * Return: Void
 */

void execute_builtin_command(char *command, char **argv)
{
	int i;
	size_t len;

	if (_strcmp(command, "env") == 0 || _strcmp(command, "printenv") == 0)
	{
		_printenviron();
	}
	if (_strcmp(command, "exit") == 0)
	{
		_printexit();
	}
	if (_strcmp(command, "echo") == 0)
	{
		for (i = 1; argv[i] != NULL; i++)
		{
			len = _strlen(argv[i]);
			write(STDOUT_FILENO, argv[i], len);
			write(STDOUT_FILENO, " ", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * execute_binary_command- Function executes commands in the binary file.
 * @command: Command input
 * @argv: Argument vectors
 * Return: Void
 */

void execute_binary_command(char *command, char **argv)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = actual_path(command);

	if (access(full_path, X_OK) != 0)
	{
		perror(command);
		free(full_path);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(command);
	}
	else if ((pid == 0))
	{
		if (execve(full_path, argv, NULL) == -1)
		{
			perror(command);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror(command);
		}
	}
	free(full_path);
}
