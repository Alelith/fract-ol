/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:27:37 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 22:50:13 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;
	t_complex	temp;

	temp = multiply_complx(z, z);
	res = sum_complx(temp, c);
	return (res);
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

	i = -1;
	j = -1;
	z.real = 0;
	z.imag = 0;
	while (j++ < H)
	{
		while (i++ < W)
		{
			c.real = -0.5 + ((double)i / W - 0.5) * (img -> x_max - img -> x_min);
			c.imag = ((double)j / H - 0.5) * ((img -> y_max - img -> y_min) * ((double)H / W));
			dives = diverge(z, c, ITER, 2.0);
			if (dives > 0)
				my_mlx_pixel_put(img, i, j,
					psychedelic_color(ITER - dives, 0.0));
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
		i = -1;
	}
}
