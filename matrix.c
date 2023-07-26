#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @seen: li ghadi yetbadel 
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *seen)
{
	int i = 0;
	unsigned long int res = 0;

	if (*seen == '+')
		seen++;  /* TODO: why does this make main return 255? */
	for (i = 0;  seen[i] != '\0'; i++)
	{
		if (seen[i] >= '0' && seen[i] <= '9')
		{
			res *= 10;
			res += (seen[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @tach: param 
 * @tesr: chi unique 
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *tach, char *tesr)
{
	_eputs(tach->fname);
	_eputs(": ");
	print_d(tach->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(tach->argv[0]);
	_eputs(": ");
	_eputs(tesr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @value: value 
 * @bet: file
 *
 * Return: number of characters printed
 */
int print_d(int value, int bet)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (bet == STDERR_FILENO)
		__putchar = _eputchar;
	if (value < 0)
	{
		_abs_ = -value;
		__putchar('-');
		count++;
	}
	else
		_abs_ = value;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @numero: number
 * @bas: base
 * @signes: les signes 
 *
 * Return: string
 */
char *convert_number(long int numero, int bas, int signes)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numero;

	if (!(signes & CONVERT_UNSIGNED) && numero < 0)
	{
		n = -numero;
		sign = '-';

	}
	array = signes & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bas];
		n /= bas;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @bu: adress deyl hadak li tbadel 
 * Return: Always 0;
 */
void remove_comments(char *bu)
{
	int i;

	for (i = 0; bu[i] != '\0'; i++)
		if (bu[i] == '#' && (!i || bu[i - 1] == ' '))
		{
			bu[i] = '\0';
			break;
		}
}
