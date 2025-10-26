/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:51:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 22:32:22 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file str_to_uint.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_to_uint function.
 */

/**
 * @brief Converts a string to an unsigned integer.
 * @ingroup conversion_functions
 * 
 * @param nptr The string to convert.
 * 
 * @return The unsigned integer representation of the string.
 */
unsigned int	str_to_uint(const char *nptr)
{
	unsigned int	result;

	result = 0;
	while (*nptr)
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}
