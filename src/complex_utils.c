/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:30:51 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 19:51:45 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_complex	multiply_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real * b.real) - (a.imag * b.imag);
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return (result);
}

t_complex	sum_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real + b.real);
	result.imag = (a.imag + b.imag);
	return (result);
}

t_complex	sinh_complx(t_complex num)
{
	t_complex	result;

	result.real = sinh(num.real) * cos(num.imag);
	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}

t_complex	div_complx(t_complex a, t_complex b)
{
	t_complex	result;
	double		den;

	den = (b.real * b.real) + (b.imag * b.imag);
	result.real = (a.real * b.real + a.imag * b.imag) / den;
	result.imag = (a.imag * b.real - a.real * b.imag) / den;
	return (result);
}

double	complx_module(t_complex num)
{
	return (sqrt((num.real * num.real) + (num.imag * num.imag)));
}
