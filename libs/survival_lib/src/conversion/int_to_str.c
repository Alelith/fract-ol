/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:27:17 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:43:34 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file int_to_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the int_to_str function.
 */

/**
 * @brief Calculates the number of digits and signs needed to represent a number.
 * 
 * @param nbr The number to evaluate.
 * 
 * @return The total length required to represent the number as a string.
 */
static int	int_len(int nbr)
{
	int	result;

	result = 0;
	if (nbr <= 0)
		result++;
	while (nbr != 0)
	{
		nbr /= 10;
		result++;
	}
	return (result);
}

/**
 * @brief Converts an integer to a string representation.
 * @ingroup conversion_functions
 * 
 * @param n The integer to convert.
 * 
 * @return A pointer to the newly allocated string representation of the integer.
 * @retval NULL if memory allocation failed.
 * @warning Needs to be freed after use.
 */
char	*int_to_str(int n)
{
	int		length;
	int		sign;
	char	*result;

	length = int_len(n);
	sign = 1;
	result = malloc(length + 1);
	if (!result)
		return (0);
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		sign = -1;
	}
	if (n == 0)
		result[0] = 48;
	while (n != 0)
	{
		result[length - 1] = sign * (n % 10) + 48;
		n /= 10;
		length--;
	}
	return (result);
}
