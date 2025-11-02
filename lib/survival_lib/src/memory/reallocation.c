/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:02:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:43:17 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file reallocation.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the reallocation function.
 */

/**
 * @brief Reallocates memory to a new size, copying existing data if available.
 * @ingroup memory_functions
 * 
 * Reallocates memory to a new size. If the pointer is NULL, it allocates new
 * memory. If new_size is 0, it frees the existing memory. Otherwise, it copies
 * the old data to a new memory block and frees the old pointer.
 * 
 * @param ptr The pointer to reallocate (can be NULL).
 * @param new_size The new size of the memory block.
 * @param old_size The current size of the memory block.
 * 
 * @return A pointer to the newly allocated memory.
 * @retval NULL if the allocation failed or if new_size is 0.
 * @warning The old pointer should not be used after this function is called.
 */
void	*reallocation(void *ptr, unsigned long new_size, unsigned long old_size)
{
	void	*new_ptr;

	if (!ptr)
		return (callocation(new_size, 1));
	if (!new_size)
	{
		free(ptr);
		return (0);
	}
	new_ptr = callocation(new_size, 1);
	if (new_ptr == 0)
		return (0);
	if (new_size > old_size)
		mem_copy(new_ptr, ptr, old_size);
	else
		mem_copy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
