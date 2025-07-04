/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:07:56 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/04 16:22:43 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	calculate_mandelbrot(t_data *data, t_vector2 screen_pos)
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

static void	calculate_julia(t_data *data, t_vector2 screen_pos)
{
	t_complex	z;

	z.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	z.real *= data -> max.real - data -> min.real;
	z.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	z.imag *= data -> max.imag - data -> min.imag;
	z.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	draw_julia(data, z, screen_pos);
}

static void	calculate_sinh_mandelbrot(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	draw_sinh_mandelbrot(data, c, screen_pos);
}

static void	calculate_dragon_mandelbrot(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
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
				calculate_mandelbrot(data, screen_pos);
			else if (data -> type == JULIA)
				calculate_julia(data, screen_pos);
			else if (data -> type == SINH_MANDELBROT)
				calculate_sinh_mandelbrot(data, screen_pos);
			else if (data -> type == DRAGON_MANDELBROT)
				calculate_dragon_mandelbrot(data, screen_pos);
		}
		screen_pos.x = -1;
	}
	mlx_put_image_to_window(data -> mlx, data -> win, data -> img, 0, 0);
}
