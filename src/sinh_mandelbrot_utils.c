/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinh_mandelbrot_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:34:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 23:00:22 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;

	res = sinh_complx(div_complx(z, c));
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

void	draw_sinh_mandelbrot(t_data *img)
{
	t_complex	c;
	t_complex	z;
	int			i;
	int			j;
	int			dives;

	i = -1;
	j = -1;
	z.real = 0;
	z.imag = 1;
	while (j++ < H)
	{
		while (i++ < W)
		{
			c.real = ((double)i / W - 0.5) * 4;
			c.imag = ((double)j / H - 0.5) * (4 * ((double)H / W));
			dives = diverge(z, c, ITER, 2.0);
			if (dives > 0)
				my_mlx_pixel_put(img, i, j,
					psychedelic_color((ITER - dives), 0.0));
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
		i = -1;
	}
}
