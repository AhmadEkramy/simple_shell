#include "shell.h"
#include <stdlib.h>

/**
 * get_history_file - this gets the history of the files
 * and returns to the console the history of each file.
 * @info: This is the parameter parameter struct to be
 * shown to the console.
 * Return: This returns the allocated string containg history
 * of the files and give each one by one.
 */

char *get_history_file(info_t *info)
{
	char *bufff, *directy;

	directy = _getenv(info, "HOME=");
	if (!directy)
		return (NULL);
	bufff = malloc(sizeof(char) * (_strlen(directy) + _strlen(HIST_FILE) + 2));
	if (!bufff)
		return (NULL);
	bufff[0] = 0;
	_strcpy(bufff, directy);
	_strcat(bufff, "/");
	_strcat(bufff, HIST_FILE);
	return (bufff);
}

/**
 * write_history - this will creates a file, or appends to an
 * existing file which has been passed as an args.
 * @information: this is the parameter struct to be created and display
 * to be display in the console.
 * Return: On success 1 is return and printed to the console,
 * and -1 when fails.
 */
int write_history(info_t *information)
{
	ssize_t ffopen;
	char *nameFile = get_history_file(information);
	list_t *node = NULL;

	if (!nameFile)
		return (-1);

	ffopen = open(nameFile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nameFile);
	if (ffopen == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		_putsfd(node->str, ffopen);
		_putfd('\n', ffopen);
	}
	_putfd(BUF_FLUSH, ffopen);
	close(ffopen);
	return (1);
}

/**
 * read_history - This reads the history from file and displays each
 * history of each file to the console.
 * @info:This is  the parameter struct to be returned to the console
 * of the output.
 * Return: This will the histcount on success
 * and 0 when fails.
 */
int read_history(info_t *info)
{
	int pp, behh = 0;
	int lCounter = 0;
	ssize_t ffopen, readLen;
	ssize_t fileSize = 0;
	struct stat st;
	char *bufff = NULL;
	char *nameFile = get_history_file(info);

	if (!nameFile)
		return (0);

	ffopen = open(nameFile, O_RDONLY);
	free(nameFile);
	if (ffopen == -1)
		return (0);
	if (!fstat(ffopen, &st))
		fileSize = st.st_size;
	if (fileSize < 2)
		return (0);
	bufff = malloc(sizeof(char) * (fileSize + 1));
	if (!bufff)
		return (0);
	readLen = read(ffopen, bufff, fileSize);
	bufff[fileSize] = 0;
	if (readLen <= 0)
		return (free(bufff), 0);
	close(ffopen);
	for (pp = 0; pp < fileSize; pp++)
		if (bufff[pp] == '\n')
		{
			bufff[pp] = 0;
			build_history_list(info, bufff + behh, lCounter++);
			behh = pp + 1;
		}
	if (behh != pp)
	build_history_list(info, bufff + behh, lCounter++);
	free(bufff);
	info->histcount = lCounter;
	while (info->histcount-- >= HIST_MAX)
	delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - this will adds entry to a history linked list
 * when passed args.
 * @info: this is the structure containing potential arguments.
 * Used to maintain code to be returned to the console.
 * @buf: This is the buffer of the files to be printed in the console.
 * @linecount: This is the history linecount, histcount which
 * returns to the console the history of all the files.
 * Return: On success it returns 0 and 1 when fails.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - This will renumbers the history linked list
 * and returuned the changes which were previously passed after changes
 * made.
 * @info: This is the structure containing potential arguments about the
 * parameters passed.
 * Return: This will always return the histcount to the console
 * of the output.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int pp = 0;

	do {
		node->num = pp++;
		node = node->next;
	} while (node);
	return (info->histcount = pp);
}
