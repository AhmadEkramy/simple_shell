#include "shell.h"
#include<stdlib.h>

/**
 * _myhistory - Displays the history of shell.
 * @info: Struct containing all the informations.
 *  Return: IF sucsses Gives 0 to an input.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);/* Displaing the history of list */
	return (0);
}

/**
 * unset_alias - Set alias to a string given.
 * @info: Parameter to pass the number of code in.
 * @str: Returns the string alias of them all.
 * Return: IF sucsses Gives 0 neither Givers 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *pp;
	char cha;
	int results;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	cha = *pp;
	*pp = 0;
	results = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pp = cha;
	return (results);
}

/**
 * set_alias - Set an alias to a strings given.
 * @info: Struct parameter.
 * @str: String alias passed to an agrs
 * Return: IF sucsses Gives 0 neither Givers 1.
 */
int set_alias(info_t *info, char *str)
{
	char *pp;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias to a string.
 * @node: Passed on alias or an alias node.
 * Return: IF sucsses Gives 0 neither Givers 1.
 */
int print_alias(list_t *node)
{
	char *pp = NULL;
	char *arr = NULL;

	if (node)
	{
		pp = _strchr(node->str, '=');
		for (arr = node->str; arr <= pp; arr++)
			_putchar(*arr);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics to all the alias in a strings.
 * @info: Structure containing all the alias of the information.
 *  Return: IF sucsses Gives 0.
 */
int _myalias(info_t *info)
{
	int p = 0;
	char *pp = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		do {
			print_alias(node);
			node = node->next;
		} while (node);
		return (0);
	}
	for (p = 1; info->argv[p]; p++)
	{
		pp = _strchr(info->argv[p], '=');
		if (pp)
			set_alias(info, info->argv[p]);
		else
			print_alias(node_starts_with(info->alias, info->argv[p], '='));
	}

	return (0);
}
