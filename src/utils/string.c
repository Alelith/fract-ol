/**
 * @file string.c
 * @brief String validation utilities for command-line argument parsing
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Validates if the input string specifies a Mandelbrot variant
 *
 * @details Checks if the provided string matches any of the supported
 * Mandelbrot-type fractals: "mandelbrot", "sinh", "eye", or "dragon".
 * Used during command-line parsing to validate fractal type and determine
 * the expected number of arguments (Mandelbrot types require only the type,
 * while Julia requires additional parameters).
 *
 * @ingroup utils
 *
 * @param[in] type String to validate against Mandelbrot variant names
 *
 * @return int Boolean result of the validation
 * @retval 1 String matches a known Mandelbrot variant name
 * @retval 0 String does not match any Mandelbrot variant
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
 * @brief Validates if the input string specifies the Julia set fractal
 *
 * @details Checks if the provided string matches "julia". Used during
 * command-line parsing to identify when Julia set parameters are expected.
 * Julia sets require additional real and imaginary parameters for the
 * constant c, unlike Mandelbrot variants which only need the type name.
 *
 * @ingroup utils
 *
 * @param[in] type String to validate against Julia set identifier
 *
 * @return int Boolean result of the validation
 * @retval 1 String matches "julia"
 * @retval 0 String does not match "julia"
 */
int	is_julia(char *type)
{
	if (str_compare_all(type, "julia"))
		return (1);
	return (0);
}
