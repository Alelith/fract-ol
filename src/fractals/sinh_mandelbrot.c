/**
 * @file sinh_mandelbrot.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the Sinh Mandelbrot fractal variant renderer.
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Sinh Mandelbrot fractal calculation.
 * @details Computes z = sinh(z/c) for the Sinh Mandelbrot set.
 * 
 * @param z The current complex number (iteration value).
 * @param c The constant complex number (pixel value).
 * 
 * @return t_complex The result of one iteration.
 */
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;

	res = sinh_complx(div_complx(z, c));
	return (res);
}

/**
 * @brief Determines if a complex number diverges in the Sinh Mandelbrot set.
 * @details Iterates the Sinh Mandelbrot function until divergence or max iterations reached.
 * 
 * @param z Complex number to test.
 * @param c Complex set parameter (constant).
 * @param iter Maximum number of iterations to perform.
 * @param limit Divergence threshold (typically 2.0).
 * 
 * @return int Remaining iterations when diverged, or 0 if did not diverge.
 */
static int	diverge(t_complex z, t_complex c, int iter, double limit)
{
	while (iter--)
	{
		z = iteration(z, c);
		if (complx_module(z) > limit)
			return (iter);
	}
	return (0);
}

/**
 * @brief Renders a single pixel of the Sinh Mandelbrot fractal.
 * @details Calculates the divergence behavior and colors the pixel using HSV coloring.
 * @ingroup fractal_rendering
 * 
 * @param img Pointer to the main data structure.
 * @param c Complex number corresponding to the pixel.
 * @param pos Screen position (pixel coordinates).
 */
void	draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, ITER, 2.0);
	if (dives > 0)

		my_mlx_pixel_put(img, pos, get_color_hsv(dives, calculate_iterations(img, ITER)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
