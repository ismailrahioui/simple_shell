#include "shell.h"

/**
 * add_node - node start the list
 * @addpoint: el address bta3 el pointer
 * @stfield: elstr bta3 elfield
 * @raqm: index of history that used
 *
 * Return: size of the list which used
 */
list_t *add_node(list_t **addpoint, const char *stfield, int raqm)
{
	list_t *new_head;

	if (!addpoint)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->raqm = raqm;
	if (stfield)
	{
		new_head->stfield = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *addpoint;
	*addpoint = new_head;
	return (new_head);
}

/**
 * add_node_end - adds node fe akher el list
 * @addpoint: el address bta3 el pointer
 * @stfield: elstr bta3 elfield
 * @raqm: index of history that used
 *
 * Return: size of the list which used
 */
list_t *add_node_end(list_t **addpoint, const char *stfield, int raqm)
{
	list_t *new_node, *noote;

	if (!addpoint)
		return (NULL);

	noote = *addpoint;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->raqm = raqm;
	if (stfield)
	{
		new_node->stfield = _strdup(stfield);
		if (!new_node->stfield)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (noote)
	{
		while (noote->next)
			noote = node->next;
		noote->next = new_node;
	}
	else
		*addpoint = new_node;
	return (new_node);
}

/**
 * print_list_str - tb3 str element bta3t el list_t with list
 * @x: el address bta3 el pointer
 *
 * Return: size of the list which used
 */
size_t print_list_str(const list_t *x)
{
	size_t u = 0;

	while (x)
	{
		_puts(x->str ? x->str : "(nil)");
		_puts("\n");
		x = x->next;
		u++;
	}
	return (u);
}

/**
 * delete_node_at_index - emsah elnode feha inteex
 * @addpoint: enwan elpointer of awel node
 * @inteex: elindex el haetmseh
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **addpoint, unsigned int inteex)
{
	list_t *node, *prev_node;
	unsigned int u = 0;

	if (!addpoint || !*addpoint)
		return (0);

	if (!inteex)
	{
		node = *addpoint;
		*addpoint = (*addpoint)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *addpoint;
	while (node)
	{
		if (u == inteex)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		u++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees kol elnode fe ellist
 * @heaptr: enwan elpointer bta3 elhead
 *
 * Return: void
 */
void free_list(list_t **heaptr)
{
	list_t *node, *next_node, *head;

	if (!heaptr || !*heaptr)
		return;
	head = *heaptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*heaptr = NULL;
}
