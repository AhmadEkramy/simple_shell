#include "shell.h"
#include<stdlib.h>

/**
 * **strtow - This will always splits the string into 2
 * and ignores the repeated deliminator.
 * @str: This is the input string to be splited into
 * 2.
 * @deli: This is the delimeter the string passed in the codes.
 * Return: This will always return the pointer array on
 *success and nothing is returned when failed.
 */

char **strtow(char *str, char *deli)
{
	int pp, jik, riek;
	int mom, noWord = 0;
	char **strr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (pp = 0; str[pp] != '\0'; pp++)
		if (!is_delim(str[pp], deli) && (is_delim(str[pp + 1], deli) ||
			!str[pp + 1]))
			noWord++;

	if (noWord == 0)
		return (NULL);
	strr = malloc((1 + noWord) * sizeof(char *));
	if (!strr)
		return (NULL);
	for (pp = 0, jik = 0; jik < noWord; jik++)
	{
		while (is_delim(str[pp], deli))
			pp++;
		riek = 0;
		while (!is_delim(str[pp + riek], deli) && str[pp + riek])
			riek++;
		strr[jik] = malloc((riek + 1) * sizeof(char));
		if (!strr[jik])
		{
			for (riek = 0; riek < jik; riek++)
				free(strr[riek]);
			free(strr);
			return (NULL);
		}
		for (mom = 0; mom < riek; mom++)
			strr[jik][mom] = str[pp++];
		strr[jik][mom] = 0;
	}
	strr[jik] = NULL;
	return (strr);
}

/**
 * **strtow2 - This will always splits a string into
 * many words.
 * @str: This is the input string to be passed as an argument.
 * @deli: This is the delimeter of the strings to be passed.
 * Return: On success, it returns the pointer to the array
 * and NULL is fails.
 */
char **strtow2(char *str, char deli)
{
	int pp, jik, riek;
	int mom, noWord = 0;
	char **strr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (pp = 0; str[pp] != '\0'; pp++)
		if ((str[pp] != deli && str[pp + 1] == deli) ||
		    (str[pp] != deli && !str[pp + 1]) || str[pp + 1] == deli)
			noWord++;
	if (noWord == 0)
		return (NULL);
	strr = malloc((1 + noWord) * sizeof(char *));
	if (!strr)
		return (NULL);
	for (pp = 0, jik = 0; jik < noWord; jik++)
	{
		while (str[pp] == deli && str[pp] != deli)
			pp++;
		riek = 0;
		while (str[pp + riek] != deli && str[pp + riek] && str[pp + riek] != deli)
			riek++;
		strr[jik] = malloc((riek + 1) * sizeof(char));
		if (!strr[jik])
		{
			for (riek = 0; riek < jik; riek++)
				free(strr[riek]);
			free(strr);
			return (NULL);
		}
		for (mom = 0; mom < riek; mom++)
			strr[jik][mom] = str[pp++];
		strr[jik][mom] = 0;
	}
	strr[jik] = NULL;
	return (strr);
}
