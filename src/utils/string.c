/**
 * @file string.c
 * @author Lilith Estévez Boeta
 * @brief This file contains string validation functions for fractal type identification.
 */

#include "fract_ol.h"

/**
 * @brief Checks if a string matches the "mandelbrot" fractal type.
 * @details Compares the input string with valid Mandelbrot variants (mandelbrot, sinh, eye).
 * @ingroup graphics_module
 * 
 * @param type String to check.
 * 
 * @return int 1 if type is a valid mandelbrot variant, 0 otherwise.
 */
int	is_mandelbrot(char *type)
{
	if (str_compare_all(type, "mandelbrot")
		|| str_compare_all(type, "sinh")
		|| str_compare_all(type, "eye")
		|| str_compare_all(type, "dragon"))
		return (1);
	return (0);
}

/**
 * @brief Checks if a string matches the "julia" fractal type.
 * @ingroup graphics_module
 * 
 * @param type String to check.
 * 
 * @return int 1 if type is "julia", 0 otherwise.
 */
int	is_julia(char *type)
{
	if (str_compare_all(type, "julia"))
		return (1);
	return (0);
}
