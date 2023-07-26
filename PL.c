#include "shell.h"

/**
 **_strncpy - copies a string
 *@dgst: fin ghadi ytcoppa str
 *@surc: soursa
 *@nun: che7al mn char ghadi ycopia
 *Return: string li tconnecta
 */
char *_strncpy(char *dgst, char *surc, int nun)
{
	int i, j;
	char *s = dgst;

	i = 0;
	while (surc[i] != '\0' && i < nun - 1)
	{
		dgst[i] = surc[i];
		i++;
	}
	if (i < nun)
	{
		j = i;
		while (j < nun)
		{
			dgst[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dgst: string lawel
 *@surc:  tani 
 *@nun: che7al mn byte daz
 *Return: string li rja3 
 */
char *_strncat(char *dgst, char *surc, int nun)
{
	int i, j;
	char *s = dgst;

	i = 0;
	j = 0;
	while (dgst[i] != '\0')
		i++;
	while (surc[j] != '\0' && j < nun)
	{
		dgst[i] = surc[j];
		i++;
		j++;
	}
	if (j < nun)
		dgst[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@sos: string li t7awel 
 *@cue: li kanqalbi elih 
 *Return: pointers 
 */
char *_strchr(char *sos, char cue)
{
	do {
		if (*sos == cue)
			return (sos);
	} while (*sos++ != '\0');

	return (NULL);
}
