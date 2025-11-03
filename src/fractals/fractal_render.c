/**
 * @file fractal_render.c
 * @brief Core fractal rendering engine with multi-threaded computation
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Maps screen coordinates to complex plane and renders Mandelbrot fractal
 *
 * @details Transforms pixel coordinates to complex plane coordinates taking
 * into account the current zoom level and viewing window. The complex number
 * becomes the C parameter in the Mandelbrot iteration z = z² + c.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] data Pointer to application state with viewing parameters
 * @param[in] screen_pos Screen pixel coordinates to be mapped
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
 * @brief Maps screen coordinates to complex plane and renders Julia set fractal
 *
 * @details Transforms pixel coordinates to the initial Z value for Julia set
 * iteration. The C parameter is fixed and provided by the user at program start.
 * Iteration formula is z_{n+1} = z_n² + c where c remains constant.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] data Pointer to application state with viewing parameters
 * @param[in] screen_pos Screen pixel coordinates to be mapped
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
 * @brief Maps coordinates and dispatches to appropriate Mandelbrot variant
 *
 * @details Transforms screen coordinates to complex plane and determines which
 * Mandelbrot variant to render based on the fractal type. Handles Sinh, Eye,
 * and Dragon variants, each with different iteration formulas.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] data Pointer to application state with viewing parameters
 * @param[in] screen_pos Screen pixel coordinates to be mapped
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

	else if (data -> type == DRAGON_MANDELBROT)
		draw_dragon_mandelbrot(data, c, screen_pos);
}

/**
 * @brief Calculates adaptive iteration count based on current zoom level
 *
 * @details Dynamically adjusts the maximum iteration count using a logarithmic
 * scale relative to zoom level. Higher zoom levels reveal finer detail and
 * require more iterations to accurately determine convergence or divergence.
 * Formula: iterations = max_iter * log₂(zoom_factor + 1)
 *
 * @ingroup fractal_render
 *
 * @param[in] data Pointer to application state containing current zoom factor
 * @param[in] max_iter Base maximum iteration count (typically ITER constant)
 *
 * @return int Scaled iteration count for current zoom level
 */
int	calculate_iterations(t_data *data, int max_iter)
{
	return (max_iter * log2(data->zoom_factor + 1));
}

/**
 * @brief Thread worker function that renders a horizontal section of the fractal
 *
 * @details Each thread is responsible for computing a range of scanlines.
 * Iterates through assigned rows and columns, maps each pixel to complex
 * coordinates, and dispatches to the appropriate fractal rendering function
 * based on the current fractal type. This function runs in parallel across
 * NUM_THREADS worker threads.
 *
 * @ingroup fractal_render
 *
 * @param[in] arg Pointer to t_thread_data structure containing thread parameters
 *
 * @return void* Always returns NULL (required by pthread interface)
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
				|| data->type == EYE_MANDELBROT
				|| data->type == DRAGON_MANDELBROT)
				calculate_c(data, screen_pos);
		}
	}
	return (NULL);
}

/**
 * @brief Orchestrates multi-threaded fractal rendering across all worker threads
 *
 * @details Divides the screen into horizontal strips and spawns NUM_THREADS
 * worker threads to compute each section in parallel. Distributes remaining
 * rows evenly if screen height is not perfectly divisible. Blocks until all
 * threads complete their work before returning. Called whenever the view changes
 * due to zoom or parameter adjustments.
 *
 * @ingroup fractal_render
 *
 * @param[in,out] data Pointer to application state with all rendering parameters
 */
void	redraw_fractal(t_data *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				remaining_rows;
	int				i;

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
}
