/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_zero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:17:54 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 17:55:29 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file set_zero.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the set_zero function.
 */

/**
 * @brief Sets a block of memory to zero.
 * @ingroup memory_functions
 * 
 * @param s The memory block to set.
 * @param n The number of bytes to set.
 */
void	set_zero(void *s, size_t n)
{
	mem_set(s, 0, n);
}
