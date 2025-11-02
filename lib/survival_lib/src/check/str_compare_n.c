/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_compare_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:54 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 01:01:53 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_compare_n.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_compare_n function.
 */

/**
 * @brief Compares the first @a n characters of two strings for equality.
 * @ingroup check_functions
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The maximum number of characters to compare.
 * 
 * @retval 1 if the first @a n characters of both strings are equal.
 * @retval 0 if the strings differ or either pointer is NULL.
 */
int	str_compare_n(const char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (1);
	s1len = str_len(s1);
	s2len = str_len(s2);
	if (s1len > s2len && s2len < n)
		return (mem_compare(s1, s2, s2len + 1));
	else if (s1len <= s2len && s1len < n)
		return (mem_compare(s1, s2, s1len + 1));
	return (mem_compare(s1, s2, n));
}
