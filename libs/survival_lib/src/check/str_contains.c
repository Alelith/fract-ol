/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:23:33 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:43:33 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_contains.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_contains function.
 */

/**
 * @brief Checks if a string contains any character from a specified set.
 * @ingroup check_functions
 * 
 * @param str The string to search.
 * @param set The set of characters to look for.
 * 
 * @retval 1 if the string contains at least one character from the set.
 * @retval 0 if the string contains no characters from the set.
 */
int	str_contains(char *str, char *set)
{
	while (str && *str)
	{
		if (is_from_set(*str, set))
			return (1);
		str++;
	}
	return (0);
}
