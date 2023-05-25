#include "shell.h"
#include<stdlib.h>


/**
 *_eputs -Print an input to the strings passed.
 * @stri: String to be printed in the console.
 * Return: Nothing to be printed to the console or ouput.
 */
void _eputs(char *stri)
{
	int pp = 0;

	if (!stri)
		return;
	do {
		_eputchar(stri[pp]);
		pp++;
	} while (stri[pp] != '\0');
}

/**
 * _eputchar - Write the character c.
 * @cha: Character to be printed in the program.
 * Return: IF sucsses return 0 neither Givers -1
 */
int _eputchar(char cha)
{
	static int pp;
	static char bufff[WRITE_BUF_SIZE];

	if (cha == BUF_FLUSH || pp >= WRITE_BUF_SIZE)
	{
		write(2, bufff, pp);
		pp = 0;
	}
	if (cha != BUF_FLUSH)
		bufff[pp++] = cha;
	return (1);
}

/**
 * _putfd - This will char Character to the fd passed in the program.
 * @cha: Character to be printed.
 * @fil: Describes the file passed in the program.
 * Return: IF sucsses return 1 neither Givers -1
 */
int _putfd(char cha, int fil)
{
	static int pp;
	static char bufff[WRITE_BUF_SIZE];

	if (cha == BUF_FLUSH || pp >= WRITE_BUF_SIZE)
	{
		write(fil, bufff, pp);
		pp = 0;
	}
	if (cha != BUF_FLUSH)
		bufff[pp++] = cha;
	return (1);
}

/**
 *_putsfd - Input passed to print.
 * @stri: String to be printed.
 * @fil: File descriptor.
 * Return: Return the number of character.
 */
int _putsfd(char *stri, int fil)
{
	int pp = 0;

	if (!stri)
		return (0);
	do {
		pp += _putfd(*stri++, fil);
	} while (*stri);
	return (pp);
}
