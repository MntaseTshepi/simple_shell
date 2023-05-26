#include "shell.h"
#include <stdbool.h>
#include <ctype.h>

/**
 * free_argv - frees argv
 * @argv: argv parameter
 * Return: Void
 */

void free_argv(char **argv)
{
	int i;
	
	if (argv == NULL)
		return;
	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
		argv[i] = NULL;
	}
	free(argv);
	argv = NULL;
}
/**
 * is_valid_number - checks if number is a positive int
 * @str: string parameter
 * Return: bool variable of true and
*/

bool is_valid_number(const char *str)
{
	if (str == NULL || *str == '\0')
		return false;
	while (*str)
	{
		if (!isdigit(*str))
			return false;
		str++;
	}
	return(true);
}
/**
 * main - main function
 * @argc: count parameter
 * @argv: vector parameter
 * Return: 0 on success)
 */

int main(int argc, char **argv)
{
	bool pipe = false;
	char *errorMessage = "Error parsing command.\n";
	char *command = NULL;
	size_t command_size = 0;
	ssize_t num_chars = 0;
	int exit_code;
	char *exit_args;
	FILE *file = NULL;
	if (argc > 1)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
	}
	while (1 && !pipe)
	{
		print_prompt();
		if (file)
		{
			num_chars = getline(&command, &command_size, file);
			if (num_chars == -1)
			{
				if (feof(stdin))
				{
					write(1, "\n", 1);
					free(command);
					break;
				}
			}
		}
		else
		{
			num_chars = getline(&command, &command_size, stdin);
			if (num_chars == -1)
			{
				if (feof(stdin))
				{
					write(1, "\n", 1);
					free(command);
					exit(0);
				}
			}
		}
		if (num_chars == 0)
		{
			free(command);
			command = NULL;
			continue;
		}
		if (command[num_chars - 1] == '\n')
		{
			command[num_chars - 1] = '\0';
			num_chars--;
		}
		if (strncmp(command, "exit", 4) == 0)
		{
			exit_args = strtok(command, " ");
			if (exit_args != NULL)
			{
				exit_args = strtok(NULL, " ");
				if (exit_args == NULL)
				{
					free(command);
					exit(0);
				}
				else if (is_valid_number(exit_args))
				{
					exit_code = atoi(exit_args);
					free(command);
					exit(exit_code);
				}
				else 
				{
					write(2, "./hsh: 1: exit: Illegal number: ", 32);
					write(2, exit_args, strlen(exit_args));
					write(2, "\n", 1);
					free(command);
					exit(2);
				}
			}
			else
			{
				free(command);
				exit(0);
			}
		}
		argv = parse_command(command, num_chars);
		if (argv == NULL)
		{
			write(STDERR_FILENO, errorMessage, strlen(errorMessage));
			free(command);
			command = NULL;
			continue;
		}
		execute_command(argv);
		free_argv(argv);
		free(command);
		command = NULL;
	}
	if (file)
	{
		fclose(file);
	}
	return (0);
}

