/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eye_mandelbrot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:00:13 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:48 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** EYE MANDELBROT - Cubic "Eye" Mandelbrot variation
**
** This file implements a unique cubic variation of the Mandelbrot set
** using the formula z(n+1) = z(n)³ + 1/c. This creates distinctive
** three-fold symmetry patterns with complex internal structures.
** The cubic term produces different escape dynamics compared to the
** quadratic classic Mandelbrot, while the inverse of c adds additional
** geometric complexity and creates "eye-like" formations.
*/

#include "fract_ol.h"

/*
** iteration - Perform one cubic eye Mandelbrot iteration step
** @z: Current z value in the iteration sequence
** @c: Complex parameter c (inverted and added)
**
** Implements the cubic eye formula: z(n+1) = z(n)³ + 1/c
** This formula uses cubic iteration (z³) instead of quadratic (z²)
** and adds the complex inverse of c. The cubic term creates three-fold
** rotational symmetry, while 1/c adds radial complexity. This
** combination produces intricate eye-like or flower-like patterns.
** Returns the new z value for the next iteration.
*/
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;		/* Result of iteration */

	/* Calculate z³ + 1/c */
	res = sum_complx(multiply_complx(multiply_complx(z, z), z),
			inv_complx(c));		/* z³ + (1/c) */
	return (res);
}

/*
** diverge - Test if point escapes to infinity in cubic eye Mandelbrot
** @z: Initial z value (typically 0 for Mandelbrot variants)
** @c: Complex parameter being tested (inverted in formula)
** @iter: Maximum number of iterations to perform
** @limit: Escape radius (typically 2.0)
**
** Performs the iterative test using the cubic eye formula z³ + 1/c.
** The cubic term causes faster divergence for large values but may
** create more stable regions due to the three-fold symmetry. The
** inverse operation can cause interesting convergence patterns.
** Returns remaining iteration count on escape, or 0 if in set.
*/
static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)				/* Iterate up to maximum count */
	{
		z = iteration(z, c);		/* Apply cubic eye formula */
		if (complx_module(z) > limit)	/* Check if escaped */
			return (iter);		/* Return remaining iterations */
	}
	return (0);				/* Point is in the set */
}

/*
** draw_eye_mandelbrot - Render one pixel of cubic eye Mandelbrot set
** @img: Application data with graphics context and parameters
** @c: Complex coordinate for this pixel
** @pos: Screen position to render the pixel
**
** Calculates whether the given complex coordinate belongs to the
** cubic eye Mandelbrot set. This variant produces patterns with
** three-fold symmetry and eye-like formations due to the cubic
** iteration and complex inverse terms. Uses psychedelic coloring
** with animation for dynamic visual effects.
*/
void	draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;		/* Escape iteration count */

	/* Test if point escapes using cubic eye transformation */
	dives = diverge(img -> initial_z, c, ITER, 2.0);
	if (dives > 0)				/* Point escaped */
		/* Color with psychedelic scheme and animation offset */
		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off));
	else					/* Point is in the set */
		my_mlx_pixel_put(img, pos, 0);	/* Black color for set members */
}
