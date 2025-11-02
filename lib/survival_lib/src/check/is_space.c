/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:22:49 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 22:01:24 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_space.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_space function.
 */

/**
 * @brief Checks if the character is a space character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is space.
 * @retval 0 if the character is not space.
 */
int	is_space(char c)
{
	return ((c <= 13 && c >= 9) || c == 32);
}
