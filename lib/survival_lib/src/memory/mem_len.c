/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:35:16 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:18:41 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file mem_len.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the mem_len function.
 */

/**
 * @brief Gets the length of a memory block.
 * @ingroup memory_functions
 * 
 * @param ptr The memory direction that the block starts.
 * @param blk_size Size of each data value in the memory block (1 for chars, 
 * 4 for int, 8 for pointers, etc.).
 * 
 * @return The size of the memory block.
 * 
 * @warning The memory block needs to be NULL terminated, if is not NULL 
 * terminated the behaviour of this function is undefined.
 */
int	mem_len(void *ptr, size_t blk_size)
{
	int	len;

	len = 0;
	while (ptr && ((char *)ptr)[len * blk_size])
		len++;
	return (len);
}
