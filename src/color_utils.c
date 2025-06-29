/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:39:32 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 01:10:59 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	psychedelic_color(int iter, int max_iter, double phase)
{
	double	t;
	double	freq;
	double	r_s;
	double	g_s;
	double	b_s;

	t = (double)iter / max_iter;
	freq = 10.0;
	r_s = sin(freq * t * 2 * PI + phase);
	g_s = sin(freq * t * 2 * PI + phase + 0.33 * 2 * PI);
	b_s = sin(freq * t * 2 * PI + phase + 0.66 * 2 * PI);
	return ((255 << 24)
		| ((int)(127.5 * (r_s + 1.0)) << 16)
		| ((int)(127.5 * (g_s + 1.0)) << 8)
		| (int)(127.5 * (b_s + 1.0)));
}
