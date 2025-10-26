#include "fract_ol.h"

static t_complex	iteration(t_complex z, t_complex c)
{
	t_complex	res;

	res = sinh_complx(div_complx(z, c));
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

void	draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos)
{
	int			dives;

	dives = diverge(img -> initial_z, c, ITER, 2.0);
	if (dives > 0)

		my_mlx_pixel_put(img, pos, get_color_hsv(dives, calculate_iterations(img, ITER)));
	else
		my_mlx_pixel_put(img, pos, 0);
}
