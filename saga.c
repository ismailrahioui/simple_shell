#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @tach: constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *tach)
{
	if (!tach->environ || tach->env_changed)
	{
		tach->environ = list_to_strings(tach->env);
		tach->env_changed = 0;
	}

	return (tach->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @tach:  prototype.
 *  Return: 1 f delete, 0 f otherwise
 * @vary: the string
 */
int _unsetenv(info_t *tach, char *vary)
{
	list_t *nodejs = tach->env;
	size_t i = 0;
	char *p;

	if (!nodejs || !vary)
		return (0);

	while (nodejs)
	{
		p = starts_with(nodejs->stfield, vary);
		if (p && *p == '=')
		{
			tach->env_changed = delete_node_at_index(&(tach->env), i);
			i = 0;
			nodejs = tach->env;
			continue;
		}
		nodejs = nodejs->next;
		i++;
	}
	return (tach->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @tach: Slksddjj
 * @very: tthe string
 * @input:  var value
 *  Return: dima 0
 */
int _setenv(info_t *tach, char *very, char *input)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!very || !input)
		return (0);

	buf = malloc(_strlen(very) + _strlen(input) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, very);
	_strcat(buf, "=");
	_strcat(buf, input);
	node = tach->env;
	while (node)
	{
		p = starts_with(node->stfield, very);
		if (p && *p == '=')
		{
			free(node->stfield);
			node->stfield = buf;
			tach->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(tach->env), buf, 0);
	free(buf);
	tach->env_changed = 1;
	return (0);
}
