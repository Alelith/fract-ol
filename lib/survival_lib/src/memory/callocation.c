/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callocation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:11:14 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:44:32 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file callocation.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the callocation function.
 */

/**
 * @brief Allocates zero-initialized memory for an array of elements.
 * @ingroup memory_functions
 * 
 * Allocates memory for an array of @a nmemb elements, 
 * each of size @a size bytes,
 * and initializes all bytes to zero.
 * 
 * @param nmemb The number of elements.
 * @param size The size of each element in bytes.
 * 
 * @return A pointer to the allocated zero-initialized memory.
 * @retval NULL if the allocation failed.
 * @warning Needs to be freed with free() after use.
 */
void	*callocation(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (!result)
		return (0);
	set_zero(result, nmemb * size);
	return (result);
}
