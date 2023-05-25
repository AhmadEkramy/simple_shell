#include "shell.h"
#include<stdlib.h>

/**
 * _myexit - Exit to the shell.
 * @info: Holds the informations in function.
 *  Return: Exits with new command and later used.
 */
int _myexit(info_t *info)
{
	int che;

	if (info->argv[1])
	{
		che = _erratoi(info->argv[1]);
		if (che == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current working directory.
 * @info: Information to a structure.
 *  Return: IF sucsses Gives 0 to the console.
 */
int _mycd(info_t *info)
{
	char *ste, *dirtt;
	char buffer[1024];
	int chdr;

	ste = getcwd(buffer, 1024);
	if (!ste)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirtt = _getenv(info, "HOME=");
		if (!dirtt)
			chdr = chdir((dirtt = _getenv(info, "PWD=")) ? dirtt : "/");
		else
			chdr = chdir(dirtt);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ste);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdr =
			chdir((dirtt = _getenv(info, "OLDPWD=")) ? dirtt : "/");
	}
	else
		chdr = chdir(info->argv[1]);
	if (chdr == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Changes the current working directory.
 * @info: Contains the information about the functions was pass.
 *  Return: IF sucsses Gives 0 to the console.
 */
int _myhelp(info_t *info)
{
	char **argmt;

	argmt = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argmt);
	return (0);
}
