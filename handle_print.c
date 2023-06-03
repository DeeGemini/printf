#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments
 * @list: List of arguments to be printed
 * @i: current index of the formatted string.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *i, va_list list, char buffer[],
	      int flags, int width, int precision, int size)
{
	int p, unknown_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'u', print_unsigned}, {'b', print_binary},
		{'o', print_octal}, {'i', print_int}, {'x', print_hexadecimal},
		{'%', print_percent}, {'d', print_int}, {'X', print_hexa_upper},
		{'s', print_string}, {'p', print_pointer}, {'R', print_rot13string},
		{'r', print_reverse}, {'S', point_non_printable}, {'\0', NULL}
	};
	for (p = 0; fmt_types[p].fmt != '\0'; p++)
		if (fmt[*i] == fmt_types[p].fmt)
			return (fmt_types[p].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[p].fmt == '\0')
	{
		if (fmt[*i] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);

		if (fmt[*i - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (fmt[*i] != ' ' && fmt[*i] != '%')
				--(*i);
			if (fmt[*i] == ' ')
				--(*i);
			return (1);
		}
		unknown_len += write(1, &fmt[*i], 1);
		return (unknown_len);
	}
	return (printed_chars);
}
