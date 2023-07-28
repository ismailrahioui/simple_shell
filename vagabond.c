#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @tazeko: sss
 */
void clear_info(info_t *tazeko)
{
	tazeko->arg = NULL;
	tazeko->argv = NULL;
	tazeko->vini = NULL;
	tazeko->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @otipax: stdress
 * @avenue: arguor
 */
void set_info(info_t *otipax, char **avenue)
{
	int i = 0;

	otipax->fname = avenue[0];
	if (otipax->arg)
	{
		otipax->argv = strtow(otipax->arg, " \t");
		if (!otipax->argv)
		{

			otipax->argv = malloc(sizeof(char *) * 2);
			if (otipax->argv)
			{
				otipax->argv[0] = _strdup(otipax->arg);
				otipax->argv[1] = NULL;
			}
		}
		for (i = 0; otipax->argv && otipax->argv[i]; i++)
			;
		otipax->argc = i;

		replace_alias(otipax);
		replace_vars(otipax);
	}
}

/**
 * free_info - frees info_t struct fields
 * @cea: =ddress
 * @alli: true  fields
 */
void free_info(info_t *cea, int alli)
{
	ffree(cea->argv);
	cea->argv = NULL;
	cea->vini = NULL;
	if (alli)
	{
		if (!cea->cmd_buf)
			free(cea->arg);
		if (cea->env)
			free_list(&(cea->env));
		if (cea->history)
			free_list(&(cea->history));
		if (cea->alias)
			free_list(&(cea->alias));
		ffree(cea->environ);
			cea->environ = NULL;
		bfree((void **)cea->cmd_buf);
		if (cea->readfd > 2)
			close(cea->readfd);
		_putchar(BUF_FLUSH);
	}
}
