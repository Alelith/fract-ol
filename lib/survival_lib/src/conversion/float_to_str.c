/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:26:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 10:23:19 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file float_to_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the float_to_str function.
 */

/**
 * @brief Calculates the total length needed to represent a float as a string.
 * 
 * @param nbr The float number to evaluate.
 * @param decimals The number of decimal places to include.
 * 
 * @return The total length required to represent the float as a string.
 */
static int	float_len(float nbr, int decimals)
{
	int		len;
	int		int_part;

	len = 0;
	if (nbr < 0.0f)
	{
		len++;
		nbr = -nbr;
	}
	int_part = (int)nbr;
	if (int_part == 0)
		len++;
	while (int_part > 0)
	{
		int_part /= 10;
		len++;
	}
	len++;
	len += decimals;
	return (len);
}

/**
 * @brief Fill the decimal digits (left-to-right) and place the decimal point.
 * 
 * @param result The string to fill.
 * @param frac_part The fractional part of the float number.
 * @param decimals The number of decimal places to include.
 * @param length The total length of the resulting string.
 * 
 * @return The index of the last position available for the integer part
 * (i.e. position where the least-significant integer digit should be placed).
 */
static int	fill_decimal_part(char *result, float frac_part,
					int decimals, int length)
{
	int	pos;
	int	k;
	int	digit;

	pos = length - decimals;
	k = 0;
	while (k < decimals)
	{
		frac_part *= 10.0f;
		digit = (int)frac_part;
		result[pos + k] = digit + '0';
		frac_part -= digit;
		k++;
	}
	result[pos - 1] = '.';
	return (pos - 2);
}

/**
 * @brief Fill the integer digits right-to-left into result ending at end_idx.
 * 
 * @param result The string to fill.
 * @param int_part The integer part of the float number.
 * @param end_idx The ending index in the string to start filling from.
 */
static void	fill_integer_part(char *result, int int_part, int end_idx)
{
	if (int_part == 0)
	{
		result[end_idx] = '0';
		return ;
	}
	while (int_part > 0)
	{
		result[end_idx] = (int_part % 10) + '0';
		end_idx--;
		int_part /= 10;
	}
}

/**
 * @brief Fill the string with both integer and decimal parts of the float.
 * 
 * @param result The string to fill.
 * @param nbr The float number to convert.
 * @param decimals The number of decimal places to include.
 * @param length The total length of the resulting string.
 */
static void	fill_float_str(char *result, float nbr, int decimals, int length)
{
	int		int_part;
	float	frac_part;
	int		end_idx;

	int_part = (int)nbr;
	frac_part = nbr - int_part;
	end_idx = fill_decimal_part(result, frac_part, decimals, length);
	fill_integer_part(result, int_part, end_idx);
}

/**
 * @brief Converts a float to a string with specified decimal places.
 * @ingroup conversion_functions
 * 
 * @param n The float number to convert.
 * @param decimals The number of decimal places to include in the result.
 * 
 * @return A pointer to the newly allocated string representation of the float.
 * @retval NULL if memory allocation failed.
 * @warning Needs to be freed after use.
 */
char	*float_to_str(float n, int decimals)
{
	int		length;
	char	*result;

	length = float_len(n, decimals);
	result = malloc(length + 1);
	if (!result)
		return (0);
	result[length] = '\0';
	if (n < 0.0f)
	{
		result[0] = '-';
		n = -n;
	}
	fill_float_str(result, n, decimals, length);
	return (result);
}
