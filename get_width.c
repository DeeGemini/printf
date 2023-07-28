#include "main.h"

/**
 * get_width - computes the width for printing
 * @format: arranged string to print the arguments
 * @i: arguments to be printed
 * @list: arguments
 * Return: width
 */

int get_width(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int width = 0;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
			curr_i++;
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
	}

	*i = curr_i - 1;

	return (width);
}

