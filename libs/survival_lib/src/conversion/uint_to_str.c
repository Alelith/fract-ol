/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:53:01 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 22:27:53 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file uint_to_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the uint_to_str function.
 */

/**
 * @brief Get the of digits and signs that a number contains.
 * 
 * @param nbr The number to evaluate.
 * 
 * @return The length of the number.
 */
static int	uint_len(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

/**
 * @brief Converts an unsigned integer to a string.
 * @ingroup conversion_functions
 * 
 * @param n The unsigned integer to convert.
 * 
 * @return A pointer to the string representation of the unsigned integer.
 * @warning Needs to be freed after use.
 */
char	*uint_to_str(unsigned int n)
{
	char	*str;
	int		len;

	len = uint_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
