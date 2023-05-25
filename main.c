#include "shell.h"
#include <stdlib.h>

/**
 * main -This is an entry point to begin entering data.
 * @ach: This is the arguments counter to the console.
 * @arv: This is the argument vector to the console.
 * Return:  On success, 0 is returned and 1 if fails.
 */
int main(int ach, char **arv)
{
	info_t info[] = { INFO_INIT };
	int ffopen = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (ffopen)
		: "r" (ffopen));

	if (ach == 2)
	{
		ffopen = open(arv[1], O_RDONLY);
		if (ffopen == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arv[0]);
				_eputs(": 0: Can't open ");
				_eputs(arv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = ffopen;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, arv);
	return (EXIT_SUCCESS);
}
