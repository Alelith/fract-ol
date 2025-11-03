/**
 * @file complex_trigonometric.c
 * @author Lilith Estévez Boeta
 * @brief This file contains trigonometric operations for complex numbers, including hyperbolic sine calculation.
 */

#include "fract_ol.h"

/**
 * @brief Computes the hyperbolic sine of a complex number.
 * @details Calculates sinh(z) for complex numbers using the formula:
 * sinh(z) = sinh(Re(z))*cos(Im(z)) + i*cosh(Re(z))*sin(Im(z))
 * @ingroup complex_ops
 * 
 * @param num The complex number.
 * 
 * @return t_complex The hyperbolic sine of num.
 */
t_complex	sinh_complx(t_complex num)
{
	t_complex	result;

	result.real = sinh(num.real) * cos(num.imag);

	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}
