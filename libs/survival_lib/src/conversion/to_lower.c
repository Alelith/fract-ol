/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:33:36 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:42:14 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file to_lower.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the to_lower function.
 */

/**
 * @brief Converts a character to lowercase.
 * @ingroup conversion_functions
 * 
 * @param c The character to convert.
 * 
 * @retval lowercase version of the character if it is alphabetic (A-Z).
 * @retval c unchanged if it is not alphabetic.
 */
int	to_lower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
