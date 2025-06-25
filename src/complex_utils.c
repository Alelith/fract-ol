/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:30:51 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/25 22:31:17 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	print_complx(t_complex num)
{
	ft_printf("%f + %fi\n", num.real, num.imag);
}

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

t_complex	subs_complx(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real - b.real);
	result.imag = (a.imag - b.imag);
	return (result);
}

double	complx_module(t_complex num)
{
	return (sqrt((num.real * num.real) + (num.imag * num.imag)));
}
