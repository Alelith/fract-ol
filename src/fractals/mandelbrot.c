/**
 * @file mandelbrot.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the classic Mandelbrot fractal set renderer.
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Mandelbrot fractal calculation.
 * @details Computes z = z² + c for the Mandelbrot set.
 * 
 * @param z The current complex number (iteration value).
 * @param c The constant complex number (pixel value).
 * 
 * @return t_complex The result of one iteration.
 */
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;
	t_complex	temp;

	temp = multiply_complx(z, z);
	res = sum_complx(temp, c);
	return (res);
}

/**
 * @brief Determines if a complex number diverges in the Mandelbrot set.
 * @details Iterates the Mandelbrot function until divergence or max iterations reached.
 * 
 * @param z Initial complex number.
 * @param c Complex parameter (pixel coordinate).
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
 * @brief Renders a single pixel of the Mandelbrot fractal.
 * @details Calculates the divergence behavior and colors the pixel accordingly.
 * @ingroup fractal_rendering
 * 
 * @param img Pointer to the main data structure.
 * @param c Complex number corresponding to the pixel.
 * @param pos Screen position (pixel coordinates).
 */
void	draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, calculate_iterations(img, ITER), 2.0);
	if (dives > 0)

		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
