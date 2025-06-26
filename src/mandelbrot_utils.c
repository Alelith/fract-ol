/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:27:37 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/27 00:30:25 by acesteve         ###   ########.fr       */
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

void	draw_mandelbrot(t_data *img)
{
	t_complex	c;
	t_complex	z;
	int			i;
	int			j;
	int			dives;

	i = W + 1;
	j = H + 1;
	while (j--)
	{
		while (i--)
		{
			c.real = -0.5 + ((double)i / W - 0.5) * (3.5 / 0.75);
			c.imag = ((double)j / H - 0.5) * (3.5 / 0.75) * ((double)H / W);
			z.real = 0;
			z.imag = 0;
			dives = diverge(z, c, ITER, 2);
			if (dives)
				my_mlx_pixel_put(img, i, j,
					trgb_rainbow((dives * 250 / ITER) - dives, 0));
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
		i = W + 1;
	}
}
