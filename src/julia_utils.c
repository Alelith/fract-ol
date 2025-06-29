/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:10:14 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 11:18:18 by acesteve         ###   ########.fr       */
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

void	draw_julia(t_data *img, double c_real, double c_img)
{
	t_complex	c;
	t_complex	z;
	int			i;
	int			j;
	int			dives;

	i = -1;
	j = -1;
	c.real = c_real;
	c.imag = c_img;
	while (j++ < H)
	{
		while (i++ < W)
		{
			z.real = ((double)i / W - 0.5) * 4;
			z.imag = ((double)j / H - 0.5) * (4 * ((double)H / W));
			dives = diverge(z, c, ITER, 2.0);
			if (dives > 0)
				my_mlx_pixel_put(img, i, j,
					psychedelic_color(ITER - dives, ITER, 0.0));
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
		i = -1;
	}
}
