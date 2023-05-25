#include "shell.h"
#include <stdlib.h>

/**
 * interactive -This gives true if the shell is in interactive or not.
 * @info: This is a struct adress which will be returned after a while.
 * Return: IF sucsses Gives 1 neither Givers -1.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This is a checker for a deliminater.
 * @cha: this is a character.
 * @delim: This is a string.
 * Return: IF TRUE , returns 1 else returns 0.
 */
int is_delim(char cha, char *delim)
{
	do {
		if (*delim++ == cha)
			return (1);
	} while (*delim);
	return (0);
}

/**
 *_isalpha - This is a checker to all the aphabetic
 * characters.
 *@cha: This is a character.
 *Return: IF TRUE , returns 1 else returns 0.
 */

int _isalpha(int cha)
{
	if ((cha >= 'A' && cha <= 'Z') || (cha >= 'a' && cha <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This is a converter of a string given into
 * an integer.
 *@stri: This is a string converted by _atoi.
 *Return: IF no number found , returns 0 else returns 1.
 */

int _atoi(char *stri)
{
	int kk, sn = 1;
	int fggg = 0, putout;
	unsigned int answer = 0;

	for (kk = 0;  stri[kk] != '\0' && fggg != 2; kk++)
	{
		if (stri[kk] == '-')
			sn *= -1;

		if (stri[kk] >= '0' && stri[kk] <= '9')
		{
			fggg = 1;
			answer *= 10;
			answer += (stri[kk] - '0');
		}
		else if (fggg == 1)
			fggg = 2;
	}

	if (sn == -1)
		putout = -answer;
	else
		putout = answer;

	return (putout);
}
