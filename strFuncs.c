#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - a function that returns the length of a string
 * @s: a pointer to the characters string
 * Return: the length of the character string
 */

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - a function that copies the string pointed to by src, including the
 * terminating null byte, to the buffer pointed by des
 * @dest: pointer to the destination of copied string
 * @src: pointer to the src of the source string
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	size_t x;

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}

/**
 * _strcat - a function that concantenates two strings
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: pointer to destination string
 */

char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - a function that concantenates two strings where n number
 * of bytes are copied from source
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: the n bytes to copy from src
 * Return: pointer to destination string
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t x;

	for (x = 0; x < n && src[x] != '\0'; x++)
		dest[dest_len + x] = src[x];
	dest[dest_len + x] = '\0';

	return (dest);
}