#include "shell.h"
#include<stdlib.h>

/**
 * _strcpy - Always will copy the strings
 * present or passed as parameter
 * @dest: Destination where the strings.
 * @src: Source of the string.
 * Return: Return pointers.
 */
char *_strcpy(char *dest, char *src)
{
	int pp = 0;

	if (dest == src || src == 0)
		return (dest);
	do {
		dest[pp] = src[pp];
		pp++;
	} while (src[pp]);
	dest[pp] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a strings present
 * @stri: String to to duplicated when checking.
 * Return: Return the duplicated string.
 */
char *_strdup(const char *stri)
{
	int legth = 0;
	char *retun;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		legth++;
	retun = malloc(sizeof(char) * (legth + 1));
	if (!retun)
		return (NULL);
	for (legth++; legth--;)
		retun[legth] = *--stri;
	return (retun);
}

/**
 *_puts - Print to the console an input string.
 *@stri: String to be printed to the output.
 * Return: Return Nothing or NULL.
 */
void _puts(char *stri)
{
	int pp = 0;

	if (!stri)
		return;
	do {
		_putchar(stri[pp]);
		pp++;
	} while (stri[pp] != '\0');
}

/**
 * _putchar - Write the characters to stdout.
 * @cha: Character toto be printed.
 * Return: IF sucsses Gives 1 neither Givers -1.
 */
int _putchar(char cha)
{
	static int pp;
	static char bufff[WRITE_BUF_SIZE];

	if (cha == BUF_FLUSH || pp >= WRITE_BUF_SIZE)
	{
		write(1, bufff, pp);
		pp = 0;
	}
	if (cha != BUF_FLUSH)
		bufff[pp++] = cha;
	return (1);
}
