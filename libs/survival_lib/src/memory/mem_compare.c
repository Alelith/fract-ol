/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:37:16 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 01:12:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @file mem_compare.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_compare function.
 */

/**
 * @brief Compares two memory blocks.
 * @ingroup memory_functions
 * 
 * @param s1 The first memory block.
 * @param s2 The second memory block.
 * @param n The number of bytes to compare.
 * 
 * @retval 1 if the memory blocks are equal.
 * @retval 0 if the memory blocks are not equal.
 */
int	mem_compare(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*src1;
	const unsigned char	*src2;

	if (!s1 || !s2)
		return (0);
	src1 = (const unsigned char *) s1;
	src2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (src1[i] != src2[i])
			return (0);
		i++;
	}
	return (1);
}
