/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:16:55 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:00:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file mem_set.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_set function.
 */

/**
 * @brief Sets a block of memory to a specified value.
 * @ingroup memory_functions
 * 
 * @param s The memory block to set.
 * @param c The value to set the memory block to.
 * @param n The number of bytes to set.
 * 
 * @return A pointer to the memory block.
 */
void	*mem_set(void *s, int c, size_t n)
{
	char	*src;

	src = (char *) s;
	while (s && n > 0)
	{
		src[n - 1] = c;
		n--;
	}
	return (s);
}
