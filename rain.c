#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @tach: param deyal struct
 * @bu: address deyal  buffer li endna
 * @leno: address deyal len var li ghadi nkhadmo bih
 *
 * Return: bytes li qrina
 */
ssize_t input_buf(info_t *tach, char **bu, size_t *leno)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*leno) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)tach->cmd_buf);*/
		free(*bu);
		*bu = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(bu, &len_p, stdin);
#else
		r = _getline(tach, bu, &len_p);
#endif
		if (r > 0)
		{
			if ((*bu)[r - 1] == '\n')
			{
				(*bu)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			tach->linecount_flag = 1;
			remove_comments(*bu);
			/* if (_strchr(*bu, ';')) is this a command chain? */
			{
				*leno = r;
				tach->cmd_buf = bu;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @tach: parameter deyal struct
 *
 * Return: bytes li qrina
 */
ssize_t get_input(info_t *tach)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(tach->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(tach, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(tach, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(tach, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			tach->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @tach: parameter deyal struct
 * @bu: buffer li endna
 * @size: size li ghadi nkhadmo bih
 *
 * Return: r
 */
ssize_t read_buf(info_t *tach, char *bu, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(tach->readfd, bu, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @tach: parameter deyal struct li endna
 * @pitro: address deyal pointer heta buffer, preallocated wela NULL
 * @leno: lqyass deyale preallocated ptr buffer ila makanch  NULL
 *
 * Return: s
 */
int _getline(info_t *tach, char **pitro, size_t *leno)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pitro;
	if (p && leno)
		s = *leno;
	if (i == len)
		i = len = 0;

	r = read_buf(tach, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (leno)
		*leno = s;
	*pitro = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @s_num: la signe deyal dak num
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int s_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
