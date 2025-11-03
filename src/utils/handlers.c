/**
 * @file handlers.c
 * @brief Event handlers for user input including keyboard and mouse
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Cleanly shuts down the application and frees all resources
 *
 * @details Destroys the pixel buffer mutex, frees allocated memory, and
 * releases all SDL2 resources including texture, renderer, and window.
 * Calls SDL_Quit to properly shut down SDL subsystems before exiting.
 * This function never returns.
 *
 * @ingroup utils
 *
 * @param[in,out] vars Pointer to application state containing resources to free
 *
 * @return int Always returns 0 (never reached due to exit call)
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
 * @brief Processes keyboard input events
 *
 * @details Handles keyboard events from SDL2. Currently only implements the
 * ESC key for application termination by calling close_window. Can be extended
 * to handle additional keyboard controls for parameter adjustment, color scheme
 * switching, or view manipulation.
 *
 * @ingroup utils
 *
 * @param[in] keycode SDL keycode identifying which key was pressed
 * @param[in,out] vars Pointer to application state
 *
 * @return int Always returns 0 after processing the key event
 */
int	key_handler(SDL_Keycode keycode, t_data *vars)
{
	if (keycode == SDLK_ESCAPE)
		close_window(vars);
	return (0);
}

/**
 * @brief Handles zoom operations centered on the mouse cursor position
 *
 * @details Implements interactive zoom by adjusting the complex plane viewing
 * window. Left mouse button (or wheel up) zooms in by 1.1x, right button
 * (or wheel down) zooms out by 0.9x. The zoom is centered on the cursor's
 * position in the complex plane, maintaining that point's position on screen.
 * Updates viewing bounds, increments color phase for animation, and triggers
 * a complete re-render.
 *
 * @ingroup utils
 *
 * @param[in] mousecode SDL mouse button code (SDL_BUTTON_LEFT or SDL_BUTTON_RIGHT)
 * @param[in] x Horizontal screen coordinate of mouse cursor
 * @param[in] y Vertical screen coordinate of mouse cursor
 * @param[in,out] img Pointer to application state to be updated with new zoom
 *
 * @return int Returns 0 after processing zoom event
 * @retval 0 Zoom processed successfully or invalid input detected
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
