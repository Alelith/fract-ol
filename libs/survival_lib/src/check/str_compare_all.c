/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_compare_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:54 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 01:12:27 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_compare_all.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_compare_all function.
 */

/**
 * @brief Checks if two strings are equal.
 * @ingroup check_functions
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @retval 1 if the strings are equal.
 * @retval 0 if the strings are not equal.
 */
int	str_compare_all(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	s1len = str_len(s1);
	s2len = str_len(s2);
	if (s1len != s2len)
		return (0);
	return (mem_compare(s1, s2, s1len));
}
