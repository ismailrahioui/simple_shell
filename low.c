#include "shell.h"

/**
 * _myenv - prints the current environment
 * @tach: prototyp
 * Return: dima 0
 */
int _myenv(info_t *tach)
{
	print_list_str(tach->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @tach: S maintain
 * @nom: env var nome
 *
 * Return: valuer
 */
char *_getenv(info_t *tach, const char *nom)
{
	list_t *nodejs = tach->env;
	char *pu;

	while (nodejs)
	{
		pu = starts_with(nodejs->stfield, nom);
		if (pu && *pu)
			return (pu);
		nodejs = nodejs->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @tach:  prototype.
 *  Return: dima 0
 */
int _mysetenv(info_t *tach)
{
	if (tach->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(tach, tach->argv[1], tach->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @tach:  prototype.
 *  Return: dima 0
 */
int _myunsetenv(info_t *tach)
{
	int i;

	if (tach->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= tach->argc; i++)
		_unsetenv(tach, tach->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @tach: prototype.
 * Return: dima 0
 */
int populate_env_list(info_t *tach)
{
	list_t *nodejs = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&nodejs, environ[i], 0);
	tach->env = nodejs;
	return (0);
}
