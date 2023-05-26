#include "shell.h"

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

