#include "shell.h"
#include<stdlib.h>

/**
 * list_len - This will always determine length of linked list
 * presnet in the codes.
 * @hhder: This is the pointer to first node of the program or
 * codes written
 * Return: size of list
 */
size_t list_len(const list_t *hhder)
{
	size_t pp = 0;

	do {
		hhder = hhder->next;
		pp++;
	} while (hhder);

	return (pp);
}

/**
 * list_to_strings - This will return an array of strings
 * of the list->str linked to the codes.
 * @header: This is a pointer to first node passed.
 * Return: This will always return an array of strings present
 * in the codes.
 */
char **list_to_strings(list_t *header)
{
	list_t *node = header;
	size_t pp = list_len(header);
	size_t jik;
	char **riek;
	char *stri;

	if (!header || !pp)
		return (NULL);
	riek = malloc(sizeof(char *) * (pp + 1));
	if (!riek)
		return (NULL);
	for (pp = 0; node; node = node->next, pp++)
	{
		stri = malloc(_strlen(node->str) + 1);
		if (!stri)
		{
			for (jik = 0; jik < pp; jik++)
				free(riek[jik]);
			free(riek);
			return (NULL);
		}

		stri = _strcpy(stri, node->str);
		riek[pp] = stri;
	}
	riek[pp] = NULL;
	return (riek);
}


/**
 * print_list - This will print all the elements of a
 * list_t linked list in the files given or passed.
 * @hhder: This is a pointer to first node given or passed.
 * Return: This is the size of list in the strings and the one
 * given in codes.
 */
size_t print_list(const list_t *hhder)
{
	size_t pp = 0;

	do {
		_puts(convert_number(hhder->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hhder->str ? hhder->str : "(nil)");
		_puts("\n");
		hhder = hhder->next;
		pp++;
	} while (hhder);
	return (pp);
}

/**
 * node_starts_with - This will return a node whose string starts
 * with prefix in the given codes.
 * @node: This is a pointer to list head passed in the codes.
 * @p_fix: This is the string to match in the codes given.
 * @cha: This is the next character after prefix to match
 * with the previous one or codes.
 * Return: This will returns match node or null or nothing
 * nothing is found.
 */
list_t *node_starts_with(list_t *node, char *p_fix, char cha)
{
	char *pre = NULL;

	do {
		pre = starts_with(node->str, p_fix);
		if (pre && ((cha == -1) || (*pre == cha)))
			return (node);
		node = node->next;
	} while (node);

	return (NULL);
}

/**
 * get_node_index - This is to get the index of a node presents
 * in the codes passed in the codes.
 * @header: This is the pointer to list head of the node
 * and point to another one.
 * @node: This is a pointer to the node passed in the codes
 * and returns a new nodes.
 * Return: This will always returns index of the node
 * or -1 when fail to get any index of the node present in the
 * codes.
 */
ssize_t get_node_index(list_t *header, list_t *node)
{
	size_t pp = 0;

	do {
		if (header == node)
			return (pp);
		header = header->next;
		pp++;
	}  while (header);

	return (-1);
}
