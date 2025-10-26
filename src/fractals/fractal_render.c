/**
 * @file fractal_render.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the main fractal rendering engine with multi-threaded rendering and coordinate mapping functions.
 */

#include "fract_ol.h"

/**
 * @brief Converts screen coordinates to complex plane coordinates for Mandelbrot set.
 * @details Maps pixel coordinates to complex numbers in the Mandelbrot plane.
 * 
 * @param data Pointer to the main data structure containing zoom and bounds information.
 * @param screen_pos The screen position (pixel coordinates).
 */
static void	calculate_c_off(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.real += data -> min.real;
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	c.imag += data -> min.imag;
	draw_mandelbrot(data, c, screen_pos);
}

/**
 * @brief Converts screen coordinates to complex plane coordinates for Julia set.
 * @details Maps pixel coordinates to complex numbers for initial Z values in Julia set.
 * 
 * @param data Pointer to the main data structure containing zoom and bounds information.
 * @param screen_pos The screen position (pixel coordinates).
 */
static void	calculate_z(t_data *data, t_vector2 screen_pos)
{
	t_complex	z;

	z.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	z.real *= data -> max.real - data -> min.real;
	z.real += data -> min.real;
	z.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	z.imag *= data -> max.imag - data -> min.imag;
	z.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	z.imag += data -> min.imag;
	draw_julia(data, z, screen_pos);
}

/**
 * @brief Converts screen coordinates to complex plane coordinates for Eye/Sinh Mandelbrot.
 * @details Maps pixel coordinates to complex numbers for Eye and Sinh Mandelbrot sets.
 * 
 * @param data Pointer to the main data structure containing zoom and bounds information.
 * @param screen_pos The screen position (pixel coordinates).
 */
static void	calculate_c(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;

	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.real += data -> min.real;

	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;
	c.imag += data -> min.imag;

	if (data -> type == SINH_MANDELBROT)
		draw_sinh_mandelbrot(data, c, screen_pos);
	else if (data -> type == EYE_MANDELBROT)
		draw_eye_mandelbrot(data, c, screen_pos);
}

/**
 * @brief Calculates the maximum number of iterations based on zoom factor.
 * @details Dynamically adjusts iteration depth for better visual effects at different zoom levels.
 * 
 * @param data Pointer to the main data structure containing the zoom factor.
 * @param max_iter The base maximum number of iterations.
 * 
 * @return int The adjusted maximum number of iterations.
 */
int	calculate_iterations(t_data *data, int max_iter)
{
	return (max_iter * log2(data->zoom_factor + 1));
}

/**
 * @brief Renders a portion of the fractal in a separate thread.
 * @details Thread worker function that calculates and renders fractal pixels for assigned rows.
 * 
 * @param arg Pointer to t_thread_data structure containing thread-specific parameters.
 * 
 * @return void* Returns NULL.
 */
void	*render_fractal_threaded(void *arg)
{
	t_thread_data	*thread_data;
	t_data			*data;
	t_vector2		screen_pos;

	thread_data = (t_thread_data *)arg;
	data = thread_data->data;

	screen_pos.y = thread_data->start_y - 1;
	screen_pos.x = -1;

	while (++screen_pos.y < thread_data->end_y)
	{
		screen_pos.x = -1;

		while (++screen_pos.x < SCREEN_WIDTH)
		{

			if (data->type == MANDELBROT)
				calculate_c_off(data, screen_pos);
			else if (data->type == JULIA)
				calculate_z(data, screen_pos);
			else if (data->type == SINH_MANDELBROT
				|| data->type == EYE_MANDELBROT)
				calculate_c(data, screen_pos);
		}
	}
	return (NULL);
}

/**
 * @brief Renders the entire fractal using multi-threading.
 * @details Distributes fractal rendering across multiple threads and displays the result.
 * 
 * @param data Pointer to the main data structure containing fractal parameters and window info.
 */
void	redraw_fractal(t_data *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				remaining_rows;
	int				i;

	mlx_clear_window(data->mlx, data->win);

	rows_per_thread = SCREEN_HEIGHT / NUM_THREADS;
	remaining_rows = SCREEN_HEIGHT % NUM_THREADS;

	i = -1;
	while (++i < NUM_THREADS)
	{

		thread_data[i].data = data;
		thread_data[i].thread_id = i;
		thread_data[i].start_y = i * rows_per_thread;
		thread_data[i].end_y = (i + 1) * rows_per_thread;

		if (i < remaining_rows)
		{
			thread_data[i].start_y += i;
			thread_data[i].end_y += i + 1;
		}
		else
		{
			thread_data[i].start_y += remaining_rows;
			thread_data[i].end_y += remaining_rows;
		}

		pthread_create(&threads[i], NULL, render_fractal_threaded,
			&thread_data[i]);
	}

	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
