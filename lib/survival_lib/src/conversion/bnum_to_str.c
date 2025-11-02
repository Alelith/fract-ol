/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnum_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:00:35 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 22:29:20 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file bnum_to_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the bnum_to_str function.
 */

/**
 * @brief Get the of digits and signs that a number contains.
 * 
 * @param nbr The number to evaluate.
 * @param base The base for conversion (e.g., 2 for binary, 10 for decimal,
 *  16 for hexadecimal).
 * 
 * @return The length of the number.
 */
static int	bnum_len(int nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

/**
 * @brief Converts an integer to a string in a specified base.
 * @ingroup conversion_functions
 * 
 * @param n The integer to convert.
 * @param base The base for conversion (e.g., 2 for binary, 10 for decimal,
 *  16 for hexadecimal).
 * @param is_upper If non-zero, use uppercase letters for bases greater than 10.
 * 
 * @return A pointer to the string representation of the integer in
 *  the specified base.
 * @warning Needs to be freed after use.
 */
char	*bnum_to_str(int n, int base, int is_upper)
{
	const char	*digits;
	char		*result;
	int			i;
	int			length;

	if (is_upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	length = bnum_len(n, base);
	i = length - 1;
	result = (char *)malloc(length + 1);
	if (!result)
		return (0);
	if (n == 0)
		result[i--] = '0';
	while (n > 0)
	{
		result[i--] = digits[n % base];
		n /= base;
	}
	result[length] = '\0';
	return (result);
}
