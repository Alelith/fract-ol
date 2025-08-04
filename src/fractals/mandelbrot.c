/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:27:37 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** MANDELBROT SET - Classic Mandelbrot fractal implementation
**
** This file implements the classic Mandelbrot set fractal using the
** iteration formula z(n+1) = z(n)² + c, where z starts at 0 and c
** is the complex coordinate being tested. The Mandelbrot set consists
** of all points c for which the iteration does not escape to infinity.
*/

#include "fract_ol.h"

/*
** iteration - Perform one Mandelbrot iteration step
** @z: Current z value in the iteration sequence
** @c: Complex parameter c (the point being tested)
**
** Implements the core Mandelbrot formula: z(n+1) = z(n)² + c
** This is the fundamental operation that defines the Mandelbrot set.
** The iteration is repeated until either the magnitude exceeds the
** escape radius or the maximum iteration count is reached.
** Returns the new z value for the next iteration.
*/
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;		/* Result of iteration */
	t_complex	temp;		/* Temporary for z² calculation */

	temp = multiply_complx(z, z);		/* Calculate z² */
	res = sum_complx(temp, c);		/* Add c to get z² + c */
	return (res);
}

/*
** diverge - Test if point escapes to infinity
** @z: Initial z value (typically 0 for Mandelbrot)
** @c: Complex parameter being tested
** @iter: Maximum number of iterations to perform
** @limit: Escape radius (typically 2.0)
**
** Performs the iterative test to determine if a point belongs to the
** Mandelbrot set. Iterates the formula z = z² + c until either the
** magnitude exceeds the limit (escapes) or max iterations reached.
** Returns the remaining iteration count when escape occurs, or 0 if
** the point appears to be in the set (doesn't escape).
*/
static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)				/* Iterate up to maximum count */
	{
		z = iteration(z, c);		/* Apply Mandelbrot formula */
		if (complx_module(z) > limit)	/* Check if escaped */
			return (iter);		/* Return remaining iterations */
	}
	return (0);				/* Point is in the set */
}

/*
** draw_mandelbrot - Render one pixel of Mandelbrot set
** @img: Application data with graphics context and parameters
** @c: Complex coordinate for this pixel
** @pos: Screen position to render the pixel
**
** Calculates whether the given complex coordinate belongs to the
** Mandelbrot set and renders the appropriate color. Uses the escape
** iteration count to determine coloring - points that escape quickly
** get bright colors, points that take longer get different colors,
** and points in the set are colored black.
*/
void	draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;		/* Escape iteration count */

	/* Test if point escapes and get iteration count */
	dives = diverge(img -> initial_z, c, ITER, 2.0);
	if (dives > 0)				/* Point escaped */
		/* Color based on escape speed with animation phase */
		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off));
	else					/* Point is in the set */
		my_mlx_pixel_put(img, pos, 0);	/* Black color for set members */
}
