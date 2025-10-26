#include "fract_ol.h"

static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;

	res = sum_complx(multiply_complx(multiply_complx(z, z), z),
			inv_complx(c));
	return (res);
}

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

void	draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, calculate_iterations(img, ITER), 2.0);
	if (dives > 0)
		my_mlx_pixel_put(img, pos, psychedelic_color(dives, img -> color_off, calculate_iterations(img, ITER)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
