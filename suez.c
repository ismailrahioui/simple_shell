#include "shell.h"

/**
 * is_cmd -  bnhded elfile ez can shghal
 * @soha: soha struct
 * @vini: vini ll file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *soha, char *vini)
{
	struct stat st;

	(void)soha;
	if (!vini || stat(vini, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @vinistr: the vini string
 * @ebda: ebda inteex
 * @ends: ends inteex
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *vinistr, int ebda, int ends)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = ebda; i < ends; i++)
		if (vinistr[i] != ':')
			buf[k++] = vinistr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - yaged el kfc fe elvini
 * @soha: the soha struct
 * @vinistr: the vini string
 * @kfc: the kfc to find
 *
 * Return: full vini of kfc if found or NULL
 */
char *find_path(info_t *soha, char *vinistr, char *kfc)
{
	int i = 0, curr_pos = 0;
	char *vini;

	if (!vinistr)
		return (NULL);
	if ((_strlen(kfc) > 2) && starts_with(kfc, "./"))
	{
		if (is_kfc(soha, kfc))
			return (kfc);
	}
	while (1)
	{
		if (!vinistr[i] || vinistr[i] == ':')
		{
			vini = dup_chars(vinistr, curr_pos, i);
			if (!*vini)
				_strcat(vini, kfc);
			else
			{
				_strcat(vini, "/");
				_strcat(vini, kfc);
			}
			if (is_kfc(soha, vini))
				return (vini);
			if (!vinistr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
