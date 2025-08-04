/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:38:12 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** IMAGE MANAGEMENT - MLX image buffer manipulation
**
** This file implements low-level image buffer operations for MLX
** graphics. It provides direct pixel manipulation functions that
** write color data directly to the image buffer memory, bypassing
** MLX's slower pixel-by-pixel drawing functions for improved
** performance in fractal rendering applications.
*/

#include "fract_ol.h"

/*
** my_mlx_pixel_put - Write pixel directly to MLX image buffer
** @data: Application data containing MLX image information
** @pos: 2D vector containing pixel coordinates (x, y)
** @color: 32-bit ARGB color value to write
**
** Performs direct memory manipulation to write pixel colors to the
** MLX image buffer. This bypasses MLX's mlx_pixel_put function for
** significantly improved performance when rendering thousands of
** pixels. Calculates the exact memory address using line length
** and bits per pixel, then writes the color value directly to
** memory. Essential for real-time fractal rendering performance.
*/
void	my_mlx_pixel_put(t_data *data, t_vector2 pos, int color)
{
	char	*dst;		/* Destination memory address */

	dst = data->addr;	/* Start with image buffer base address */
	/* Calculate pixel memory offset using row stride and column offset */
	dst += (pos.y * data->line_length + pos.x * (data->bits_per_pixel / 8));
	/* Write color value directly to calculated memory location */
	*((unsigned int *)dst) = color;
}
