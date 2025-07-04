/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:37:58 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/04 14:49:01 by acesteve         ###   ########.fr       */
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
