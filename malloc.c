#include "shell.h"
#include<stdlib.h>

/**
 **_memset - This will always fills memory with a constant
 * and checks if it is used or not byte
 *@str: This is the pointer to the memory area which points to the
 * current element presents in the body of a codes.
 *@byt: This is the byte to fill with *s in the program
 * of a codes.
 *@num1: This is the amount of bytes to be filled in the
 * codes.
 *Return: This will return pointer to the string
 * present in the codes.
 */
char *_memset(char *str, char byt, unsigned int num1)
{
	unsigned int pp;

	for (pp= 0; pp < num1; pp++)
		str[pp] = byt;
	return (str);
}

/**
 * ffree - This will free a string of the strings given.
 * @pt: This is the string of the strings passed.
 */
void ffree(char **pt)
{
	char **args = pt;

	if (!pt)
		return;
	while (*pt)
		free(*pt++);
	free(args);
}

/**
 * _realloc - This will reallocates a block of memory to
 * the main memory and passed to it to the second.
 * @ptr: This is a pointer to a previous malloc allocated
 * property.
 * @oldSize: this is the byte size of previous block which
 * was created by a malloc.
 * @newSize: This will return the byte size of new block
 * created.
 * Return: This is the pointer to the block of files created
 * already in the files.
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *pt;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	pt = malloc(newSize);
	if (!pt)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		pt[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (pt);
}
