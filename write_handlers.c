#include "main.h"
#include <unistd.h>

/**
 * handle_write_char - produces a string
 * @c: char types
 * @buffer: Buffer array to operate print
 * @flags: Computes active flags
 * @width: width
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */

int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	char padd = ' ';

	switch (flags & F_ZERO)
	{
		case F_ZERO:
			padd = '0';
			break;
		default:
			padd = ' ';
			break;
	}

	buffer[0] = c;
	buffer[1] = '\0';

	if (width > 1)
	{
		int paddingCount = width - 1;

		for (int i = 0; i < paddingCount; i++)
		{
			buffer[i + 1] = padd;
		}
		switch (flags & F_MINUS)
		{
			case F_MINUS:
				return (write((1, &buffer[0], 1) + write(1, &buffer[1], paddingCount)));
			default:
				return (write(1, &buffer[1], paddingCount) + write(1, &buffer[0], 1));
		}
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - produces a string
 * @is_negative: List of arguments
 * @ind: char types
 * @buffer: Buffer array to handle print
 * @flags: Computes active flags
 * @width: width
 * @precision: precision specifier
 * @size: Size specifier
 * Return: no of chars printed
 */

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ';
	char extra_ch = 0;

	UNUSED(size);

	switch (flags & (F_ZERO | F_MINUS))
	{
		case F_ZERO:
			padd = '0';
			break;
		case F_MINUS:
			padd = ' ';
			break;
		default:
			break;
	}
	switch (is_negative)
	{
		case 1:
			extra_ch = '-';
			break;
		default:
			break;
	}
	switch (flags & (F_PLUS | F_SPACE))
	{
		case F_PLUS:
			extra_ch = '+';
			break;
		case F_SPACE:
			extra_ch = ' ';
			break;
		default:
			break;
	}
	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - produces a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: value of length
 * @padd: Pading char
 * @extra_c: Extra char
 * Return: no of chars printed
 */

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	switch (prec)
	{
		case 0:
			if (ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
				return (0);
			if (ind == BUFF_SIZE - 2 && buffer[ind] == '0')
				buffer[ind] = padd = ' ';
			break;
		default:
			if (prec > 0 && prec < length)
				padd = ' ';
			break;
	}

	while (prec > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if (extra_c != 0)
		length++;

	if (width > length)
	{
		return (handle_width(ind, buffer, flags, width, length, padd, extra_c));
	}

	if (extra_c)
		buffer[--ind] = extra_c;

	return (write(1, &buffer[ind], length));
}

/**
 * handle_width - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @length: no length
 * @padd: Pading char
 * @extra_c: Extra char
 * Return: 0 success
 */

int handle_width(int ind, char buffer[],
	int flags, int width, int length,
	char padd, char extra_c)
{
	int i, padd_start = 1;

	for (i = 1; i < width - length + 1; i++)
		buffer[i] = padd;
	buffer[i] = '\0';

	if (flags & F_MINUS && padd == ' ')
	{
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
	}
	else if (!(flags & F_MINUS) && padd == ' ')
	{
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
	}
	else if (!(flags & F_MINUS) && padd == '0')
	{
		if (extra_c)
			buffer[--padd_start] = extra_c;
		return (write(1, &buffer[padd_start], i - padd_start) +
			write(1, &buffer[ind], length - (1 - padd_start)));
	}

	return (0);
}


/**
 * write_unsgnd - produces an unsigned number
 * @is_negative: no indicating if the num is negative
 * @ind: Index no in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: no of chars printed
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	padd = (flags & F_ZERO && !(flags & F_MINUS)) ? '0' : padd;
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - prints a memory address
 * @buffer: Arrays of chars
 * @ind: Index number in the buffer
 * @length: value of length
 * @width: Width specifier
 * @extra_c: Char representing extra char
 * Return: Number of written chars
 */

int write_pointer(char buffer[], int ind,
		int length, int width, char extra_c)
{
	if (width > length)
	{
		return (handle_width(ind, buffer, length, width, extra_c));
	}

	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

/**
 * handle_width - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of no
 * @width: Width
 * @flags: Flags
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * Return: No of written chars
 */

int handle_width(int ind, char buffer[],
		int flags, int width, int length,
		char padd, char extra_c)
{
	int i;

	for (i = 3; i < width - length + 3; i++)
		buffer[i] = padd;
	buffer[i] = '\0';

	switch (padd)
	{
		case ' ':
			if (flags & F_MINUS)
			{
				buffer[--ind] = 'x';
				buffer[--ind] = '0';
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
			}
			else
			{
				buffer[--ind] = 'x';
				buffer[--ind] = '0';
				if (extra_c)
					buffer[--ind] = extra_c;
				return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
			}
			break;
		case '0':
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
			break;
		default:
			break;
	}
}


