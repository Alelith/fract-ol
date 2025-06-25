/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:27:37 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/25 23:33:10 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_complex	iteration(t_complex z, t_complex c)
{
	return (sum_complx(multiply_complx(z, z), c));
}

int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)
	{
		z = iteration(z, c);
		if (complx_module(z) > limit)
			return (iter);
	}
	return (0);
}
