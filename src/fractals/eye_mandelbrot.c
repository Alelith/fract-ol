/**
 * @file eye_mandelbrot.c
 * @brief Implementation of the Eye Mandelbrot fractal variant
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Eye Mandelbrot formula
 *
 * @details Computes z_{n+1} = z_n³ + 1/c, using cubic iteration instead of
 * the quadratic formula of the classic Mandelbrot. The addition of the inverse
 * of c creates unique visual patterns with eye-like structures and different
 * convergence behavior compared to the standard set.
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

	res = sum_complx(multiply_complx(multiply_complx(z, z), z),
			inv_complx(c));
	return (res);
}

/**
 * @brief Tests for divergence using the Eye Mandelbrot formula
 *
 * @details Iterates the cubic formula until divergence or maximum iterations.
 * The divergence behavior differs from standard Mandelbrot due to the z³
 * term and inverse operation, creating distinct visual characteristics.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Initial complex value (typically 0)
 * @param[in] c Complex constant from pixel coordinates
 * @param[in] iter Maximum number of iterations to perform
 * @param[in] limit Divergence threshold
 *
 * @return int Remaining iterations when divergence detected, or 0 if bounded
 * @retval 0 Point appears to be in the Eye Mandelbrot set
 * @retval >0 Point diverged; value determines color
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
 * @brief Renders a single pixel of the Eye Mandelbrot fractal
 *
 * @details Computes divergence using the cubic iteration formula and colors
 * the pixel accordingly. Points in the set are rendered black while diverging
 * points receive psychedelic coloring based on escape speed, revealing the
 * distinctive eye-like patterns that characterize this variant.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] img Pointer to application state with rendering parameters
 * @param[in] c Complex coordinate from pixel position
 * @param[in] pos Screen coordinates for pixel placement
 */
void	draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, calculate_iterations(img, ITER), 2.0);
	if (dives > 0)
		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
