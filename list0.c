#include "shell.h"
#include<stdlib.h>

/**
 * add_node - This will add node at the end of the list
 * later link them together.
 * @head: this is an address of pointer to head node
 * which links the lists provided.
 * @str: this is a str field of node which will be passed.
 * @num: This is a node index used by history and display the history
 * of the files present.
 * Return: This will return the size of list
 * present or passed.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newHead;

	if (!head)
		return (NULL);
	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = num;
	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * add_node_end - This is will adds a node to the end of the
 * list and link them together at the end.
 * @head: this is an address of pointer to head node which point to
 * one after the other.
 * @str: This is a string  field of node where an agrs are
 * going to be passed.
 * @num: this is the node index used by history of the files and
 * gives the history of the files.
 * Return: this will always retunr size of list present.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		do {
			node = node->next;
		node->next = newNode;
		} while (node->next);
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * print_list_str - This will print only the string elements present in
 * in the list.
 * @hhder: This is a pointer to first node and then to the next later.
 * Return: This will always return size of list.
 */
size_t print_list_str(const list_t *hhder)
{
	size_t pp = 0;

	do {
		_puts(hhder->str ? hhder->str : "(nil)");
		_puts("\n");
		hhder = hhder->next;
		pp++;

	return (pp);
} while (hhder);

/**
 * delete_node_at_index - This will delete node at given index
 * and continue.
 * @head: This is an address of pointer to first node of the list.
 * @index: This is an index of node to be deleted in the list
 * provided.
 * Return: On success, 1 is returned and 0 when fails.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int pp = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
	if (pp == index)
	{
		prevNode->next = node->next;
		free(node->str);
		free(node);
		return (1);
	}
		pp++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - This will free all nodes of a list present
 * and the given point.
 * @head_ptr: This is an address of pointer to head node
 * of the of the list.
 * Return: AlWays return Null or void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nextNode, *header;

	if (!head_ptr || !*head_ptr)
		return;
	header = *head_ptr;
	node = header;
	do {

	 	nextNode = node->next;
	 	free(node->str);
	 	free(node);
		 node = nextNode;
	} while (node);

	*head_ptr = NULL;
}}
