#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Produces output according to a format.
 * @format: The format string.
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;

	if (format == NULL)
		return (-1);

	va_start(args, format);
	printed_chars = handle_print(format, &args);
	va_end(args);

	return (printed_chars);
}

/**
 * handle_print - Handles the format string and prints the output.
 * @format: The format string.
 * @args: The variable argument list.
 *
 * Return: The number of characters printed.
 */
int handle_print(const char *format, va_list *args)
{
	int i = 0;
	int printed_chars = 0;
	char buffer[BUFF_SIZE] = {'\0'};
	int flags = 0;
	int width = 0;
	int precision = -1;
	int size = 0;

	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			flags = get_flags(format, &i);
			width = get_width(format, &i, *args);
			precision = get_precision(format, &i, *args);
			size = get_size(format, &i);
			if (format[i] == '\0')
				return (-1);
			if (format[i] == '%')
				printed_chars += print_percent(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'c' || format[i] == 's')
				printed_chars += handle_write_char(va_arg(*args, int), buffer, flags, width, precision, size);
			else if (format[i] == 'd' || format[i] == 'i')
				printed_chars += print_int(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'b')
				printed_chars += print_binary(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'u')
				printed_chars += print_unsigned(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'o')
				printed_chars += print_octal(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'x' || format[i] == 'X')
				printed_chars += print_hexadecimal(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'S')
				printed_chars += print_non_printable(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'p')
				printed_chars += print_pointer(*args, buffer, flags, width, precision, size);
			else if (format[i] == 'R')
				printed_chars += print_rot13string(*args, buffer, flags, width, precision, size);
			else
				printed_chars += write_num(i - 1, (char *)format, flags, width, precision, 0, ' ', format[i]);
			i++;
		}
		else
		{
			printed_chars += write_num(i, (char *)format, flags, width, precision, 0, ' ', format[i]);
			i++;
		}
	}
	write(1, buffer, printed_chars);
	return (printed_chars);
}
