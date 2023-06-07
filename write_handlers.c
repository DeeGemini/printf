#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';

		for (i = 0; i < width - 1; i++)
		buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) +
			write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
			write(1, &buffer[0], 1));
		}
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 1)
	{
		buffer[ind] = padd;
		return (write(1, &buffer[ind], 1));
	}

	if (width < length)
		width = length;

	if (width > BUFF_SIZE - 1)
		width = BUFF_SIZE - 1;

		buffer[BUFF_SIZE - 1] = '\0';

	if (flags & F_MINUS)
	{
		buffer[ind] = extra_c;

		for (i = ind + 1; i < BUFF_SIZE - 1; i++)
		buffer[i] = padd;

		padd_start = 0;
	}
	else
	{
		for (i = ind; i < BUFF_SIZE - 1 - width + ind + padd_start; i++)
		buffer[i] = padd;

		buffer[i] = extra_c;
	}

	return (write(1, &buffer[ind], BUFF_SIZE - ind - padd_start));
}

/************************* WRITE UNSIGNED *************************/

/**
 * write_unsgnd - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
	UNUSED(is_negative);
	UNUSED(precision);
	UNUSED(size);

	return (write_num(ind, buffer, flags, width, 0,
		BUFF_SIZE - ind - 1, ' ', 0));
}

/************************* WRITE POINTER *************************/

/**
 * write_pointer - Prints a string
 * @buffer: Buffer array to handle print
 * @ind: char types.
 * @length: Number length
 * @width: get width.
 * @flags: Calculates active flags
 * @padd: Pading char
 * @extra: Extra char
 * @padd_start: Index where padding should start.
 *
 * Return: Number of chars printed.
 */
int write_pointer(char buffer[], int ind, int length, int width,
int flags, char padd, char extra, int padd_start)
{
	int i;

	buffer[ind] = extra;

	for (i = ind + 1; i < BUFF_SIZE - 1 - width + ind + padd_start; i++)
	buffer[i] = padd;

	buffer[i++] = '0';
	buffer[i] = 'x';

	return (write(1, &buffer[ind], BUFF_SIZE - ind - padd_start));
}
