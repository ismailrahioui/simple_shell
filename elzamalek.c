#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @soso: string whose length to chck
 *
 * Return: integer length of string
 */
int _strlen(char *soso)
{
	int u = 0;

	if (!soso)
		return (0);

	while (*soso++)
		u++;
	return (u);
}

/**
 * _strcmp - prfroom lexico comparison of two straangs
 * @soso1: the first one
 * @soso2: the second two
 *
 * Return: negative if soso1 < soso2,
 * positive if soso1 > soso2, zero if soso1 == soso2
 */
int _strcmp(char *soso1, char *soso2)
{
	while (*soso1 && *soso2)
	{
		if (*soso1 != *soso2)
			return (*soso1 - *soso2);
		soso1++;
		soso2++;
	}
	if (*soso1 == *soso2)
		return (0);
	else
		return (*soso1 < *soso2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystuck: elstring bta3 elsearch
 * @noodle: elsubstring elmatlob
 *
 * Return: enwan of next harf el haystack or NULL
 */
char *starts_with(const char *haystuck, const char *noodle)
{
	while (*noodle)
		if (*noodle++ != *haystuck++)
			return (NULL);
	return ((char *)haystuck);
}

/**
 * _strcat - concatenates two strings
 * @desk: masafet el buffer
 * @src: masdar el buffer
 *
 * Return: pinter to destination bffer
 */
char *_strcat(char *desk, char *srk)
{
	char *rat = desk;

	while (*desk)
		desk++;
	while (*srk)
		*desk++ = *srk++;
	*desk = *srk;
	return (rat);
}
