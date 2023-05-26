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
	else if (strcmp (command, "exit") == 0)
	{
		if (argv[1] != NULL)
		{
			_printexit(status, argv);
		}
		else
		{
			exit(status);
		}
	}
	else if (strcmp (command, "echo") == 0)
	{
		for (i = 1; argv[i] != NULL; i++)
		{
			len = strlen(argv[i]);
			if(write(STDOUT_FILENO, argv[i], len) == -1 || 
					write(STDOUT_FILENO, " ", 1) == - 1)
			{
				write(STDERR_FILENO, "Error writing to stdout\n", 24);
				exit(EXIT_FAILURE);
			}
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			write(STDERR_FILENO, "Error writing to stdout\n", 24);
			exit(EXIT_FAILURE);
		}
	}
	else if (strcmp(command, "setenv") == 0)
		setenv_function(argv);
	else if (strcmp(command, "unsetenv") == 0)
		unsetenv_function(argv);
	else if (strcmp(command, "cd") == 0)
		cd_builtin(argv);
	else
	{
		write(STDERR_FILENO, "Unrecognized command:", 22);
		write(STDERR_FILENO, command, strlen(command));
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_external_command - executes binary files
 * @command: Command parameter
 * @argv: argv parameter
 * Return: Void
 *
 */

void execute_external_command(char* command, char** argv)
{
	pid_t pid = fork();
	int status;
	char which_command[512];
	char result[256];
	char* result_ptr;
	char* path = NULL;
	FILE* which_output;
	size_t result_length;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		strcpy(which_command, "which ");
		strcat(which_command, command);
		strcat(which_command, " 2>/dev/null");

		which_output = popen(which_command, "r");
		if (which_output == NULL)
		{
			perror("popen");
			exit(EXIT_FAILURE);
		}
		result_ptr = fgets(result, sizeof(result), which_output);
		pclose(which_output);
		if (result_ptr == NULL)
		{
			write(STDERR_FILENO, "Command not found: ", 19);
			write(STDERR_FILENO, command, strlen(command));
			write(STDERR_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}
		result_length = strlen(result);
		if (result_length > 0 && result[result_length - 1] == '\n')
		{
			result[result_length - 1] = '\0';
		}
		path = malloc(strlen(result) + 1);
		if (path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcpy(path, result);
		argv[0] = path;
		execve(path, argv, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (path != NULL)
		{
			free(path);
		}
	}
}
