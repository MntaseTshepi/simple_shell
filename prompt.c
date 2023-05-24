#include "shell.h"
#include <unistd.h>
#include <string.h>

/**
 * print_prompt - prints shell prompt
 * Return: Void
 */

void print_prompt(void)
{
    const char *prompt = "$ ";

    if (isatty(STDIN_FILENO))
    {
        write(STDOUT_FILENO, prompt, strlen(prompt));
    }
}
