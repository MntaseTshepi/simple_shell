#include "shell.h"

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
