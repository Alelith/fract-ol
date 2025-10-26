/**
 * @file handlers.c
 * @author Lilith Estévez Boeta
 * @brief This file contains event handlers for keyboard input, mouse wheel zoom, and window closing.
 */

#include "fract_ol.h"

/**
 * @brief Closes the application window and cleans up resources.
 * @details Destroys the mutex and window, then exits the program.
 * 
 * @param vars Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	close_window(t_data *vars)
{
	pthread_mutex_destroy(&vars->img_mutex);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

/**
 * @brief Handles keyboard input events.
 * @details Currently closes the window when ESC key (65307) is pressed.
 * 
 * @param keycode The key code of the pressed key.
 * @param vars Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	key_handler(int keycode, t_data *vars)
{
	if (keycode == 65307)
		close_window(vars);
	return (0);
}

/**
 * @brief Handles mouse wheel zoom events.
 * @details Zooms in/out based on mouse wheel direction, centered at mouse cursor position.
 * 
 * @param mousecode Mouse button code (4 for scroll up, 5 for scroll down).
 * @param x Mouse X coordinate.
 * @param y Mouse Y coordinate.
 * @param img Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	zoom(int mousecode, int x, int y, t_data *img)
{
	double		zoom_factor;
	t_complex	mouse_point;
	double		width;
	double		height;

	if (x < 0 && y < 0)
		return (0);
	if (mousecode == 4)
		zoom_factor = 1.1;
	else if (mousecode == 5)
		zoom_factor = 0.9;
	else
		return (0);

	img->zoom_factor *= zoom_factor;
	width = img->max.real - img->min.real;
	height = img->max.imag - img->min.imag;

	mouse_point.real = ((double)x / SCREEN_WIDTH - 0.5) * width + img->min.real;
	mouse_point.imag = ((double)y / SCREEN_HEIGHT - 0.5) * height * ((double)SCREEN_HEIGHT / SCREEN_WIDTH) + img->min.imag;

	img->min.real = mouse_point.real - (mouse_point.real - img->min.real) / zoom_factor;
	img->min.imag = mouse_point.imag - (mouse_point.imag - img->min.imag) / zoom_factor;
	img->max.real = mouse_point.real + (img->max.real - mouse_point.real) / zoom_factor;
	img->max.imag = mouse_point.imag + (img->max.imag - mouse_point.imag) / zoom_factor;

	img -> color_off += 0.125;
	redraw_fractal(img);
	return (0);
}
