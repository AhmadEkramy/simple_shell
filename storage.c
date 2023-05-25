#include "shell.h"
#include<stdlib.h>
/**
 * bfree - This will free a pointer and NULLs the address
 * which will return 0 to the console.
 * @ptri: This is an address of the pointer to free in the
 * program.
 * Return: This returns 1 when success and 0 if not.
 */
int bfree(void **ptri)
{
	if (ptri && *ptri)
	{
		free(*ptri);
		*ptri = NULL;
		return (1);
	}
	return (0);
}
