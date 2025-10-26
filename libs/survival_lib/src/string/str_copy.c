/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:53:15 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:49:57 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_copy.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_copy function.
 */

/**
 * @brief Copies a string to a destination buffer.
 * @ingroup string_functions
 * 
 * @param dst The destination buffer.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * 
 * @return The total length of the string it tried to create.
 */
size_t	str_copy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if ((!src || !dst) && size > 0)
		return (0);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (str_len(src));
}
