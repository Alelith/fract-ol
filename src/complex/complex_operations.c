/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:30:51 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:38 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** COMPLEX OPERATIONS - Mathematical operations for complex numbers
**
** This file implements fundamental arithmetic operations for complex numbers.
** These operations are essential for fractal calculations as fractals are
** defined in the complex plane. All functions follow standard complex
** arithmetic rules and are optimized for fractal iteration performance.
*/

#include "fract_ol.h"

/*
** multiply_complx - Multiply two complex numbers
** @a: First complex number (multiplicand)
** @b: Second complex number (multiplier)
**
** Performs complex multiplication using the formula:
** (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
** This is the core operation for fractal iteration formulas like z².
** Returns the product as a new complex number.
*/
t_complex	multiply_complx(t_complex a, t_complex b)
{
	t_complex	result;		/* Result of multiplication */

	/* Real part: ac - bd */
	result.real = (a.real * b.real) - (a.imag * b.imag);
	/* Imaginary part: ad + bc */
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return (result);
}

/*
** sum_complx - Add two complex numbers
** @a: First complex number (addend)
** @b: Second complex number (addend)
**
** Performs complex addition using the formula:
** (a + bi) + (c + di) = (a + c) + (b + d)i
** Used in fractal iteration formulas like z² + c in Mandelbrot set.
** Returns the sum as a new complex number.
*/
t_complex	sum_complx(t_complex a, t_complex b)
{
	t_complex	result;		/* Result of addition */

	result.real = (a.real + b.real);	/* Add real parts */
	result.imag = (a.imag + b.imag);	/* Add imaginary parts */
	return (result);
}

/*
** div_complx - Divide two complex numbers
** @a: Dividend complex number
** @b: Divisor complex number
**
** Performs complex division using the formula:
** (a + bi) / (c + di) = [(ac + bd) + (bc - ad)i] / (c² + d²)
** Multiplies numerator and denominator by conjugate of denominator
** to eliminate imaginary part from denominator. Used in advanced
** fractal variations that require complex division operations.
** Returns the quotient as a new complex number.
*/
t_complex	div_complx(t_complex a, t_complex b)
{
	t_complex	result;		/* Result of division */
	double		den;		/* Denominator (modulus squared) */

	den = (b.real * b.real) + (b.imag * b.imag);	/* |b|² */
	/* Real part: (ac + bd) / |b|² */
	result.real = (a.real * b.real + a.imag * b.imag) / den;
	/* Imaginary part: (bc - ad) / |b|² */
	result.imag = (a.imag * b.real - a.real * b.imag) / den;
	return (result);
}

/*
** inv_complx - Calculate multiplicative inverse of complex number
** @a: Complex number to invert
**
** Computes 1/a for complex number a using the formula:
** 1 / (a + bi) = (a - bi) / (a² + b²)
** This is equivalent to dividing by the conjugate and scaling by
** the modulus squared. Used in fractal variations requiring
** complex reciprocals. Returns the inverse as a new complex number.
*/
t_complex	inv_complx(t_complex a)
{
	t_complex	result;		/* Result of inversion */
	double		den;		/* Denominator (modulus squared) */

	den = (a.real * a.real) + (a.imag * a.imag);	/* |a|² */
	result.real = a.real / den;			/* Real part / |a|² */
	result.imag = -a.imag / den;			/* -Imaginary part / |a|² */
	return (result);
}

/*
** complx_module - Calculate modulus (magnitude) of complex number
** @num: Complex number to calculate modulus for
**
** Computes |z| = √(a² + b²) for complex number z = a + bi.
** This represents the distance from the origin in the complex plane.
** Essential for fractal escape condition testing - when |z| exceeds
** a threshold (typically 2), the point is considered to escape to infinity.
** Returns the modulus as a double precision value.
*/
double	complx_module(t_complex num)
{
	return (sqrt((num.real * num.real) + (num.imag * num.imag)));
}
