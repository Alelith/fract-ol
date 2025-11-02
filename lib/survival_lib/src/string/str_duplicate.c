/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:16:25 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:51:29 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_duplicate.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_duplicate function.
 */

/**
 * @brief Create a duplicate of a string.
 * @ingroup string_functions
 * 
 * @param s The string to duplicate.
 * 
 * @return A pointer to the duplicated string, or NULL if the allocation failed.
 * Needs to be freed after use.
 */
char	*str_duplicate(const char *s)
{
	char	*result;

	if (!s)
		return (0);
	result = malloc(str_len(s) + 1);
	if (!result)
		return (0);
	str_copy(result, s, str_len(s) + 1);
	return (result);
}
