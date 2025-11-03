/**
 * @file complex_operations.c
 * @brief Implementation of basic complex number arithmetic operations
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Multiplies two complex numbers
 *
 * @details Computes the product of two complex numbers using the formula:
 * (a + bi)(c + di) = (ac - bd) + (ad + bc)i
 * This is a fundamental operation used in all fractal iteration formulas.
 *
 * @ingroup complex_ops
 *
 * @param[in] a First complex number multiplicand
 * @param[in] b Second complex number multiplicand
 *
 * @return t_complex Product of a and b as a new complex number
 */
t_complex	multiply_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real * b.real) - (a.imag * b.imag);
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return (result);
}

/**
 * @brief Adds two complex numbers
 *
 * @details Computes the sum of two complex numbers by adding their real and
 * imaginary components separately: (a + bi) + (c + di) = (a + c) + (b + d)i
 * Used extensively in fractal iteration formulas to add the constant term.
 *
 * @ingroup complex_ops
 *
 * @param[in] a First complex number addend
 * @param[in] b Second complex number addend
 *
 * @return t_complex Sum of a and b as a new complex number
 */
t_complex	sum_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real + b.real);
	result.imag = (a.imag + b.imag);
	return (result);
}

/**
 * @brief Divides one complex number by another
 *
 * @details Computes the quotient of two complex numbers using the formula:
 * (a + bi) / (c + di) = [(ac + bd) + (bc - ad)i] / (c² + d²)
 * The denominator is normalized by multiplying by the conjugate to eliminate
 * the imaginary part from the divisor.
 *
 * @ingroup complex_ops
 *
 * @param[in] a Dividend (numerator) complex number
 * @param[in] b Divisor (denominator) complex number
 *
 * @return t_complex Quotient of a divided by b
 *
 * @warning No division-by-zero check is performed. Ensure b is non-zero.
 */
t_complex	div_complx(t_complex a, t_complex b)
{
	t_complex	result;
	double		den;

	den = (b.real * b.real) + (b.imag * b.imag);

	result.real = (a.real * b.real + a.imag * b.imag) / den;

	result.imag = (a.imag * b.real - a.real * b.imag) / den;
	return (result);
}

/**
 * @brief Computes the multiplicative inverse of a complex number
 *
 * @details Calculates 1/(a + bi) using the formula:
 * 1/(a + bi) = (a - bi) / (a² + b²) = a/(a² + b²) - bi/(a² + b²)
 * The result is the complex conjugate divided by the squared modulus.
 * Used in fractal variants that require reciprocal operations.
 *
 * @ingroup complex_ops
 *
 * @param[in] a Complex number to be inverted
 *
 * @return t_complex Multiplicative inverse of a
 *
 * @warning No check for zero input. Ensure a is non-zero to avoid division by zero.
 */
t_complex	inv_complx(t_complex a)
{
	t_complex	result;
	double		den;

	den = (a.real * a.real) + (a.imag * a.imag);
	result.real = a.real / den;
	result.imag = -a.imag / den;
	return (result);
}

/**
 * @brief Calculates the modulus (absolute value) of a complex number
 *
 * @details Computes the Euclidean distance from the origin to the complex
 * number in the complex plane using the formula: |a + bi| = √(a² + b²)
 * This is the critical function for divergence detection in fractal iteration.
 * When the modulus exceeds a threshold, the point is considered to diverge.
 *
 * @ingroup complex_ops
 *
 * @param[in] num Complex number whose modulus is to be calculated
 *
 * @return double Non-negative modulus of the complex number
 */
double	complx_module(t_complex num)
{
	return (sqrt((num.real * num.real) + (num.imag * num.imag)));
}
