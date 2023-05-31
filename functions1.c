#include "main.h"

/************************* PRINTF *************************/
/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format)
	{
	if (*format == '%')
	{
		format++;
		switch (*format)
		{
		case 'c':
			count += print_char(args);
			break;
		case 's':
			count += print_string(args);
			break;
		case '%':
			count += print_percent(args);
			break;
		case 'd':
		case 'i':
			count += print_int(args);
			break;
		case 'b':
			count += print_binary(args);
			break;
		default:
			putchar('%');
			putchar(*format);
			count += 2;
			break;
		}
	}
	else
	{
		putchar(*format);
		count++;
	}
	format++;
	}

	va_end(args);

	return (count);
}

/************************* EXAMPLE USAGE *************************/

int main(void)
{
	_printf("Character: %c\n", 'A');
	_printf("String: %s\n", "Hello, World!");
	_printf("Percent sign: %%\n");
	_printf("Integer: %d\n", 12345);
	_printf("Binary: %b\n", 42);

	return (0);
}

