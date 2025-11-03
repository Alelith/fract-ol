/**
 * @file julia.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the Julia set fractal renderer.
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Julia fractal calculation.
 * @details Computes z = z² + c for the Julia set.
 * 
 * @param z The current complex number (iteration value).
 * @param c The constant complex number (Julia parameter).
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
 * @brief Determines if a complex number diverges in the Julia set.
 * @details Iterates the Julia function until divergence or max iterations reached.
 * 
 * @param z Complex number to test.
 * @param c Julia set parameter (constant).
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
 * @brief Renders a single pixel of the Julia fractal.
 * @details Calculates the divergence behavior and colors the pixel accordingly.
 * @ingroup fractal_rendering
 * 
 * @param img Pointer to the main data structure.
 * @param z Complex number corresponding to the pixel.
 * @param pos Screen position (pixel coordinates).
 */
void	draw_julia(t_data *img, t_complex z, t_vector2 pos)
{
	int			dives;

	dives = diverge(z, img -> initial_c, calculate_iterations(img, ITER), 2.0);

	my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER)));
}
