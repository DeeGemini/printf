#include "main.h"
/**
 * handle_print - prints argument based on type
 * @fmt: arranged string to print the arguments
 * @list: arguments to be printed
 * @ind: indicator
 * @buffer: Buffer array to operate print
 * @flags: computes active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: 1 or 2
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int unknow_len = 0;
	int printed_chars = -1;

	switch (fmt[*ind])
	{
		case 'c':
			return (print_char(list, buffer, flags, width, precision, size));
		case 's':
			return (print_string(list, buffer, flags, width, precision, size));
		case '%':
			return (print_percent(list, buffer, flags, width, precision, size));
		case 'i':
		case 'd':
			return (print_int(list, buffer, flags, width, precision, size));
		case 'b':
			return (print_binary(list, buffer, flags, width, precision, size));
		case 'u':
			return (print_unsigned_int(list, buffer, flags, width, precision, size));
		case 'o':
			return (print_octal(list, buffer, flags, width, precision, size));
		case 'x':
			return (print_hexadecimal(list, buffer, flags, width, precision, size));
		case 'X':
			return (print_hexa_upper(list, buffer, flags, width, precision, size));
		case 'p':
			return (print_pointer(list, buffer, flags, width, precision, size));
		case 'S':
			return (print_non_printable(list, buffer, flags, width, precision, size));
		case 'r':
			return (print_reverse(list, buffer, flags, width, precision, size));
		case 'R':
			return (print_rot13string(list, buffer, flags, width, precision, size));
		case '\0':
			return (-1);
		default:
			return (handle_unknown(fmt, ind, buffer));
	}

	return (printed_chars);
}

/**
 * handle_unknown - holds the unknown
 * @fmt: arranged string to print the arguments
 * @ind: indicator
 * @buffer: Buffer array to operate print
 * Return: 1
 */

int handle_unknown(const char *fmt, int *ind, char buffer[])
{
	int unknow_len = 0;

	unknow_len += write(1, "%%", 1);
	if (fmt[*ind - 1] == ' ')
		unknow_len += write(1, " ", 1);
	else if (width)
	{
		--(*ind);
		while (fmt[*ind] != ' ' && fmt[*ind] != '%')
			--(*ind);
		if (fmt[*ind] == ' ')
			--(*ind);
		return (1);
	}
	unknow_len += write(1, &fmt[*ind], 1);
	return (unknow_len);
}


