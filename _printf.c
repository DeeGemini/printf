#include “main.h”

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	int buff_ind = 0;
	char buffer[BUFF_SIZE];
	va_list list;

	if (format == NULL)
	return (-1);

	va_start(list, format);

	for (int i = 0; format[i] != '\0'; i++)
	{
	if (format[i] != '%')
	{
		buffer[buff_ind++] = format[i];
		if (buff_ind == BUFF_SIZE - 1)
		{
		print_buffer(buffer, &buff_ind);
		printed_chars += buff_ind;
		}
	}
	else
	{
		print_buffer(buffer, &buff_ind);
		i++;	/* Skip the '%' */

		switch (format[i])
		{
		case 'd':
			printed_chars += printf("%d", va_arg(list, int));
			break;
		case 'f':
			printed_chars += printf("%f", va_arg(list, double));
			break;
		case 'c':
			printed_chars += printf("%c", va_arg(list, int));
			break;
		case 's':
			printed_chars += printf("%s", va_arg(list, char*));
			break;
		default:
			putchar('%');
			putchar(format[i]);
			printed_chars += 2;
		}
	}
	}

	print_buffer(buffer, &buff_ind);
	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
	buffer[*buff_ind] = '\0';
	printf("%s", buffer);
	}

	*buff_ind = 0;
}

