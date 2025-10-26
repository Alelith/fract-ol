/**
 * @file color.c
 * @author Lilith Estévez Boeta
 * @brief This file contains color generation functions including HSV to RGB conversion and psychedelic color schemes.
 */

#include "fract_ol.h"

/**
 * @brief Combines TRGB components into a single color value.
 * 
 * @param t Transparency/Alpha channel value (0-255).
 * @param r Red channel value (0-255).
 * @param g Green channel value (0-255).
 * @param b Blue channel value (0-255).
 * 
 * @return int Color value in TRGB format (0xTTRRGGBB).
 */
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

/**
 * @brief Fills an RGB array with the specified color components.
 * 
 * @param a Red channel component (0-1 range).
 * @param b Green channel component (0-1 range).
 * @param c Blue channel component (0-1 range).
 * @param rgb Pointer to array of 3 doubles to store RGB values.
 * 
 * @return void
 */
static void	fill_rgb(double a, double b, double c, double *rgb)
{
	rgb[0] = a;
	rgb[1] = b;
	rgb[2] = c;
}

/**
 * @brief Converts HSV color space to RGB color space.
 * 
 * @param h Hue value (0-360 degrees).
 * @param s Saturation value (0-1).
 * @param v Value/Brightness (0-1).
 * @param out Pointer to output array of 3 ints for RGB values (0-255).
 * 
 * @return void
 */
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

/**
 * @brief Generates a color based on iteration count using HSV color model.
 * @details Maps iteration count to hue while maintaining saturation and value.
 * 
 * @param iter Current iteration count (divergence measure).
 * @param max_iter Maximum number of iterations.
 * 
 * @return int Color value in TRGB format (0xTTRRGGBB).
 */
int	get_color_hsv(int iter, int max_iter)
{
	double	t;
	double	hue;
	double	sat;
	double	val;
	int		rgb[3];

	t = (double)iter / (max_iter - 1);
	hue = 360.0 * t + 225;
	if (hue > 360.0)
		hue -= 360.0;
	sat = 1.0;
	val = ((double)iter / max_iter) + 0.25;
	if (val > 1)
		val = 1;

	hsv_to_rgb(hue, sat, val, &rgb[0]);
	return (get_trgb(255, rgb[0], rgb[1], rgb[2]));
}

/**
 * @brief Generates a psychedelic color based on iteration count using sinusoidal waves.
 * @details Uses sine functions with different phase offsets for each RGB channel.
 *          Implements smooth color transitions using lower frequency and smooth envelope.
 * 
 * @param iter Current iteration count (divergence measure).
 * @param phase Phase offset for the sine waves (for animation).
 * @param iterations Maximum number of iterations.
 * 
 * @return int Color value in TRGB format (0xTTRRGGBB).
 */
int	psychedelic_color(int iter, double phase, int iterations)
{
	double	t;
	double	freq;
	double	r_s;
	double	g_s;
	double	b_s;
	double	envelope;

	t = (double)iter / iterations;
	freq = 3.0;
	
	envelope = 0.5 + 0.5 * sin(PI * t);

	r_s = sin(freq * t * 2 * PI + phase);
	g_s = sin(freq * t * 2 * PI + phase + 0.33 * 2 * PI);
	b_s = sin(freq * t * 2 * PI + phase + 0.66 * 2 * PI);

	return (get_trgb(255,
			127.5 * (r_s + 1.0) * envelope,
			127.5 * (g_s + 1.0) * envelope,
			127.5 * (b_s + 1.0) * envelope));
}
