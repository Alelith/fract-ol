/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:07:56 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 16:02:41 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	calculate_c_off(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.real -= 0.5;
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	draw_mandelbrot(data, c, screen_pos);
}

static void	calculate_z(t_data *data, t_vector2 screen_pos)
{
	t_complex	z;

	z.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	z.real *= data -> max.real - data -> min.real;
	z.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	z.imag *= data -> max.imag - data -> min.imag;
	z.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	draw_julia(data, z, screen_pos);
}

static void	calculate_c(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	if (data -> type == SINH_MANDELBROT)
		draw_sinh_mandelbrot(data, c, screen_pos);
	else if (data -> type == EYE_MANDELBROT)
		draw_eye_mandelbrot(data, c, screen_pos);
}

void	redraw_fractal(t_data *data)
{
	t_vector2	screen_pos;

	mlx_clear_window(data -> mlx, data -> win);
	screen_pos.x = -1;
	screen_pos.y = -1;
	while (screen_pos.y++ < SCREEN_HEIGHT)
	{
		while (screen_pos.x++ < SCREEN_WIDTH)
		{
			if (data -> type == MANDELBROT)
				calculate_c_off(data, screen_pos);
			else if (data -> type == JULIA)
				calculate_z(data, screen_pos);
			else if (data -> type == SINH_MANDELBROT
				|| data -> type == EYE_MANDELBROT)
				calculate_c(data, screen_pos);
		}
		screen_pos.x = -1;
	}
	mlx_put_image_to_window(data -> mlx, data -> win, data -> img, 0, 0);
}
