/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ascii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:12:59 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 21:55:42 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_ascii.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_ascii function.
 */

/**
 * @brief Checks if the character is an ASCII character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is an ASCII character.
 * @retval 0 if the character is not an ASCII character.
 */
int	is_ascii(int c)
{
	return (c >= 0 && c <= 127);
}
