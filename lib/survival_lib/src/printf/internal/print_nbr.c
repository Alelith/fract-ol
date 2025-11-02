/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:48:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:01:32 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_internal.h"

/**
 * @file print_nbr.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the print_nbr function.
 */

/**
 * @brief Prints a number in a specified format.
 * @ingroup print_functions
 * 
 * @param args The argument list containing the value to print.
 * @param format The format specifier ('d', 'i', 'u', 'x', 'X', 'p', 'f', 'o').
 * 
 * @return The number of characters printed.
 */
int	print_nbr(va_list args, char format)
{
	char	*str;
	int		len;

	len = 0;
	str = 0;
	if (format == 'd' || format == 'i')
		str = int_to_str(va_arg(args, int));
	else if (format == 'u')
		str = uint_to_str((unsigned int)va_arg(args, int));
	else if (format == 'x' || format == 'X')
		str = bnum_to_str(va_arg(args, unsigned int), 16, format == 'X');
	else if (format == 'p')
	{
		len += print_str("0x", 0);
		str = bnum_to_str((unsigned long)va_arg(args, void *), 16, 0);
	}
	else if (format == 'f')
		str = float_to_str((float)va_arg(args, double), 6);
	else if (format == 'o')
		str = bnum_to_str((unsigned int)va_arg(args, int), 8, 0);
	if (!str)
		return (0);
	len += print_str(str, 0);
	free(str);
	return (len);
}
