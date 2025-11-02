/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:36:44 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:44:45 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file mem_search.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_search function.
 */

/**
 * @brief Searches for a character in a memory block.
 * @ingroup memory_functions
 * 
 * @param s The memory block to search.
 * @param c The character to search for.
 * @param n The number of bytes to search.
 * 
 * @return A pointer to the first occurrence of the character 
 * in the memory block.
 * @retval NULL if the character was not found.
 */
void	*mem_search(const void *s, int c, size_t n)
{
	unsigned char	*src;

	if (!s)
		return (0);
	c = (unsigned char)c;
	src = (unsigned char *) s;
	while (n--)
	{
		if (*src == c)
			return (src);
		src++;
	}
	return (0);
}
