/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:39:32 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/26 18:51:05 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	insert_colors(float *rgb, float r, float g, float b)
{
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

static void	convert_hsv(float *rgb, float h, float s, float v)
{
	float	c;
	float	x;

	c = v * s;
	x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
	if (h < 60)
		insert_colors(rgb, c, x, 0);
	else if (h < 120)
		insert_colors(rgb, x, c, 0);
	else if (h < 180)
		insert_colors(rgb, 0, c, x);
	else if (h < 240)
		insert_colors(rgb, 0, x, c);
	else if (h < 300)
		insert_colors(rgb, x, 0, c);
	else
		insert_colors(rgb, c, 0, x);
}

static int	hsv_to_rgb(float h, float s, float v)
{
	float	m;
	float	rgb[3];

	convert_hsv(&rgb[0], h, s, v);
	return (get_trgb(0, round((rgb[0] + m) * 255.0)
			, round((rgb[1] + m) * 255.0)
			, round((rgb[2] + m) * 255.0)));
}

int	get_trgb(int t, int r, int g, int b)
{
	if (t > 255 || r > 255 || g > 255 || b > 255)
		return (-1);
	return (t << 24 | r << 16 | g << 8 | b);
}

int	trgb_rainbow(int value, float offset)
{
	float	h;
	float	s;
	float	v;

	if (value < 0)
		value = 0;
	if (value > 255)
		value = 255;
	h = fmodf((360.0f * value) / 255.0f + offset, 360.0f);
	if (h < 0)
		h += 360.0f;
	s = 1.0f;
	v = ((float)value / 255.0f) + 0.125;
	if (v > 1)
		v = 1;
	return (hsv_to_rgb(h, s, v));
}
