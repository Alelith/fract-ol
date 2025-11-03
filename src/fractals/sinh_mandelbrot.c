/**
 * @file sinh_mandelbrot.c
 * @brief Implementation of the Sinh Mandelbrot fractal variant
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Sinh Mandelbrot formula
 *
 * @details Computes z_{n+1} = sinh(z_n / c) using the complex hyperbolic sine
 * function instead of the polynomial iteration. The division by c and sinh
 * operation create dramatically different structures with flowing, organic
 * shapes compared to the angular features of polynomial fractals.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Current complex value in the iteration sequence
 * @param[in] c Complex constant from pixel coordinates
 *
 * @return t_complex Next value in the iteration sequence
 */
static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;

	res = sinh_complx(div_complx(z, c));
	return (res);
}

/**
 * @brief Tests for divergence using the Sinh Mandelbrot formula
 *
 * @details Iterates the hyperbolic sine formula until divergence or maximum
 * iterations. The transcendental nature of sinh creates different convergence
 * patterns and typically requires different divergence thresholds than
 * polynomial fractals.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Initial complex value from application state
 * @param[in] c Complex constant from pixel coordinates
 * @param[in] iter Maximum number of iterations to perform
 * @param[in] limit Divergence threshold
 *
 * @return int Remaining iterations when divergence detected, or 0 if bounded
 * @retval 0 Point appears to be in the Sinh Mandelbrot set
 * @retval >0 Point diverged; value determines color intensity
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
 * @brief Renders a single pixel of the Sinh Mandelbrot fractal
 *
 * @details Computes divergence using the hyperbolic sine iteration and applies
 * HSV color mapping based on iteration count. Points in the set are black while
 * diverging points show smooth color gradients, highlighting the fluid organic
 * structures characteristic of this transcendental fractal variant.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] img Pointer to application state with rendering parameters
 * @param[in] c Complex coordinate from pixel position
 * @param[in] pos Screen coordinates for pixel placement
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
