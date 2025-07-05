/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:22:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 17:37:19 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	initial_variables(t_data *data, char **argv)
{
	if (ft_strcmp(argv[1], "mandelbrot"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 0;
	}
	else if (ft_strcmp(argv[1], "sinh"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 1;
	}
	else if (ft_strcmp(argv[1], "eye"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 0;
	}
	else if (ft_strcmp(argv[1], "julia"))
	{
		data -> initial_c.real = atod(argv[2]);
		data -> initial_c.imag = atod(argv[3]);
	}
}

static void	initial_conditions(t_data *data, char **argv)
{
	data -> max.real = 2;
	data -> max.imag = 2;
	data -> min.real = -2;
	data -> min.imag = -2;
	initial_variables(data, argv);
	if (ft_strcmp(argv[1], "mandelbrot"))
		data -> type = MANDELBROT;
	else if (ft_strcmp(argv[1], "sinh"))
		data -> type = SINH_MANDELBROT;
	else if (ft_strcmp(argv[1], "eye"))
		data -> type = EYE_MANDELBROT;
	else if (ft_strcmp(argv[1], "julia"))
		data -> type = JULIA;
}

void	init_window(t_data *vars)
{
	vars -> mlx = mlx_init();
	vars -> win = mlx_new_window(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol");
	vars -> img = mlx_new_image(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	vars -> addr = mlx_get_data_addr(vars -> img, &(vars -> bits_per_pixel),
			&(vars -> line_length), &(vars -> endian));
	mlx_key_hook(vars -> win, key_handler, vars);
	mlx_mouse_hook(vars -> win, zoom, vars);
	mlx_hook(vars -> win, 17, 0, close, vars);
	redraw_fractal(vars);
	mlx_loop(vars -> mlx);
}

int	main(int argc, char **argv)
{
	t_data	vars;

	if ((argc != 2 && is_mandelbrot(argv[1]))
		|| (argc != 4 && is_julia(argv[1])))
	{
		exit(0);
	}
	initial_conditions(&vars, argv);
	init_window(&vars);
}
