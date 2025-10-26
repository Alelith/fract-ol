/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:40:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 19:06:45 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_search_str.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_search_str function.
 */

/**
 * @brief Searches for the first occurrence of a substring in a string.
 * @ingroup string_functions
 * 
 * @param big The string to search.
 * @param little The substring to search for.
 * @param len The number of characters to search.
 * 
 * @return A pointer to the first occurrence of the substring in the string.
 * @retval NULL if the character not found.
 */
char	*str_search_str(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	j = 0;
	little_len = str_len(little);
	if (little_len == 0)
		return ((char *) big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			while (j < little_len && i + j < len
				&& big[i + j] == little[j])
				j++;
			if (j == little_len)
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (0);
}
