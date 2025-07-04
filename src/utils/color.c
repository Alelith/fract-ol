/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:39:32 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/04 13:48:24 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static int	get_trgb(double t, double r, double g, double b)
{
	int	it;
	int	ir;
	int	ig;
	int	ib;
	int	res;

	it = t;
	ir = r;
	ig = g;
	ib = b;
	res = it << 24
		| ir << 16
		| ig << 8
		| ib;
	return (res);
}

static void	fill_rgb(double a, double b, double c, double *rgb)
{
	rgb[0] = a;
	rgb[1] = b;
	rgb[2] = c;
}

static void	hsv_to_rgb(double h, double s, double v, int *out)
{
	double	c;
	double	x;
	double	m;
	double	rgb[3];

	c = v * s;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	m = v - c;
	if (h < 60)
		fill_rgb(c, x, 0, &rgb[0]);
	else if (h < 120)
		fill_rgb(x, c, 0, &rgb[0]);
	else if (h < 180)
		fill_rgb(0, c, x, &rgb[0]);
	else if (h < 240)
		fill_rgb(0, x, c, &rgb[0]);
	else if (h < 300)
		fill_rgb(x, 0, c, &rgb[0]);
	else
		fill_rgb(c, 0, x, &rgb[0]);
	out[0] = (int)((rgb[0] + m) * 255);
	out[1] = (int)((rgb[1] + m) * 255);
	out[2] = (int)((rgb[2] + m) * 255);
}

int	get_color_hsv(int iter)
{
	double	t;
	double	hue;
	double	sat;
	double	val;
	int		rgb[3];

	t = (double)iter / (ITER - 1);
	hue = 360.0 * t + 225;
	if (hue > 360.0)
		hue -= 360.0;
	sat = 1.0;
	val = ((double)iter / ITER) + 0.125;
	if (val > 1)
		val = 1;
	hsv_to_rgb(hue, sat, val, &rgb[0]);
	return (get_trgb(255, rgb[0], rgb[1], rgb[2]));
}

int	psychedelic_color(int iter, double phase)
{
	double	t;
	double	freq;
	double	r_s;
	double	g_s;
	double	b_s;

	t = (double)iter / ITER;
	freq = 10.0;
	r_s = sin(freq * t * 2 * PI + phase);
	g_s = sin(freq * t * 2 * PI + phase + 0.33 * 2 * PI);
	b_s = sin(freq * t * 2 * PI + phase + 0.66 * 2 * PI);
	return (get_trgb(255,
			127.5 * (r_s + 1.0),
			127.5 * (g_s + 1.0),
			127.5 * (b_s + 1.0)));
}
