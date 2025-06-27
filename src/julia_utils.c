/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:10:14 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/27 03:15:00 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static t_complex	iteration(t_complex z, t_complex c)
{
	return (sum_complx(multiply_complx(z, z), c));
}

static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)
	{
		z = iteration(z, c);
		if (complx_module(z) > limit)
			return (iter);
	}
	return (0);
}

void	draw_julia(t_data *img, double c_real, double c_img)
{
	t_complex	c;
	t_complex	z;
	int			i;
	int			j;
	int			dives;

	i = W + 1;
	j = H + 1;
	c.real = c_real;
	c.imag = c_img;
	while (j--)
	{
		while (i--)
		{
			z.real = ((double)i / W) * 4 - 2;
			z.imag = ((double)j / H) * 4 - 2;
			dives = diverge(z, c, ITER, 10);
			if (dives)
				my_mlx_pixel_put(img, i, j,
					trgb_rainbow((dives * 250 / ITER) - dives, 150));
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
		i = W + 1;
	}
}
