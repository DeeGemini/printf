#include “main.h”

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List of arguments
 * Return: Number of chars printed
 */
int print_char(va_list types)
{
	char c = va_arg(types, int);

	putchar(c);
	return (1);
}

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List of arguments
 * Return: Number of chars printed
 */
int print_string(va_list types)
{

	char *str = va_arg(types, char *);

	if (str == NULL)
	str = "(null)";
	printf("%s", str);
	return (strlen(str));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * Return: Number of chars printed
 */
int print_percent(va_list types)
{
	putchar('%');
	return (1);
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: List of arguments
 * Return: Number of chars printed
 */
int print_int(va_list types)
{

	int n = va_arg(types, int);

	printf("%d", n);
	return (1);
}

/************************* PRINT BINARY *************************/
/**
* print_binary - Prints an unsigned number in binary format
 * @types: List of arguments
 * Return: Number of chars printed
 */
int print_binary(va_list types)
{
	unsigned int n = va_arg(types, unsigned int);
	int count = 0;

	if (n == 0)
	{
	putchar('0');
	return (1);
	}

	unsigned int mask = 1U << (sizeof(unsigned int) * 8 - 1);
	int leading_zeros = 1;

	while (mask)
	{
	if (n & mask)
		leading_zeros = 0;

	if (!leading_zeros)
	{
		putchar((n & mask) ? '1' : '0');
		count++;
	}

	mask >>= 1;
	}

	return (count);
}
