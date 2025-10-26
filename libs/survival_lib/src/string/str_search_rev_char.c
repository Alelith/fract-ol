/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_rev_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:15 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:44:56 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_search_rev_char.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_search_rev_char 
 * function.
 */

/**
 * @brief Searches for the last occurrence of a character in a string.
 * @ingroup string_functions
 * 
 * @param s The string to search.
 * @param c The character to search for.
 * 
 * @return A pointer to the last occurrence of the character in the string.
 * @retval NULL if the character was not found.
 */
char	*str_search_rev_char(const char *s, int c)
{
	const char	*ini_s;

	ini_s = s;
	c = c % 256;
	s += str_len(s) - 1;
	if (c == '\0')
		return ((char *)s + 1);
	while (s >= ini_s)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	return (0);
}
