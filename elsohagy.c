#include "shell.h"

/**
 **_memset - bemly elmemory beconstant bytes
 *@soso: elpointer beta3t elmemory
 *@book: adad el bytes *soso
 *@noon: the amount of bytes to be filled
 *Return: (soso) a pointer to the memory area soso
 */
char *_memset(char *soso, char book, unsigned int noon)
{
	unsigned int u;

	for (u = 0; u < noon; u++)
		soso[u] = book;
	return (soso);
}

/**
 * ffree - freees elstrng elstrng
 * @poop: estrng elestrng
 */
void ffree(char **poop)
{
	char **apple = poop;

	if (!poop)
		return;
	while (*poop)
		free(*poop++);
	free(apple);
}

/**
 * _realloc - reeallocate blok of memory
 * @pter: pintr too abl elmalloc'ated blok
 * @osize: msahet elprevious blok
 * @nsize: msahet elnew blok
 *
 * Return: pintr to da ol'blok.
 */
void *_realloc(void *pter, unsigned int osize, unsigned int nsize)
{
	char *l;

	if (!pter)
		return (malloc(nsize));
	if (!nsize)
		return (free(pter), NULL);
	if (nsize == osize)
		return (pter);

	l = malloc(nsize);
	if (!l)
		return (NULL);

	osize = osize < nsize ? osize : nsize;
	while (old_size--)
		l[osize] = ((char *)pter)[osize];
	free(pter);
	return (l);
}
