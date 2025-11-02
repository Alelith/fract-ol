/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:27:42 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:43:23 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_trim.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_trim function.
 */

/**
 * @brief Removes leading and trailing characters from a string.
 * @ingroup string_functions
 * 
 * @param s1 The string to trim.
 * @param set The set of characters to remove from the beginning and end.
 * 
 * @return A pointer to the trimmed string (newly allocated).
 * @retval NULL if the allocation failed.
 * @warning Needs to be freed after use.
 */
char	*str_trim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*result;

	if (!s1 || !set)
		return (0);
	end = str_len(s1) - 1;
	start = 0;
	while (s1[start] && is_from_set(s1[start], set))
		start++;
	while (start < end && is_from_set(s1[end], set))
		end--;
	result = str_substring(s1, start, end - start + 1);
	return (result);
}
