/**
 * @file dragon_mandelbrot.c
 * @brief Implementation of the Dragon Mandelbrot fractal variant
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Dragon Mandelbrot formula
 *
 * @details Computes z_{n+1} = sinh(z_n) + 1/c² combining hyperbolic sine with
 * inverse squared operations. This complex formula produces intricate dragon-like
 * structures with sharp features and deep self-similarity. The combination of
 * transcendental and rational operations creates unique convergence patterns.
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

	res = sum_complx(sinh_complx(z), inv_complx(multiply_complx(c, c)));
	return (res);
}

/**
 * @brief Tests for divergence using the Dragon Mandelbrot formula
 *
 * @details Iterates the complex dragon formula until divergence or maximum
 * iterations. This variant typically requires significantly higher iteration
 * counts and larger divergence thresholds due to the slow-growing nature of
 * the combined sinh and inverse operations.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Initial complex value from application state
 * @param[in] c Complex constant from pixel coordinates
 * @param[in] iter Maximum number of iterations to perform
 * @param[in] limit Divergence threshold (typically much higher than standard)
 *
 * @return int Remaining iterations when divergence detected, or 0 if bounded
 * @retval 0 Point appears to be in the Dragon Mandelbrot set
 * @retval >0 Point diverged; value determines color detail
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
 * @brief Renders a single pixel of the Dragon Mandelbrot fractal
 *
 * @details Computes divergence using the dragon formula with significantly
 * increased iteration count (20x multiplier) and high divergence limit (60.0)
 * to capture the fractal's fine details. Colors diverging points with
 * psychedelic mapping to reveal the intricate dragon-scale patterns.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] img Pointer to application state with rendering parameters
 * @param[in] c Complex coordinate from pixel position
 * @param[in] pos Screen coordinates for pixel placement
 *
 * @note Uses 20x iteration multiplier due to slow convergence
 * @note Divergence limit set to 60.0 instead of standard 2.0
 */
void	draw_dragon_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, calculate_iterations(img, ITER * 20), 60.0);
	if (dives > 0)
		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER * 20)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
