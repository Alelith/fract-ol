/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:22:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:31:21 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file mem_move.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_move function.
 */

/**
 * @brief Moves memory from one block to another.
 * @ingroup memory_functions
 * 
 * @param dest The destination memory block.
 * @param src The source memory block.
 * @param n The number of bytes to move.
 * 
 * @return A pointer to the destination memory block.
 */
void	*mem_move(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if ((!dest || !src) && n > 0)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	if (dest >= src && dest <= src + n)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
		mem_copy(dest, src, n);
	return (dest);
}
