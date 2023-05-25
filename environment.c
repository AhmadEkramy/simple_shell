#include "shell.h"
#include<stdlib.h>

/**
 * _myenv - Prints to the console.
 * @info: Structure containing the arguments.
 * Return: IF sucsses return 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);/*Giving you the list*/
	return (0);
}

/**
 * _getenv - Get the value passed.
 * @info: Structure containing arguments.
 * @name: Environment variables.
 * Return: Return the value passed.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pp;

	do {
		pp = starts_with(node->str, name);
		if (pp && *pp)
			return (pp);
		node = node->next;
	} while (node);
	return (NULL);
}

/**
 * _mysetenv - Initializing the environment.
 * @info: Structure which contains argumments.
 *  Return: IF sucsses return 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove the enviroment.
 * @info: Containing ptotenial agrments.
 *  Return: IF sucsses return 0.
 */
int _myunsetenv(info_t *info)
{
	int pp;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (pp = 1; pp <= info->argc; pp++)
		_unsetenv(info, info->argv[pp]);
	return (0);
}

/**
 * populate_env_list - Gether the enviroment lists.
 * @info: containing potential agruments.
 * Return: IF sucsses return 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t pp;

	for (pp = 0; environ[pp]; pp++)
		add_node_end(&node, environ[pp], 0);
	info->env = node;
	return (0);
}
