#include "main.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @inf: the parameter & return inf struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(inf_t *inf, char *estr)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
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
 * @num: number
 * @base: base
 * @flags: arg flags
 * Return: string converted
 */

char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	char arr[] = "0123456789ABCDEF";
	int isNegative = 0, i;

	if (num == 0)
	{ /*check for zero*/
		*--ptr = '0';
		return (ptr);
	}
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{ /*check for negative*/
		isNegative = 1;
		num = -num;
	}
	if (flags & CONVERT_LOWERCASE)
	{ /*convert to lowercase*/
		for (i = 0; i < 49; i++)
		{
			arr[i] += 32;
		}
	}
	while (num != 0)
	{ /*convert*/
		*--ptr = arr[num % base];
		num /= base;
	}
	/*change sign*/
	if (isNegative == 1)
		*--ptr = '-';
	return (ptr);
}

/**
 * remove_comments - replaces first instance of '#' with '\0'
 * @buffer: string
 * Return: void
 */

void remove_comments(char *buffer)
{
	int i;

	/*loop through and look for comment*/
	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#')
		{
			if (!i || buffer[i - 1] == ' ')
			{ /*!i check if index is zero*/
				buffer[i] = '\0';
				break;
			}
		}
	}
}

