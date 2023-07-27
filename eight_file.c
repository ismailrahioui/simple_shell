#include "shell.h"

/**
 * _strcpy - copies a string
 * @desk: the destaniatioon
 * @srk: elsource bta3na
 *
 * Return: pointer to destianiatioon
 */
char *_strcpy(char *desk, char *srk)
{
	int u = 0;

	if (desk == srk || srk == 0)
		return (desk);
	while (srk[u])
	{
		desk[u] = srk[u];
		u++;
	}
	desk[u] = 0;
	return (desk);
}

/**
 * _strdup - duplicates a string
 * @stfield: elstring elduplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *stfield)
{
	int length = 0;
	char *rek;

	if (stfield == NULL)
		return (NULL);
	while (*stfield++)
		length++;
	rek = malloc(sizeof(char) * (length + 1));
	if (!rek)
		return (NULL);
	for (length++; length--;)
		rek[length] = *--stfield;
	return (rek);
}

/**
 *_puts - prints an input string
 *@stfield: string which will be printed
 *
 * Return: Nothing
 */
void _puts(char *stfield)
{
	int u = 0;

	if (!stfield)
		return;
	while (stfield[u] != '\0')
	{
		_putchar(stfield[u]);
		u++;
	}
}

/**
 * _putchar - writes the character k to stdout
 * @k: character which will be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char k)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buf, u);
		u = 0;
	}
	if (k != BUF_FLUSH)
		buf[u++] = k;
	return (1);
}
