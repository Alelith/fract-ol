/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinh_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:34:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:48 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SINH MANDELBROT - Hyperbolic sine Mandelbrot variation with division
**
** This file implements a unique variation of the Mandelbrot set using
** the formula z(n+1) = sinh(z(n)/c), where z is divided by c before
** applying the hyperbolic sine function. This creates highly complex
** fractal patterns with radial symmetries and intricate detail that
** combines the properties of division and hyperbolic transformations.
*/

#include "fract_ol.h"

/*
** iteration - Perform one sinh division Mandelbrot iteration step
** @z: Current z value in the iteration sequence
** @c: Complex parameter c (used as divisor)
**
** Implements the sinh division formula: z(n+1) = sinh(z(n)/c)
** This unusual formula first divides z by c, then applies the
** hyperbolic sine function. The division creates radial patterns
** while sinh adds hyperbolic distortion, resulting in unique
** fractal geometries not seen in standard Mandelbrot variants.
** Returns the new z value for the next iteration.
*/
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;		/* Result of iteration */

	/* Apply sinh(z/c) transformation */
	res = sinh_complx(div_complx(z, c));	/* Divide z by c, then apply sinh */
	return (res);
}

/*
** diverge - Test if point escapes to infinity in sinh division variant
** @z: Initial z value (typically 0 for Mandelbrot variants)
** @c: Complex parameter being tested (also used as divisor)
** @iter: Maximum number of iterations to perform
** @limit: Escape radius (typically 2.0)
**
** Performs the iterative test using the sinh(z/c) transformation.
** The division by c followed by sinh creates complex escape patterns
** that may converge or diverge differently from standard Mandelbrot.
** Returns remaining iteration count on escape, or 0 if in set.
*/
static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)				/* Iterate up to maximum count */
	{
		z = iteration(z, c);		/* Apply sinh division formula */
		if (complx_module(z) > limit)	/* Check if escaped */
			return (iter);		/* Return remaining iterations */
	}
	return (0);				/* Point is in the set */
}

/*
** draw_sinh_mandelbrot - Render one pixel of sinh division Mandelbrot
** @img: Application data with graphics context and parameters
** @c: Complex coordinate for this pixel
** @pos: Screen position to render the pixel
**
** Calculates whether the given complex coordinate belongs to the
** sinh division Mandelbrot set. This variant produces intricate
** patterns with radial symmetry due to the division operation
** combined with hyperbolic sine distortion. Uses HSV coloring
** for enhanced visual distinction from other fractal types.
*/
void	draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;		/* Escape iteration count */

	/* Test if point escapes using sinh division transformation */
	dives = diverge(img -> initial_z, c, ITER, 2.0);
	if (dives > 0)				/* Point escaped */
		/* Color using HSV scheme for unique visual appearance */
		my_mlx_pixel_put(img, pos, get_color_hsv(dives));
	else					/* Point is in the set */
		my_mlx_pixel_put(img, pos, 0);	/* Black color for set members */
}
