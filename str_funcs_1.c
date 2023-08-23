#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - a function that locates a character in a string
 * @s: the string to be searched
 * @c: the character to be located
 * Return: if c is found - a pointer to the first occurence
 * if c is not found - NULL
 */

char *_strchr(char *s, char c)
{
	int ind;

	for (ind = 0; s[ind]; ind++)
	{
		if (s[ind] == c)
			return (s + ind);
	}

	return (NULL);
}

/**
 * _strspn - a function that gets the length of a prefix substring
 * @s: the string to be searched
 * @accept: the prefix to be measured
 * Return: the number of bytes in s which
 * consist only of bytes from accept
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - a function that compares two strings
 * @s1: the first string to be compared
 * @s2: the second string to be compared
 * Return: positive byte difference if s1 > s2
 * 0 if s1 = s2
 * Negative byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - a function that compare two strings
 * @s1: pointer to a string
 * @s2: pointer to a string
 * @n: the first n bytes of the strings to compare
 * Return: Less than 0 if s1 is shorter than s2
 * 0 if s1 and s2 match
 * Greater than 0 if s1 is longer than s2
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t x;

	for (x = 0; s1[x] && s2[x] && x < n; x++)
	{
		if (s1[x] > s2[x])
			return (s1[x] - s2[x]);
		else if (s1[x] < s2[x])
			return (s1[x] - s2[x]);
	}
	if (x == n)
		return (0);
	else
		return (-15);
}

