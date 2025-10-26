/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:12:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:41:25 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_concat.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_concat function.
 */

/**
 * @brief Concatenates two strings.
 * @ingroup string_functions
 * 
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * 
 * @return The total length of the string it tried to create.
 */
size_t	str_concat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = str_len(dst);
	src_len = str_len(src);
	if (size <= dst_len)
		return (size + src_len);
	while (dst_len + i < size - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
