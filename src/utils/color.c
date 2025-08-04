/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:39:32 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** COLOR SYSTEM - Advanced fractal coloring and visualization schemes
**
** This file implements sophisticated coloring algorithms for fractal
** visualization using HSV color space and psychedelic effects. It provides
** smooth color gradients, animated rainbow effects, and professional
** color mapping to enhance fractal detail visibility and create
** visually stunning mathematical art.
*/

#include "fract_ol.h"

/*
** get_trgb - Pack TRGB components into MLX color format
** @t: Transparency/Alpha component (0-255)
** @r: Red component (0-255)
** @g: Green component (0-255)
** @b: Blue component (0-255)
**
** Combines separate color components into a single 32-bit integer
** using MLX's TRGB format. The transparency component allows for
** alpha blending effects, while RGB components define the visible
** color. Format: 0xTTRRGGBB where each pair is a hex byte.
** Returns packed color value suitable for MLX pixel operations.
*/
static int	get_trgb(double t, double r, double g, double b)
{
	int	it;			/* Integer transparency */
	int	ir;			/* Integer red */
	int	ig;			/* Integer green */
	int	ib;			/* Integer blue */
	int	res;			/* Packed result */

	it = t;				/* Convert double to int */
	ir = r;				/* Convert double to int */
	ig = g;				/* Convert double to int */
	ib = b;				/* Convert double to int */
	
	/* Pack components using bit shifting */
	res = it << 24			/* Transparency in high byte */
		| ir << 16		/* Red in second byte */
		| ig << 8		/* Green in third byte */
		| ib;			/* Blue in low byte */
	return (res);
}

/*
** fill_rgb - Helper function to fill RGB array
** @a: First color component value
** @b: Second color component value
** @c: Third color component value
** @rgb: Array to store the RGB values
**
** Simple utility function to assign three color component values
** to an RGB array. Used during HSV to RGB conversion to organize
** color components before final processing. Improves code
** readability by reducing repetitive array assignments.
*/
static void	fill_rgb(double a, double b, double c, double *rgb)
{
	rgb[0] = a;			/* Assign first component */
	rgb[1] = b;			/* Assign second component */
	rgb[2] = c;			/* Assign third component */
}

/*
** hsv_to_rgb - Convert HSV color space to RGB color space
** @h: Hue component (0-360 degrees)
** @s: Saturation component (0-1)
** @v: Value/brightness component (0-1)
** @out: Output array for RGB values (0-255 each)
**
** Implements the standard HSV to RGB conversion algorithm using
** the mathematical formulas for color space transformation. HSV
** provides more intuitive color control for procedural generation,
** while RGB is required for display. The algorithm uses chroma,
** intermediate values, and hue sectors to calculate RGB components.
*/
static void	hsv_to_rgb(double h, double s, double v, int *out)
{
	double	c;			/* Chroma component */
	double	x;			/* Intermediate value */
	double	m;			/* Match component */
	double	rgb[3];			/* Temporary RGB storage */

	c = v * s;			/* Calculate chroma */
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));	/* Intermediate value */
	m = v - c;			/* Calculate match component */
	
	/* Determine RGB values based on hue sector */
	if (h < 60)
		fill_rgb(c, x, 0, &rgb[0]);		/* Red-Yellow sector */
	else if (h < 120)
		fill_rgb(x, c, 0, &rgb[0]);		/* Yellow-Green sector */
	else if (h < 180)
		fill_rgb(0, c, x, &rgb[0]);		/* Green-Cyan sector */
	else if (h < 240)
		fill_rgb(0, x, c, &rgb[0]);		/* Cyan-Blue sector */
	else if (h < 300)
		fill_rgb(x, 0, c, &rgb[0]);		/* Blue-Magenta sector */
	else
		fill_rgb(c, 0, x, &rgb[0]);		/* Magenta-Red sector */
	
	/* Convert to 0-255 range and add match component */
	out[0] = (int)((rgb[0] + m) * 255);	/* Final red component */
	out[1] = (int)((rgb[1] + m) * 255);	/* Final green component */
	out[2] = (int)((rgb[2] + m) * 255);	/* Final blue component */
}

/*
** get_color_hsv - Generate HSV-based colors for fractal visualization
** @iter: Iteration count when point escaped
**
** Creates smooth color gradients using HSV color space for fractal
** coloring. Maps iteration count to hue for color cycling, uses full
** saturation for vibrancy, and adjusts value based on iteration depth.
** The hue offset of 225° provides an aesthetically pleasing starting
** color. This creates professional-looking fractal visualizations
** with smooth color transitions between iteration levels.
*/
int	get_color_hsv(int iter)
{
	double	t;			/* Normalized iteration value */
	double	hue;			/* Hue component (0-360°) */
	double	sat;			/* Saturation component */
	double	val;			/* Value/brightness component */
	int		rgb[3];			/* RGB output array */

	t = (double)iter / (ITER - 1);		/* Normalize to 0-1 range */
	hue = 360.0 * t + 225;			/* Map to hue with offset */
	if (hue > 360.0)			/* Wrap around if > 360° */
		hue -= 360.0;
	sat = 1.0;				/* Full saturation for vibrancy */
	val = ((double)iter / ITER) + 0.25;	/* Brightness based on iterations */
	if (val > 1)				/* Clamp to maximum brightness */
		val = 1;
	
	hsv_to_rgb(hue, sat, val, &rgb[0]);	/* Convert to RGB */
	return (get_trgb(255, rgb[0], rgb[1], rgb[2]));	/* Pack and return */
}

/*
** psychedelic_color - Generate animated rainbow effects for fractals
** @iter: Iteration count when point escaped
** @phase: Animation phase offset for color cycling
**
** Creates dynamic, animated colors using trigonometric functions for
** smooth color transitions. Each RGB component uses sine waves with
** different phase offsets to create rainbow effects. The frequency
** controls color cycling speed, while the phase enables animation
** by shifting the color spectrum over time. This creates visually
** striking psychedelic effects that enhance fractal exploration.
*/
int	psychedelic_color(int iter, double phase)
{
	double	t;			/* Normalized iteration value */
	double	freq;			/* Frequency of color cycling */
	double	r_s;			/* Red sine component */
	double	g_s;			/* Green sine component */
	double	b_s;			/* Blue sine component */

	t = (double)iter / ITER;		/* Normalize iteration count */
	freq = 10.0;				/* Set color cycling frequency */
	
	/* Generate sine waves with different phase offsets */
	r_s = sin(freq * t * 2 * PI + phase);				/* Red phase */
	g_s = sin(freq * t * 2 * PI + phase + 0.33 * 2 * PI);		/* Green phase */
	b_s = sin(freq * t * 2 * PI + phase + 0.66 * 2 * PI);		/* Blue phase */
	
	/* Convert sine values (-1 to 1) to color range (0 to 255) */
	return (get_trgb(255,
			127.5 * (r_s + 1.0),		/* Red component */
			127.5 * (g_s + 1.0),		/* Green component */
			127.5 * (b_s + 1.0)));		/* Blue component */
}
