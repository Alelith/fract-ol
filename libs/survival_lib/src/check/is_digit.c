/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:09:48 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 21:55:57 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_digit.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_digit function.
 */

/** 
 * @brief Checks if the character is a digit.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is a digit.
 * @retval 0 if the character is not a digit.
 */
int	is_digit(int c)
{
	return (c >= 48 && c <= 57);
}
