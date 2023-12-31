#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @FD: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *FD, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (FD[0] == 0 || FD == NULL)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; FD[i] != '\0'; i++)
		if (!is_delim(FD[i], d) && (is_delim(FD[i + 1], d) || !FD[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(FD[i], d))
			i++;
		k = 0;
		while (!is_delim(FD[i + k], d) && FD[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = FD[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @FD: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *FD, char d[10])
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (d[0] == 0 || FD == NULL)
		return (NULL);
	for (i = 0; FD[i] != '\0'; i++)
		if ((FD[i] != *d && FD[i + 1] == *d) ||
		    (FD[i] != *d && !FD[i + 1]) || FD[i + 1] == *d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (FD[i] == *d && FD[i] != *d)
			i++;
		k = 0;
		while (FD[i + k] != *d && FD[i + k] && FD[i + k] != *d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = FD[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
