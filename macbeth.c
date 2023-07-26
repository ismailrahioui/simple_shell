#include "shell.h"

/**
 *_eputs - prints an input string
 * @storz: string li ghadi nkatbo 
 *
 * Return: Nothing
 */
void _eputs(char *storz)
{
	int i = 0;

	if (!storz)
		return;
	while (storz[i] != '\0')
	{
		_eputchar(storz[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @cur: char li ghadi nkatbo lih 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char cur)
{
	static int i;
	static char bu[WRITE_BUF_SIZE];

	if (cur == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, bu, i);
		i = 0;
	}
	if (cur != BUF_FLUSH)
		bu[i++] = cur;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @mac: char li ghadi nkatbo 
 * @bet: l file li ghadi nkabto fih 
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char mac, int bet)
{
	static int i;
	static char bu[WRITE_BUF_SIZE];

	if (mac == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(bet, bu, i);
		i = 0;
	}
	if (mac != BUF_FLUSH)
		bu[i++] = mac;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @storz: string li ghadi yetakteb 
 * @bet: li ghadi nkatbo lih  to
 *
 * Return: the number of chars put
 */
int _putsfd(char *storz, int bet)
{
	int i = 0;

	if (!storz)
		return (0);
	while (*storz)
	{
		i += _putfd(*storz++, bet);
	}
	return (i);
}
