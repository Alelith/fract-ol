#include "fract_ol.h"

int	is_mandelbrot(char *type)
{
	if (str_compare_all(type, "mandelbrot")
		|| str_compare_all(type, "sinh")
		|| str_compare_all(type, "eye"))
		return (1);
	return (0);
}

int	is_julia(char *type)
{
	if (str_compare_all(type, "julia"))
		return (1);
	return (0);
}
