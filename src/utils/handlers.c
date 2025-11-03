/**
 * @file handlers.c
 * @author Lilith Estévez Boeta
 * @brief This file contains event handlers for keyboard input, mouse wheel zoom, and window closing.
 */

#include "fract_ol.h"

/**
 * @brief Closes the application window and cleans up resources.
 * @details Destroys the mutex, texture, renderer, window, and SDL2, then exits the program.
 * @ingroup graphics_module
 * 
 * @param vars Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	close_window(t_data *vars)
{
	pthread_mutex_destroy(&vars->pixels_mutex);
	if (vars->pixels)
		free(vars->pixels);
	if (vars->texture)
		SDL_DestroyTexture(vars->texture);
	if (vars->renderer)
		SDL_DestroyRenderer(vars->renderer);
	if (vars->window)
		SDL_DestroyWindow(vars->window);
	SDL_Quit();
	exit(0);
}

/**
 * @brief Handles keyboard input events.
 * @details Closes the window when ESC key is pressed.
 * @ingroup graphics_module
 * 
 * @param keycode The SDL key code of the pressed key.
 * @param vars Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	key_handler(SDL_Keycode keycode, t_data *vars)
{
	if (keycode == SDLK_ESCAPE)
		close_window(vars);
	return (0);
}

/**
 * @brief Handles mouse wheel zoom events.
 * @details Zooms in/out based on mouse wheel direction, centered at mouse cursor position.
 * @ingroup graphics_module
 * 
 * @param mousecode Mouse button code (SDL_BUTTON_WHEELUP or SDL_BUTTON_WHEELDOWN).
 * @param x Mouse X coordinate.
 * @param y Mouse Y coordinate.
 * @param img Pointer to the main data structure.
 * 
 * @return int Always returns 0.
 */
int	zoom(Uint8 mousecode, int x, int y, t_data *img)
{
	double		zoom_factor;
	t_complex	mouse_point;
	double		width;
	double		height;

	if (x < 0 || y < 0)
		return (0);
	if (mousecode == SDL_BUTTON_LEFT)
		zoom_factor = 1.1;
	else if (mousecode == SDL_BUTTON_RIGHT)
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

	img->color_off += 0.125;
	redraw_fractal(img);
	return (0);
}
