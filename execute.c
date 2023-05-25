#include "shell.h"

/**
 * execute_command - checks if a command is a builtin or binary
 * @argv: arguement parameter
 * Return: Void
 */

void execute_command(char **argv)
{
	char *command;
	
	command = argv[0];
	if (command == NULL)
	{
		free(command);
		return;
	}
	if (is_builtin(command) == 1)
	{
		execute_builtin_command(command, argv);
	}
	else
	{
		execute_external_command(command, argv);
	}
}

/**
 * is_builtin - checks if a command is a builtin or not
 * @command: command parameter
 * Return: 1 if builtin and 0 if not
 */

int is_builtin(char *command)
{
	const char *builtins[] = {"printenv", "env", "exit", "echo", "cd",
	"unsetenv", "setenv"};
	size_t num_builtins, i;
	
	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	for (i = 0; i < num_builtins; i++)
	{
		if(strcmp(command, builtins[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * _printenviron - prints enviroment variable
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
 * execute_builtin_command - executes builtin commands
 * @command: command parameter
 * @argv: agrv pararmeter
 * Return: Void
 */

void execute_builtin_command(char *command, char **argv)
{
	int i, status = EXIT_SUCCESS;
	size_t len;
	
	if (strcmp(command, "env") == 0 || strcmp(command, "printenv") == 0)
	{
		_printenviron();
	}
	if (strcmp (command, "exit") == 0)
	{
		if (argv[1] != NULL)
		{
			_printexit(status, argv);
		}
		else
		{
			exit(0);
		}
	}
	if (strcmp (command, "echo") == 0)
	{
		for (i = 1; argv[i] != NULL; i++)
		{
			len = strlen(argv[i]);
			write(STDOUT_FILENO, argv[i], len);
			write(STDOUT_FILENO, " ", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	if (strcmp(command, "setenv") == 0)
		setenv_function(argv);
	if (strcmp(command, "unsetenv") == 0)
		unsetenv_function(argv);
	if (strcmp(command, "cd") == 0)
		cd_builtin(argv);
}

/**
 * execute_external_command - executes binary files
 * @command: Command parameter
 * @argv: argv parameter
 * Return: Void
 *
 */

void execute_external_command(char *command, char **argv)
{
	pid_t pid = fork();
	int status;
	char *full_path;
	char *errorMessage = "Error command.\n";
	
	if (strncmp(command, "/bin/", 5) == 0) 
	{
		if (access(command, X_OK) != 0)
		{
			perror(command);
			return;
		}
	}
	else
	{
		full_path = getCommandPath(command);
		if (full_path == NULL)
		{
			write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
			return;
		}
		if (access(full_path, X_OK) != 0)
		{
			perror(command);
			free(full_path);
			return;
		}
	}
	if (pid == -1)
	{
		perror(command);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (strncmp(command, "/bin/", 5) == 0)
		{
			if (execve(command, argv, NULL) == -1)
			{
				perror(command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execve(full_path, argv, NULL) == -1)
			{
				perror(command);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	if (strncmp(command, "/bin/", 5) != 0)
	{
		free(full_path);
	}
}
