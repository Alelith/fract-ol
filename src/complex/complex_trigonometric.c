/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_trigonometric.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:30:57 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/04 13:31:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_complex	sinh_complx(t_complex num)
{
	t_complex	result;

	result.real = sinh(num.real) * cos(num.imag);
	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}
