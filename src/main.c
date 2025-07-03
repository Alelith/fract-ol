/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:22:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 23:19:19 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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

int	close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	zoom_in(int mousecode, t_data *img)
{
	static int	is_zooming = 0;

	if (mousecode == 4 && !is_zooming)
	{
		/*img -> x_max /= 1.25;
		img -> y_max /= 1.25;
		img -> x_min /= 1.25;
		img -> y_min /= 1.25;*/
		is_zooming = 1;
		//draw_mandelbrot(img);
		is_zooming = 0;
		//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);	
		ft_printf("%i", mousecode);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	double	c_argr;
	double	c_argi;
	t_data	img;

	img.x_max = 2;
	img.y_max = 2;
	img.x_min = -2;
	img.y_min = -2;
	if (argc < 2 || argc > 4)
	{
		ft_printf("Entrada no válida");
		return (0);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, W, H, "Hello world!");
	img.img = mlx_new_image(vars.mlx, W, H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (ft_strcmp(argv[1], "mandelbrot"))
		draw_mandelbrot(&img);
	else if (ft_strcmp(argv[1], "cos"))
		draw_sinh_mandelbrot(&img);
	else if (ft_strcmp(argv[1], "julia"))
	{
		c_argr = atod(argv[2]);
		c_argi = atod(argv[3]);
		draw_julia(&img, c_argr, c_argi);
	}
	ft_printf("Ya ta");
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close, &vars);
	mlx_mouse_hook(vars.win, zoom_in, &img);
	mlx_loop(vars.mlx);
}
