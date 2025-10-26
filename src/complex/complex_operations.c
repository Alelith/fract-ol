/**
 * @file complex_operations.c
 * @author Lilith Estévez Boeta
 * @brief This file contains basic arithmetic operations for complex numbers including multiplication, addition, division, inversion, and modulus calculation.
 */

#include "fract_ol.h"

/**
 * @brief Multiplies two complex numbers.
 * 
 * @param a First complex number operand.
 * @param b Second complex number operand.
 * 
 * @return t_complex The product of a and b.
 */
t_complex	multiply_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real * b.real) - (a.imag * b.imag);
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return (result);
}

/**
 * @brief Adds two complex numbers.
 * 
 * @param a First complex number operand.
 * @param b Second complex number operand.
 * 
 * @return t_complex The sum of a and b.
 */
t_complex	sum_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real + b.real);
	result.imag = (a.imag + b.imag);
	return (result);
}

/**
 * @brief Divides two complex numbers.
 * 
 * @param a The dividend (numerator) complex number.
 * @param b The divisor (denominator) complex number.
 * 
 * @return t_complex The quotient of a divided by b.
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
 * @brief Computes the multiplicative inverse (reciprocal) of a complex number.
 * 
 * @param a The complex number to invert.
 * 
 * @return t_complex The inverse of a (1/a).
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
 * @brief Calculates the modulus (absolute value) of a complex number.
 * 
 * @param num The complex number.
 * 
 * @return double The modulus of num.
 */
double	complx_module(t_complex num)
{
	return (sqrt((num.real * num.real) + (num.imag * num.imag)));
}
