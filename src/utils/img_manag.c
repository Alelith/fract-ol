/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:38:12 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 16:38:56 by acesteve         ###   ########.fr       */
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
