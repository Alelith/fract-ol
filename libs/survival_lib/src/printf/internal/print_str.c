/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:46:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:04:37 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_internal.h"

/**
 * @file print_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the print_str function.
 */

/**
 * @brief Prints a string or a char.
 * @ingroup print_functions
 * 
 * @param str The string to print.
 * @param c The char to print.
 * 
 * @return The number of characters printed.
 */
int	print_str(const char *str, char c)
{
	int	len;

	len = 0;
	if (str)
	{
		len = str_len(str);
		write(1, str, len);
	}
	else if (c)
	{
		len = 1;
		write (1, &c, 1);
	}
	return (len);
}
