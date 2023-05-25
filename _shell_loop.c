#include "shell.h"
#include<stdlib.h>

/**
 * hsh - Main shell loop.
 * @info: Parameter passed.
 * @argu: Argument of the vector.
 * Return: returns 0 on success and -1 on failure.
 */
int hsh(info_t *info, char **argu)
{
	ssize_t retu = 0;
	int bIn = 0;

	do {
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		retu = get_input(info);
		if (retu != -1)
		{
			set_info(info, argu);
			bIn = find_builtin(info);
			if (bIn == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	} while (retu != -1 && bIn != -2);

	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bIn == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bIn);
}

/**
 * find_builtin - Find a builtin command.
 * @info: Parameter which returns info struct.
 * Return: Return the followings;
 * -1 is returned if builtin not found,
 *0 is returned  if builtin executed successfully,
 *1 is returned if builtin found but not failed.
 *-2 is returned  if builtin signals exit() successfully.
 */
int find_builtin(info_t *info)
{
	int pp;
	int bIn = -1;
	builtin_table builtintbl[] = {
			{"exit", _myexit},
			{"env", _myenv},
			{"help", _myhelp},
			{"history", _myhistory},
			{"setenv", _mysetenv},
			{"unsetenv", _myunsetenv},
			{"cd", _mycd},
			{"alias", _myalias},
			{NULL, NULL}
	};

	for (pp = 0; builtintbl[pp].type; pp++)
		if (_strcmp(info->argv[0], builtintbl[pp].type) == 0)
		{
			info->line_count++;
			bIn = builtintbl[pp].func(info);
			break;
		}
	return (bIn);
}

/**
 * find_cmd - Find a command in PATH.
 * @info: Parameter & return info struct which
 * Return: Return NULL or void or nothing.
 */
void find_cmd(info_t *info)
{
	char *pathers = NULL;
	int pp, riek;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (pp = 0, riek = 0; info->arg[pp]; pp++)
		if (!is_delim(info->arg[pp], " \t\n"))
			riek++;
	if (!riek)
		return;

	pathers = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (pathers)
	{
		info->path = pathers;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Fork to an exec thread.
 * @info: Parameter which returns info struct passed.
 * Return: void or NULL or nothing.
 */
void fork_cmd(info_t *info)
{
	pid_t childPip;

	childPip = fork();
	if (childPip == -1)
	{
		perror("Error:");
		return;
	}
	if (childPip == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
