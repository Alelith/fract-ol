/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:13:27 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 21:56:06 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_print.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_print function.
 */

/**
 * @brief Checks if the character is a printable character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is printable.
 * @retval 0 if the character is not printable.
 */
int	is_print(int c)
{
	return (c >= 32 && c <= 126);
}
