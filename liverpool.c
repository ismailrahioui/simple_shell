#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @tach: Sdisqlkfdklff
 *  Return: dima 0
 */
int _myhistory(info_t *tach)
{
	print_list(tach->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @tach: param
 * @store: alias
 *
 * Return: dima 0 f success, 1 on error
 */
int unset_alias(info_t *tach, char *store)
{
	char *pi, ci;
	int res;

	pi = _strchr(store, '=');
	if (!pi)
		return (1);
	ci = *pi;
	*pi = 0;
	res = delete_node_at_index(&(tach->alias),
		get_node_index(tach->alias, node_starts_with(tach->alias, store, -1)));
	*pi = ci;
	return (res);
}

/**
 * set_alias - sets alias to string hadi function
 * @tach: param
 * @store: alias string
 *
 * Return: dima 0 f success, 1 f error
 */
int set_alias(info_t *tach, char *store)
{
	char *poo;

	poo = _strchr(store, '=');
	if (!poo)
		return (1);
	if (!*++poo)
		return (unset_alias(tach, store));

	unset_alias(tach, store);
	return (add_node_end(&(tach->alias), store, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nodejs: wahed aliad node deyal varible
 *
 * Return: dima 0 f success, 1 f error
 */
int print_alias(list_t *nodejs)
{
	char *poo = NULL, *ai = NULL;

	if (nodejs)
	{
		poo = _strchr(nodejs->stfield, '=');
		for (ai = nodejs->stfield; ai <= poo; ai++)
			_putchar(*ai);
		_putchar('\'');
		_puts(poo + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @tach: variable
 *  Return: dima 0
 */
int _myalias(info_t *tach)
{
	int i = 0;
	char *poi = NULL;
	list_t *nodejs = NULL;

	if (tach->argc == 1)
	{
		nodejs = tach->alias;
		while (nodejs)
		{
			print_alias(nodejs);
			nodejs = nodejs->next;
		}
		return (0);
	}
	for (i = 1; tach->argv[i]; i++)
	{
		poi = _strchr(tach->argv[i], '=');
		if (poi)
			set_alias(tach, tach->argv[i]);
		else
			print_alias(node_starts_with(tach->alias, tach->argv[i], '='));
	}

	return (0);
}
