/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_trigonometric.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:30:57 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:44 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** COMPLEX TRIGONOMETRIC FUNCTIONS - Hyperbolic functions for complex numbers
**
** This file implements trigonometric and hyperbolic functions for complex
** numbers. These functions enable the creation of fractal variations that
** apply trigonometric transformations to standard fractal formulas,
** creating unique and visually interesting mathematical patterns.
*/

#include "fract_ol.h"

/*
** sinh_complx - Calculate hyperbolic sine of complex number
** @num: Complex number input (z = a + bi)
**
** Computes sinh(z) for complex z using Euler's formula:
** sinh(a + bi) = sinh(a)cos(b) + i*cosh(a)sin(b)
** 
** This function creates hyperbolic transformations in fractal iterations,
** producing curved and flowing patterns distinct from standard polynomial
** fractals. Used in the sinh_mandelbrot fractal variation to create
** organic, wave-like fractal boundaries. Returns transformed complex number.
*/
t_complex	sinh_complx(t_complex num)
{
	t_complex	result;		/* Result of hyperbolic sine */

	/* Real part: sinh(real) * cos(imaginary) */
	result.real = sinh(num.real) * cos(num.imag);
	/* Imaginary part: cosh(real) * sin(imaginary) */
	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}
