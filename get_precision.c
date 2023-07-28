#include "main.h"

/**
 * get_precision - computes the precision for printing
 * @format: arranged string to print the arguments
 * @i: arguments to be printed
 * @list: arguments
 * Return: precision
 */

int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;
	curr_i++;

	while (is_digit(format[curr_i]))
	{
		precision *= 10;
		precision += format[curr_i] - '0';
		curr_i++;
	}

	if (format[curr_i] == '*')
	{
		curr_i++;
		precision = va_arg(list, int);
	}

	*i = curr_i - 1;

	return (precision);
}

