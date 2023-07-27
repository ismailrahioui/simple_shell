#include "shell.h"

/**
 * list_len - tahded tol ellinked list
 * @x: pinter awel node
 *
 * Return: size of list
 */
size_t list_len(const list_t *x)
{
	size_t u = 0;

	while (x)
	{
		x = x->next;
		u++;
	}
	return (u);
}

/**
 * list_to_strings - bereturn arrstring bta3et ellist
 * @addpoint: pinter awel node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *addpoint)
{
	list_t *node = addpoint;
	size_t u = list_len(addpoint), j;
	char **strs;
	char *str;

	if (!addpoint || !u)
		return (NULL);
	strs = malloc(sizeof(char *) * (u + 1));
	if (!strs)
		return (NULL);
	for (u = 0; node; node = node->next, u++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < u; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[u] = str;
	}
	strs[u] = NULL;
	return (strs);
}


/**
 * print_list - bytba3 kol elelements oflist_t mtsl with list
 * @x: elpointer bta3 awel node
 *
 * Return: size of list
 */
size_t print_list(const list_t *x)
{
	size_t u = 0;

	while (x)
	{
		_puts(convert_number(x->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(x->str ? x->str : "(nil)");
		_puts("\n");
		x = x->next;
		u++;
	}
	return (u);
}

/**
 * node_starts_with - back noote whose string start with repfox
 * @noote: elpointer elkhas be ellist
 * @repfox: elestring elgded
 * @k: tany character ba3d el repfox
 *
 * Return: match noote or null
 */
list_t *node_starts_with(list_t *noote, char *repfox, char k)
{
	char *pp = NULL;

	while (noote)
	{
		pp = starts_with(noote->str, repfox);
		if (pp && ((k == -1) || (*pp == k)))
			return (noote);
		noote = noote->next;
	}
	return (NULL);
}

/**
 * get_node_index - bngeb inteex bta3t elnoote
 * @addpoint: elpointer bta3 elhead
 * @noote: elpointer to noote
 *
 * Return: inteex of noote or -1
 */
ssize_t get_node_index(list_t *addpoint, list_t *noote)
{
	size_t u = 0;

	while (addpoint)
	{
		if (addpoint == noote)
			return (u);
		addpoint = addpoint->next;
		u++;
	}
	return (-1);
}
