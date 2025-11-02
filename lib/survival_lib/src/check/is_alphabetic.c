/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alphabetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:04:55 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 21:54:33 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_alphabetic.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_alphabetic function.
 */

/**
 * @brief Checks if the character is an alphabetic character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is alphabetic.
 * @retval 0 if the character is not alphabetic.
 */
int	is_alphabetic(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
