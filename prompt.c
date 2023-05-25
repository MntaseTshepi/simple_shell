#include "shell.h"
#include <unistd.h>
#include <string.h>

/**
 * print_prompt - prints shell prompt
 * Return: Void
 */

void print_prompt(void)
{
	
	if (isatty(STDIN_FILENO))
	{
		const char *prompt = "$ ";
		write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}
