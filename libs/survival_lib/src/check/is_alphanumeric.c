/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alphanumeric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:12:09 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/24 21:55:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file is_alphanumeric.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_alphanumeric function.
 */

/**
 * @brief Checks if the character is an alphanumeric character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @retval 1 if the character is alphanumeric.
 * @retval 0 if the character is not alphanumeric.
 */
int	is_alphanumeric(int c)
{
	return (is_alphabetic(c) || is_digit(c));
}
