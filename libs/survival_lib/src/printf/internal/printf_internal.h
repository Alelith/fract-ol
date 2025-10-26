/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:40:25 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/25 22:42:40 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file printf_internal.h
 * @author Lilith Estévez Boeta
 * @brief Internal header for the functions used by print_format.
 */

#ifndef PRINTF_INTERNAL_H
# define PRINTF_INTERNAL_H

# include <stdarg.h>
# include <unistd.h>
# include "survival_lib.h"

int		print_nbr(va_list args, char format);
int		print_str(const char *str, char c);

#endif
