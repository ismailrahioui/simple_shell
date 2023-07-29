#include "shell.h"

/**
 * get_history_file - hngeb tarekh el file
 * @soha: elbarameter btaa elstructure
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *soha)
{
	char *buf, *dir;

	dir = _getenv(soha, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - bybne file, or byzhar to an existing file
 * @soha: elbarameter btaa elstructure
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *soha)
{
	ssize_t fd;
	char *filename = get_history_file(soha);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (soha = soha->history; soha; soha = soha->next)
	{
		_putsfd(soha->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - byqra eltarekh mn elfile
 * @soha: bta3 elparameter wel strctchert
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *soha)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info_t);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(soha, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(soha, buf + last, linecount++);
	free(buf);
	soha->histcount = linecount;
	while (soha->histcount-- >= HIST_MAX)
		delete_node_at_index(&(soha->history), 0);
	renumber_history(soha);
	return (soha->histcount);
}

/**
 * build_history_list - atts mdkhal gded
 * @soha: feha shwyat hagat
 * @buff: buffer
 * @linecounter: adad el tarekh dah
 *
 * Return: Always 0
 */
int build_history_list(info_t *soha, char *buff, int linecounter)
{
	list_t *node = NULL;

	if (soha->history)
		node = soha->history;
	add_node_end(&node, buff, linecounter);

	if (!soha->history)
		soha->history = node;
	return (0);
}

/**
 * renumber_history - renumbgjyers the hisotory lieeenked list after changes
 * @soha: feha shwya arguments
 *
 * Return: the new histcount
 */
int renumber_history(info_t *soha)
{
	list_t *node = soha->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (soha->histcount = i);
}
