/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:10:14 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** JULIA SET - Julia set fractal implementation
**
** This file implements Julia set fractals using the iteration formula
** z(n+1) = z(n)² + c, where z starts at the complex coordinate being
** tested and c is a fixed complex parameter. Unlike Mandelbrot sets
** where c varies and z starts at 0, Julia sets use a fixed c and
** vary the starting z value. Different values of c produce completely
** different Julia set shapes and patterns.
*/

#include "fract_ol.h"

/*
** iteration - Perform one Julia set iteration step
** @z: Current z value in the iteration sequence
** @c: Fixed complex parameter c for this Julia set
**
** Implements the core Julia formula: z(n+1) = z(n)² + c
** This is identical to the Mandelbrot formula, but the interpretation
** is different - here z varies (it's the coordinate being tested) and
** c is constant (defines which Julia set we're drawing).
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
** diverge - Test if point escapes to infinity in Julia set
** @z: Initial z value (the coordinate being tested)
** @c: Fixed Julia set parameter
** @iter: Maximum number of iterations to perform
** @limit: Escape radius (typically 2.0)
**
** Performs the iterative test to determine if a point belongs to the
** Julia set defined by parameter c. Iterates z = z² + c until either
** the magnitude exceeds the limit or max iterations reached.
** Returns the remaining iteration count when escape occurs, or 0 if
** the point appears to be in the set.
*/
static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)				/* Iterate up to maximum count */
	{
		z = iteration(z, c);		/* Apply Julia formula */
		if (complx_module(z) > limit)	/* Check if escaped */
			return (iter);		/* Return remaining iterations */
	}
	return (0);				/* Point is in the set */
}

/*
** draw_julia - Render one pixel of Julia set
** @img: Application data with graphics context and parameters
** @z: Complex coordinate for this pixel (becomes initial z)
** @pos: Screen position to render the pixel
**
** Calculates whether the given complex coordinate belongs to the
** Julia set defined by img->initial_c parameter. The coordinate z
** becomes the initial value for iteration, and the fixed Julia
** parameter is used as the constant. Uses doubled iteration count
** for more detailed rendering and always applies coloring.
*/
void	draw_julia(t_data *img, t_complex z, t_vector2 pos)
{
	int			dives;		/* Escape iteration count */

	/* Test if point escapes using Julia set parameters with doubled iterations */
	dives = diverge(z, img -> initial_c, ITER * 2, 2.0);
	/* Apply psychedelic coloring to all points (no black regions) */
	my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off));
}
