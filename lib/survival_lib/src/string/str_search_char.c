/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:34:53 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 19:00:53 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_search_char.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_search_char function.
 */

/**
 * @brief Searches for the first occurrence of a character in a string.
 * @ingroup string_functions
 * 
 * @param s The string to search.
 * @param c The character to search for.
 * 
 * @return A pointer to the first occurrence of the character in the string.
 * @retval NULL if the character not found.
 */
char	*str_search_char(const char *s, int c)
{
	return (mem_search(s, c, str_len(s) + 1));
}
