#include "shell.h"

/**
 * _strlen - gets string length
 * @s: string parameter
 * Return: string length
 *
 */

int _strlen(const char *s)
{
	int len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * _strcpy -Function copies the string pointed to by src
 * @dest: destination
 * @src: source
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	int len = 0;

	while (*(src + len) != '\0')
	{
		*(dest + len) = *(src + len);
		len++;
	}
	*(dest + len) = '\0';
	return (dest);
}

/**
 *_strcat - concatenate two strings
 * @dest: Parameter destination
 * @src: parameter source
 *
 * Return: Destination pointer
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - Function compares two string values
 * @s1: First string input
 * @s2: Second string input
 * Return: The differenc between string 1 and 2
 */

int _strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/**
 * _strdup - Returns a pointer which contains a copy of a given string.
 * @str: The string input.
 *
 * Return: Pointer to duplicated string or null if memory insufficient.
 */

char *_strdup(const char *str)
{
	int count = 0;
	int i;
	char *s;

	if (str == NULL)
	{
		return (NULL);
	}

	while (str[count] != '\0')
	{
		count++;
	}

	s = (char *)malloc(count * sizeof(char) + 1);

	if (s == NULL)
	{
		free(s);
		return (NULL);
	}
	for (i = 0; i < count; i++)
	{
		s[i] = str[i];
	}
	return (s);
}
