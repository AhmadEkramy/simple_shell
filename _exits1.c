#include "shell.h"
#include<stdlib.h>

/**
 **_strncpy - Strings passed is copied.
 *@dest: Destination of the file.
 *@src: Source of the program.
 *@num: Number of characters will be copied.
 *Return: This returns the concatenated strings to the console
 * of the output.
 */
char *_strncpy(char *dest, char *src, int num)
{
	int pp;
	int jj;
	char *scrr = dest;

	pp = 0;

	do {
		dest[pp] = src[pp];
		pp++;
	} while (src[pp] != '\0' && pp < num - 1);
	if (pp < num)
	{
		jj = pp;
		do {
			dest[jj] = '\0';
			jj++;
		} while (jj < num);
	}
	return (scrr);
}

/**
 **_strncat - This is the two strings.
 *@dest: 1st string.
 *@src:  2nd string.
 *@num: amount of bytes.
 *Return: This will return the strings.
 */
char *_strncat(char *dest, char *src, int num)
{
	int pp;
	int jj;
	char *scrr = dest;

	pp = 0;
	jj = 0;
	while (dest[pp] != '\0')
		pp++;
	do {
		dest[pp] = src[jj];
		pp++;
		jj++;
	} while (src[jj] != '\0' && jj < num);
	if (jj < num)
		dest[pp] = '\0';
	return (scrr);
}

/**
 **_strchr - string.
 *@str: show if the string passed.
 *@cha: character when you search.
 *Return: This is the pointer to the strings.
 */
char *_strchr(char *str, char cha)
{
	while (*str++ != '\0')
	{
		if (*str == cha)
			return (str);
	}

	return (NULL);
}
