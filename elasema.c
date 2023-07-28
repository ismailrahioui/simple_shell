#include "shell.h"

/**
 * add_node - edafa node lbdayat ellist
 * @addpoint: enwan elpointer bta3 elhead node
 * @stfield: str field of node
 * @raqm: index of node which used be elhistory
 *
 * Return: size of list
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
	new_head -> raqm = raqm;
	if (stfield)
	{
		new_head -> stfield = _strdup(stfield);
		if (!new_head -> stfield)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head -> next = *addpoint;
	*addpoint = new_head;
	return (new_head);
}

/**
 * add_node_end - edaft node fe nhayet ellist
 * @addpoint: enwan elpointer bta3 elhead node
 * @stfield: str field of node
 * @raqm: index of node which used be elhistory
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **addpoint, const char *stfield, int raqm)
{
	list_t *new_node, *node;

	if (!addpoint)
		return (NULL);

	node = *addpoint;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node -> raqm = raqm;
	if (stfield)
	{
		new_node -> stfield = _strdup(stfield);
		if (!new_node -> stfield)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*addpoint = new_node;
	return (new_node);
}

/**
 * print_list_str - betb3 bs str list_t bta3 list
 * @x: pointer awel node fe elfunction
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *x)
{
	size_t i = 0;

	while (x)
	{
		_puts(x->stfield ? x->stfield : "(nil)");
		_puts("\n");
		x = x->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - nmsa7 elnode feha inteex
 * @addpoint: enwan awel pointer fe elnode
 * @inteex: elinteex of node which will be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **addpoint, unsigned int inteex)
{
	list_t *noote, *prev_noote;
	unsigned int i = 0;

	if (!addpoint || !*addpoint)
		return (0);

	if (!inteex)
	{
		noote = *addpoint;
		*addpoint = (*addpoint)->next;
		free(noote->stfield);
		free(noote);
		return (1);
	}
	noote = *addpoint;
	while (noote)
	{
		if (i == inteex)
		{
			prev_noote->next = noote->next;
			free(noote->stfield);
			free(noote);
			return (1);
		}
		i++;
		prev_noote = noote;
		noote = noote->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @heaptr: enwan of ponter head noote
 *
 * Return: void
 */
void free_list(list_t **heaptr) {
    list_t *noote, *next_noote;

    if (!heaptr || !*heaptr)
        return;

    noote = *heaptr;
    while (noote) {
        next_noote = noote->next;
        free(noote->stfield);
        free(noote);
        noote = next_noote;
    }
    *heaptr = NULL;
}
