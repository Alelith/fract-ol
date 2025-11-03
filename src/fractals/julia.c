/**
 * @file julia.c
 * @brief Implementation of the Julia set fractal with fixed parameter
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Performs one iteration of the Julia set formula
 *
 * @details Computes the next value using z_{n+1} = z_n² + c where c is a
 * fixed complex constant provided by the user. Unlike Mandelbrot where c
 * varies per pixel, Julia sets use a constant c and vary the initial z.
 * Different c values produce dramatically different Julia set shapes.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Current complex value in the iteration sequence
 * @param[in] c Fixed complex constant parameter for this Julia set
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
 * @brief Tests for divergence in the Julia set iteration
 *
 * @details Repeatedly applies the Julia iteration formula until the modulus
 * exceeds the divergence limit or maximum iterations are reached. The initial
 * z varies per pixel while c remains constant, opposite to the Mandelbrot set.
 *
 * @ingroup fractal_render
 *
 * @param[in] z Initial complex value from pixel coordinates
 * @param[in] c Fixed complex parameter for this Julia set
 * @param[in] iter Maximum number of iterations to perform
 * @param[in] limit Divergence threshold (typically 2.0)
 *
 * @return int Remaining iterations when divergence detected, or 0 if bounded
 * @retval 0 Point appears to be in the Julia set (did not diverge)
 * @retval >0 Point diverged; value used for coloring
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
 * @brief Renders a single pixel of the Julia set with coloring
 *
 * @details Computes divergence for the given initial z value with the fixed
 * c parameter stored in the application state. All pixels are colored using
 * the psychedelic color scheme including those in the set, creating a
 * continuous color gradient across the entire image.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] img Pointer to application state with fixed c parameter
 * @param[in] z Initial complex value from pixel coordinates
 * @param[in] pos Screen coordinates where the pixel should be drawn
 */
void	draw_julia(t_data *img, t_complex z, t_vector2 pos)
{
	int			dives;

	dives = diverge(z, img -> initial_c, calculate_iterations(img, ITER), 2.0);

	my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER)));
}
