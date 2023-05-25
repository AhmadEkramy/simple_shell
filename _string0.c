#include "shell.h"
#include<stdlib.h>

/**
 * _strlen - String length.
 * @str: String whose length is checked.
 * Return: Integer length of the string.
 */
int _strlen(char *str)
{
	int pp = 0;

	if (!str)
		return (0);

	while (*str++)
		pp++;
	return (pp);
}

/**
 * _strcmp - Make lecihophical comaparison.
 * @num1: 1ST strang to be passed.
 * @num2: 2ND strang to be passed.
 * Return: if num1<num1, it print 1 to the console and
 * if num2>num1 it prints yes to the console.
 */
int _strcmp(char *num1, char *num2)
{
	do {
		if (*num1 != *num2)
			return (*num1 - *num2);
		num1++;
		num2++;
	} while (*num1 && *num2);

	if (*num1 == *num2)
		return (0);
	else
		return (*num1 < *num2 ? -1 : 1);
}

/**
 * starts_with - Checks the needle.
 * @hstack: String to be searched.
 * @point: Substring to BE find.
 * Return: Return an address of next character.
 */
char *starts_with(const char *hstack, const char *point)
{
	while (*point)
		if (*point++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination buffer of the files.
 * @src: Source buffeR.
 * Return: Return a pointer.
 */
char *_strcat(char *dest, char *src)
{
	char *retu = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (retu);
}
