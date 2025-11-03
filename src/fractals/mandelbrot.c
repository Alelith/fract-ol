/**
 * @file mandelbrot.c
 * @brief Implementation of the classic Mandelbrot set fractal
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Mandelbrot formula
 *
 * @details Computes the next value in the Mandelbrot sequence using the
 * formula z_{n+1} = z_n² + c. This is the fundamental operation that defines
 * the Mandelbrot set. Points that remain bounded under infinite iterations
 * belong to the set.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Current complex value in the iteration sequence
 * @param[in] c Complex constant representing the pixel's coordinates
 *
 * @return t_complex Next value in the iteration sequence
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
 * @brief Tests for divergence by iterating the Mandelbrot formula
 *
 * @details Repeatedly applies the iteration formula until either the modulus
 * exceeds the divergence limit or the maximum iteration count is reached.
 * Returns the number of iterations remaining when divergence is detected,
 * or 0 if the point appears to be in the set (bounded).
 *
 * @ingroup fractal_render
 *
 * @param[in] z Initial complex value (typically 0 for Mandelbrot)
 * @param[in] c Complex constant from pixel coordinates
 * @param[in] iter Maximum number of iterations to perform
 * @param[in] limit Divergence threshold (typically 2.0 for Mandelbrot)
 *
 * @return int Remaining iterations when divergence detected, or 0 if bounded
 * @retval 0 Point appears to be in the Mandelbrot set (did not diverge)
 * @retval >0 Point diverged; value indicates divergence speed
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
 * @brief Renders a single pixel of the Mandelbrot set with coloring
 *
 * @details Computes the divergence behavior for the given complex coordinate
 * and assigns a color based on the iteration count. Points in the set (no
 * divergence) are colored black. Diverging points receive a psychedelic color
 * based on how quickly they escape, creating the characteristic fractal bands.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] img Pointer to application state containing rendering parameters
 * @param[in] c Complex coordinate corresponding to the pixel
 * @param[in] pos Screen coordinates where the pixel should be drawn
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
