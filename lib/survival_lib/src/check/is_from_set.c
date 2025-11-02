/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_from_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:44:17 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:22:24 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_from_set.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the is_from_set function.
 */

/** 
 * @brief Checks if the character is in a specified set.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * @param set The set to compare.
 * 
 * @retval 1 if the character is contained in the set.
 * @retval 0 if the character is not contained in the set.
 */
int	is_from_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}
