#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
	return (-1);

	va_list args;

	va_start(args, format);

	int printed_chars = 0;
	char buffer[BUFF_SIZE];
	int buff_ind = 0;

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];

		if (buff_ind == BUFF_SIZE)
			print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
	else
	{
		print_buffer(buffer, &buff_ind);

		int flags = get_flags(format, &i);
		int width = get_width(format, &i, args);
		int precision = get_precision(format, &i, args);
		int size = get_size(format, &i);

		i++; /* Increment i to move past the '%' character */

		int printed = handle_print(format, &i, args, buffer, flags,
		width, precision, size);

		if (printed == -1)
		{
			va_end(args);
			return (-1);
		}
		printed_chars += printed;
	}
	}

	print_buffer(buffer, &buff_ind);
	va_end(args);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters containing the buffered output
 * @buff_ind: Pointer to the index indicating the length of the buffer
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, buffer, *buff_ind);

	*buff_ind = 0;
}
