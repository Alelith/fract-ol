/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:37:58 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 17:42:30 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	close(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	key_handler(int keycode, t_data *vars)
{
	if (keycode == 65307)
		close(vars);
	return (0);
}

int	zoom(int mousecode, int x, int y, t_data *img)
{
	double	zoom;

	if (mousecode == 4)
		zoom = 0.9;
	else if (mousecode == 5)
		zoom = 1.1;
	else
		return (0);
	img -> max.real *= zoom;
	img -> max.imag *= zoom;
	img -> min.real *= zoom;
	img -> min.imag *= zoom;
	img -> color_off += 0.125;
	redraw_fractal(img);
	return (0);
}
