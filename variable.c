#include "shell.h"
#include<stdlib.h>

/**
 * is_chain - This will test the current element in a
 * buffer if it is a delimantor.
 * @info: This is the parameter struct to be tested or
 * checked.
 * @buff: This is the char buffer to passed as an
 * argument.
 * @pc: This is an address of current position in buffer
 * which will also be tested.
 * Return: if  chain deliminater, it returns 1
 * and 0 if not the one.
 */
int is_chain(info_t *info, char *buff, size_t *pc)
{
	size_t jik = *pc;

	if (buff[jik] == '|' && buff[jik + 1] == '|')
	{
		buff[jik] = 0;
		jik++;
		info->cmd_buf_type = CMD_OR;
	}
	if (buff[jik] == '&' && buff[jik + 1] == '&')
	{
		buff[jik] = 0;
		jik++;
		info->cmd_buf_type = CMD_AND;
	}
	if (buff[jik] == ';')
	{
		buff[jik] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pc = jik;
	return (1);
}

/**
 * check_chain - This checks the condition if we can continue
 * to check the chain to the last.
 * @info: This is the parameter struct which gives more informations
 * about the chains.
 * @buff: This is the char buff to be passed.
 * @pc: Thisis an address of current position in buffer
 * of an element.
 * @st: This is the starting position in buffer which
 * start the current position.
 * @leng: This is the length of the buffer which must be compared
 * with all the types.
 * Return: This always return Void since it is a void funtion.
 */
void check_chain(info_t *info, char *buff, size_t *pc, size_t st, size_t leng)
{
	size_t jik = *pc;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[st] = 0;
			jik = leng;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[st] = 0;
			jik = leng;
		}
	}

	*pc = jik;
}

/**
 * replace_alias -This will replace all the alias in a
 * tokenized strings.
 * @info: This is the parameter struct whic contain all
 * the informations.
 * Return: when replaced, it gives 1 and 0 if not.
 */
int replace_alias(info_t *info)
{
	int pp;
	list_t *node;
	char *pre;

	for (pp = 0; pp < 10; pp++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pre = _strchr(node->str, '=');
		if (!pre)
			return (0);
		pre = _strdup(pre + 1);
		if (!pre)
			return (0);
		info->argv[0] = pre;
	}
	return (1);
}

/**
 * replace_vars - Thi replaces all the strings in a tokenized
 * strings.
 * @info: this is the parameter struct which contains all the
 * information.
 * Return: if replaced, gives 1 and 0 if not.
 */
int replace_vars(info_t *info)
{
	int pp = 0;
	list_t *node;

	for (pp = 0; info->argv[pp]; pp++)
	{
		if (info->argv[pp][0] != '$' || !info->argv[pp][1])
			continue;

		if (!_strcmp(info->argv[pp], "$?"))
		{
			replace_string(&(info->argv[pp]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[pp], "$$"))
		{
			replace_string(&(info->argv[pp]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[pp][1], '=');
		if (node)
		{
			replace_string(&(info->argv[pp]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[pp], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - This replaces strings present in the
 * program of it excution.
 * @older: This is an address of old string to be replaced
 * by the new string.
 * @newer: This is the new string to replace the old string.
 * Return: if replaced, it gives 1 and 0 if not replaced.
 */
int replace_string(char **older, char *newer)
{
	free(*older);
	*older = newer;
	return (1);
}
