/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:22:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/04 15:15:45 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	my_mlx_pixel_put(t_data *data, t_vector2 pos, int color)
{
	char	*dst;

	dst = data->addr;
	dst += (pos.y * data->line_length + pos.x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	ft_strcmp(char *a, char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	return (*a == *b);
}

int	zoom_in(int mousecode, int x, int y, t_data *img)
{
	static int	is_zooming = 0;

	if (mousecode == 4 && !is_zooming && x >= 0)
	{
		img -> max.real *= 0.75;
		img -> max.imag *= 0.75;
		img -> min.real *= 0.75;
		img -> min.imag *= 0.75;
		is_zooming = 1;
		redraw_fractal(img);
		is_zooming = 0;
	}
	if (mousecode == 5 && !is_zooming && y >= 0)
	{
		img -> max.real *= 1.25;
		img -> max.imag *= 1.25;
		img -> min.real *= 1.25;
		img -> min.imag *= 1.25;
		is_zooming = 1;
		redraw_fractal(img);
		is_zooming = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	vars;

	vars.max.real = 2;
	vars.max.imag = 2;
	vars.min.real = -2;
	vars.min.imag = -2;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol");
	vars.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	if (ft_strcmp(argv[1], "mandelbrot"))
	{
		vars.initial_z.real = 0;
		vars.initial_z.imag = 0;
		vars.type = MANDELBROT;
		redraw_fractal(&vars);
	}
	else if (ft_strcmp(argv[1], "cos"))
	{
		vars.initial_z.real = 0;
		vars.initial_z.imag = 1;
		vars.type = MANDELBROT;
		redraw_fractal(&vars);
	}
	else if (ft_strcmp(argv[1], "julia"))
	{
		vars.initial_c.real = atod(argv[2]);
		vars.initial_c.imag = atod(argv[3]);
		vars.type = JULIA;
		redraw_fractal(&vars);
	}
	mlx_key_hook(vars.win, key_handler, &vars);
	mlx_mouse_hook(vars.win, zoom_in, &vars);
	mlx_hook(vars.win, 17, 0, close, &vars);
	mlx_loop(vars.mlx);
}
