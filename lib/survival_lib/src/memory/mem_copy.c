/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:19:01 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:19:46 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file mem_copy.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_copy function.
 */

/**
 * @brief Copies memory from one block to another.
 * @ingroup memory_functions
 * 
 * @param dest The destination memory block.
 * @param src The source memory block.
 * @param n The number of bytes to copy.
 * 
 * @return A pointer to the destination memory block.
 */
void	*mem_copy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if ((!dest || !src) && n > 0)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
