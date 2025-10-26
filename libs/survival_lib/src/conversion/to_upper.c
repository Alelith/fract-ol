/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_upper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:32:13 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:42:17 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file to_upper.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the to_upper function.
 */

/**
 * @brief Converts a character to uppercase.
 * @ingroup conversion_functions
 * 
 * @param c The character to convert.
 * 
 * @retval uppercase version of the character if it is alphabetic (a-z).
 * @retval c unchanged if it is not alphabetic.
 */
int	to_upper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
