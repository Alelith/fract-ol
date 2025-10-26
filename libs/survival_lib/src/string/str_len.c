/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:15:41 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 18:57:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_len.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_len function.
 */

/**
 * @brief Returns the length of a string.
 * @ingroup string_functions
 * 
 * @param str The string to measure.
 * 
 * @return The length of the string.
 */
size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
