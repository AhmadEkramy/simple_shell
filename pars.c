#include "shell.h"
#include<stdlib.h>

/**
 * is_cmd - this is to  determine if a file is an executable
 * command or not executable command.
 * @info: This is an info struct which contains many informaation.
 * @pathers: This is a path to the file present in the codes.
 * Return: On success, 1 is returned and 0 if fails.
 */
int is_cmd(info_t *info, char *pathers)
{
	struct stat st;

	(void)info;
	if (!pathers || stat(pathers, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - this will duplicate the characters of the
 * strings passed.
 * @pathstr: This is the PATH of the string to be checked.
 * @begin: This is the beginning or starting of index passed.
 * @stop: This is the stopping index of the character passed.
 * Return: This will return a pointer to new index.
 */
char *dup_chars(char *pathstr, int begin, int stop)
{
	static char buff[1024];
	int pp = 0;
	int riek = 0;

	for (riek = 0, pp = begin; pp < stop; pp++)
		if (pathstr[pp] != ':')
			buff[riek++] = pathstr[pp];
	buff[riek] = 0;
	return (buff);
}

/**
 * find_path - this will find the cmd in the PATH of the strings
 * given in the codes.
 * @info: This is the info struct of the given program
 * and contains more information.
 * @pathstr: This is the PATH strings given below or in the codes.
 * @cmd:This is  the cmd to find in the programs or codes.
 * Return: returns 1 if no strings found or cmd.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int pp = 0;
	int currentPosition = 0;
	char *pather;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	do {
		if (!pathstr[pp] || pathstr[pp] == ':')
		{
			pather = dup_chars(pathstr, currentPosition, pp);
			if (!*pather)
				_strcat(pather, cmd);
			else
			{
				_strcat(pather, "/");
				_strcat(pather, cmd);
			}
			if (is_cmd(info, pather))
				return (pather);
			if (!pathstr[pp])
				break;
			currentPosition = pp;
		}
		pp++;
	} while (1);
	return (NULL);
}
