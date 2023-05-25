#include "shell.h"
#include <stdlib.h>

/**
 * _erratoi - Convert integers to a string.
 * @stri: String to be converted.
 * Return: IF sucsses Gives 0 neither Givers -1
 */
int _erratoi(char *stri)
{
	int pp = 0;
	unsigned long int answer = 0;

	if (*stri == '+')
		stri++;
	for (pp = 0;  stri[pp] != '\0'; pp++)
	{
		if (stri[pp] >= '0' && stri[pp] <= '9')
		{
			answer *= 10;
			answer += (stri[pp] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * print_error - Print an error message.
 * @info: Parameter to returned the info struct.
 * @cestr: Contains specfics error to be reported.
 * Return: IF sucsses Gives 0.
 */
void print_error(info_t *info, char *cestr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(cestr);
}

/**
 * print_d - Fucntion which prints a integer
 * @input: Input passed in the program.
 * @fil: File description.
 * Return: Returns number of character passed.
 */
int print_d(int input, int fil)
{
	int (*__putchar)(char) = _putchar;
	int pp, counters = 0;
	unsigned int absolt;
	unsigned int showCurrent;

	if (fil == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absolt = -input;
		__putchar('-');
		counters;
	}
	else
		absolt = input;
	showCurrent = absolt;
	for (pp = 1000000000; pp > 1; pp /= 10)
	{
		if (absolt / pp)
		{
			__putchar('0' + showCurrent / pp);
			counters++;
		}
		showCurrent %= pp;
	}
	__putchar('0' + showCurrent);
	counters++;

	return (counters);
}

/**
 * convert_number - Converter function which is cLONED.
 * @num2: Number to be converted by converter function.
 * @base: Base where all the functions will lie.
 * @flags: Argms that will be returned from the base.
 * Return: String characters passed in the program.
 */
char *convert_number(long int num2, int base, int flags)
{
	static char *numArr;
	static char bufff[50];
	char sgnn = 0;
	char *pptt;
	unsigned long num1 = num2;

	if (!(flags & CONVERT_UNSIGNED) && num2 < 0)
	{
		num1 = -num2;
		sgnn = '-';

	}
	numArr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pptt = &bufff[49];
	*pptt = '\0';

	do {
		*--pptt = numArr[num1 % base];
		num1 /= base;
	} while (num1 != 0);

	if (sgnn)
		*--pptt = sgnn;
	return (pptt);
}

/**
 * remove_comments - Function which replace # with 0.
 * @buff: Address of the string to be modified.
 * Return: IF sucsses Gives 0.
 */
void remove_comments(char *buff)
{
	int pp;

	for (pp = 0; buff[pp] != '\0'; pp++)
		if (buff[pp] == '#' && (!pp || buff[pp - 1] == ' '))
		{
			buff[pp] = '\0';
			break;
		}
}
