#include "shell.h"
#include<stdlib.h>

/**
 * input_buf - Chained commands.
 * @info: Struct of information.
 * @buff: Address of buffer.
 * @len: Address of length variable.
 * Return: Return number of bytes.
 */
ssize_t input_buf(info_t *info, char **buff, size_t *len)
{
	ssize_t retu = 0;
	size_t Len_k = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
		retu = getline(buff, &Len_k, stdin);
		retu = _getline(info, buff, &Len_k);
		if (retu > 0)
		{
			if ((*buff)[retu - 1] == '\n')
			{
				(*buff)[retu - 1] = '\0';
				retu--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*len = retu;
				info->cmd_buf = buff;
			}
		}
	}
	return (retu);
}

/**
 * get_input - Minus the newline.
 * @info: Struct of information.
 * Return: Return number of bytes.
 */
ssize_t get_input(info_t *info)
{
	static char *bufff;
	static size_t pp;
	static size_t lo, len_y;
	ssize_t retu = 0;
	char **buff_pt = &(info->arg);
	char *pre;

	_putchar(BUF_FLUSH);
	retu = input_buf(info, &bufff, &len_y);
	if (retu == -1)
		return (-1);
	if (len_y)
	{
		lo = pp;
		pre = bufff + pp;

		check_chain(info, bufff, &lo, pp, len_y);
		do {
			if (is_chain(info, bufff, &lo))
				break;
			lo++;
		} while (lo < len_y);

		pp = lo + 1;
		if (pp >= len_y)
		{
			pp = len_y = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_pt = pre;
		return (_strlen(pre));
	}

	*buff_pt = bufff;
	return (retu);
}

/**
 * read_buf - This will read a buffer to the console.
 * @info: Struct of information.
 * @buff: Buffer passed in the program.
 * @sz: Size of the argument.
 * Return: Return the spaecified number.
 */
ssize_t read_buf(info_t *info, char *buff, size_t *sz)
{
	ssize_t retu = 0;

	if (*sz)
		return (0);
	retu = read(info->readfd, buff, READ_BUF_SIZE);
	if (retu >= 0)
		*sz = retu;
	return (retu);
}

/**
 * _getline -Getting the next line of input from STDIN.
 * @info: Struct of information.
 * @ptr: Address of pointer to buffer.
 * @lengthy: Size of preallocated pointer.
 * Return: Return a specific number passed.
 */
int _getline(info_t *info, char **ptr, size_t *lengthy)
{
	static char bufff[READ_BUF_SIZE];
	static size_t pp, len_y;
	size_t kik;
	ssize_t retu = 0;
	ssize_t siz = 0;
	char *pre = NULL;
	char *nwpp = NULL, *cha;

	pre = *ptr;
	if (pre && lengthy)
		siz = *lengthy;
	if (pp == len_y)
		pp = len_y = 0;

	retu = read_buf(info, bufff, &len_y);
	if (retu == -1 || (retu == 0 && len_y == 0))
		return (-1);

	cha = _strchr(bufff + pp, '\n');
	kik = cha ? 1 + (unsigned int)(cha - bufff) : len_y;
	nwpp = _realloc(pre, siz, siz ? siz + kik : kik + 1);
	if (!nwpp)
		return (pre ? free(pre), -1 : -1);

	if (siz)
		_strncat(nwpp, bufff + pp, kik - pp);
	else
		_strncpy(nwpp, bufff + pp, kik - pp + 1);

		siz += kik - pp;
		pp = kik;
		pre = nwpp;

	if (lengthy)
		*lengthy = siz;
	*ptr = pre;
	return (siz);
}

/**
 * sigintHandler -This is a blocks to a ctrl-C.
 * @sig_num: Signal number numner to be returned.
 * Return: Return Null or void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
