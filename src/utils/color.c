/**
 * @file color.c
 * @brief Color generation algorithms including HSV and psychedelic mapping
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Packs ARGB color components into a 32-bit integer
 *
 * @details Combines transparency (alpha), red, green, and blue channels into
 * a single 32-bit value in ARGB8888 format. Each component occupies 8 bits:
 * alpha in bits 24-31, red in 16-23, green in 8-15, blue in 0-7.
 *
 * @ingroup utils
 *
 * @param[in] t Transparency value (0-255, typically 255 for opaque)
 * @param[in] r Red channel intensity (0-255)
 * @param[in] g Green channel intensity (0-255)
 * @param[in] b Blue channel intensity (0-255)
 *
 * @return int Packed 32-bit ARGB color value
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
 * @brief Helper function to populate RGB array during HSV conversion
 *
 * @details Assigns three color component values to an RGB array. Used as a
 * convenience function during HSV to RGB conversion to avoid code duplication
 * across the six hue sectors of the HSV color wheel.
 *
 * @ingroup utils
 *
 * @param[in] a First color component value (0.0-1.0)
 * @param[in] b Second color component value (0.0-1.0)
 * @param[in] c Third color component value (0.0-1.0)
 * @param[out] rgb Array to receive the three color values
 */
static void	fill_rgb(double a, double b, double c, double *rgb)
{
	rgb[0] = a;
	rgb[1] = b;
	rgb[2] = c;
}

/**
 * @brief Converts HSV color space to RGB color space
 *
 * @details Transforms hue, saturation, and value parameters into red, green,
 * and blue components. Uses the standard HSV color wheel divided into six
 * 60-degree sectors, each with a different RGB mixing formula. Saturation
 * controls color intensity and value controls brightness.
 *
 * @ingroup utils
 *
 * @param[in] h Hue angle in degrees (0-360)
 * @param[in] s Saturation (0.0-1.0, where 0 is grayscale and 1 is full color)
 * @param[in] v Value/brightness (0.0-1.0, where 0 is black and 1 is full brightness)
 * @param[out] out Integer array receiving RGB values scaled to 0-255
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
 * @brief Generates a color based on iteration count using HSV mapping
 *
 * @details Maps the normalized iteration count to a smooth color gradient by
 * rotating through the hue spectrum. Higher iteration counts (slower divergence)
 * cycle through different hues. Saturation is kept at maximum for vibrant colors,
 * and value is adjusted to increase brightness with iteration count, creating
 * visually pleasing fractal bands.
 *
 * @ingroup utils
 *
 * @param[in] iter Iteration count when divergence was detected
 * @param[in] max_iter Maximum possible iterations
 *
 * @return int 32-bit ARGB color value for the given iteration count
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
 * @brief Generates animated psychedelic colors with phase shifting
 *
 * @details Creates vibrant, animated color patterns using sine waves on
 * separate RGB channels with 120-degree phase offsets. The phase parameter
 * enables color cycling animation over time. An envelope function modulates
 * intensity based on iteration count, creating pulsing visual effects that
 * emphasize fractal structure boundaries.
 *
 * @ingroup utils
 *
 * @param[in] iter Iteration count when divergence was detected
 * @param[in] phase Animation phase offset (incremented each frame for cycling)
 * @param[in] iterations Maximum iteration count for normalization
 *
 * @return int 32-bit ARGB color value with animated psychedelic effect
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
