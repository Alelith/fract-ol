/**
 * @file complex_trigonometric.c
 * @brief Implementation of complex trigonometric and hyperbolic functions
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Computes the hyperbolic sine of a complex number
 *
 * @details Calculates sinh(a + bi) using Euler's formula:
 * sinh(a + bi) = sinh(a)cos(b) + i·cosh(a)sin(b)
 * where sinh and cosh are the hyperbolic sine and cosine of the real part,
 * and sin and cos are the trigonometric functions of the imaginary part.
 * Used in the Sinh Mandelbrot and Dragon Mandelbrot fractal variants.
 *
 * @ingroup complex_ops
 *
 * @param[in] num Complex number input for sinh operation
 *
 * @return t_complex Complex hyperbolic sine of the input
 */
t_complex	sinh_complx(t_complex num)
{
	t_complex	result;

	result.real = sinh(num.real) * cos(num.imag);

	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}
