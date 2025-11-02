/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:45:17 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:32:10 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_internal.h"

/**
 * @file print_nbr.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the print_nbr function.
 */

/**
 * @brief Switch the specified format to print.
 * 
 * @param args Variadric list with the data to format.
 * @param format Type of format that will be represented.
 * 
 * @return The amount of characters printed.
 */
static int	proccess_format(va_list args, char format)
{
	int		len;

	len = 0;
	if (format == '%')
		len = print_str(0, '%');
	else if (format == 'd' || format == 'i' || format == 'u' || format == 'x'
		|| format == 'X' || format == 'p' || format == 'f' || format == 'o')
		len = print_nbr(args, format);
	else if (format == 's')
		len = print_str(va_arg(args, char *), 0);
	else if (format == 'c')
		len = print_str(0, (char)va_arg(args, int));
	return (len);
}

/**
 * @brief Checks if the format specified is valid.
 * 
 * @param format The format to evaluate.
 * 
 * @retval 1 if the format is valid.
 * @retval 0 if the format is not valid.
 */
static int	is_valid_format(char format)
{
	return (format == '%' || format == 'd' || format == 'i'
		|| format == 'u' || format == 'x' || format == 'X'
		|| format == 'p' || format == 'f' || format == 'o'
		|| format == 's' || format == 'c');
}

/**
 * @brief Print a string with the data in the specified format to standar output.
 * @ingroup print_functions
 * 
 * @param format The string of the format that will be printed.
 * 
 * @return The amount of character printed
 */
int	print_format(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && is_valid_format(*(format + 1)))
		{
			format++;
			len += proccess_format(args, *format);
			format++;
		}
		else
		{
			write(1, format, 1);
			format++;
			len++;
		}
	}
	va_end(args);
	return (len);
}
