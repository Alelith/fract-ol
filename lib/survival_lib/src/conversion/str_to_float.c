/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:25:29 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 10:15:01 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file str_to_float.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_to_float function.
 */

/**
 * @brief Gets the decimal numbers of a string.
 * 
 * @param nptr The pointer to the string to read.
 * 
 * @return The decimal representation on the string.
 */
static float	parse_decimal(const char *nptr)
{
	float	result;
	float	decimal_place;

	result = 0.0f;
	decimal_place = 0.1f;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result += (*nptr - '0') * decimal_place;
		decimal_place *= 0.1f;
		nptr++;
	}
	return (result);
}

/**
 * @brief Converts a string to a float.
 * @ingroup conversion_functions
 * 
 * @param nptr The string to convert.
 * 
 * @return The float representation of the string.
 */
float	str_to_float(const char *nptr)
{
	int		sign;
	float	result;

	sign = 1;
	result = 0.0f;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10.0f) + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		result += parse_decimal(nptr);
	}
	return (result * sign);
}
