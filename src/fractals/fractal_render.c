/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:07:56 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:30:14 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FRACTAL RENDER - Main fractal rendering coordination
**
** This file contains the core rendering engine that coordinates the
** transformation from screen coordinates to complex plane coordinates
** and dispatches to appropriate fractal calculation functions. Handles
** the mapping between pixel positions and mathematical coordinates.
*/

#include "fract_ol.h"

/*
** calculate_c_off - Calculate complex coordinates for Mandelbrot rendering
** @data: Application data with viewing bounds and parameters
** @screen_pos: Current pixel position being calculated
**
** Transforms screen coordinates to complex plane coordinates for standard
** Mandelbrot set rendering. Maps pixel positions to complex c values that
** will be used in the Mandelbrot iteration formula z = z² + c. Applies
** current zoom level and viewing bounds to determine the complex coordinate.
*/
static void	calculate_c_off(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;		/* Complex coordinate for this pixel */

	/* Map X coordinate to real part of complex number */
	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	c.real -= 0.5;
	/* Map Y coordinate to imaginary part of complex number */
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;	/* Aspect ratio correction */
	draw_mandelbrot(data, c, screen_pos);			/* Calculate and render pixel */
}

/*
** calculate_z - Calculate complex coordinates for Julia set rendering
** @data: Application data with viewing bounds and parameters
** @screen_pos: Current pixel position being calculated
**
** Transforms screen coordinates to complex plane coordinates for Julia set
** rendering. Maps pixel positions to complex z values that will be used as
** initial values in the Julia iteration formula z = z² + c, where c is
** fixed. Each pixel represents a different starting point in the complex plane.
*/
static void	calculate_z(t_data *data, t_vector2 screen_pos)
{
	t_complex	z;		/* Initial z value for this pixel */

	/* Map X coordinate to real part of initial z */
	z.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	z.real *= data -> max.real - data -> min.real;
	/* Map Y coordinate to imaginary part of initial z */
	z.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	z.imag *= data -> max.imag - data -> min.imag;
	z.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;	/* Aspect ratio correction */
	draw_julia(data, z, screen_pos);		/* Calculate and render pixel */
}

/*
** calculate_c - Calculate complex coordinates for Mandelbrot variations
** @data: Application data with viewing bounds and fractal type
** @screen_pos: Current pixel position being calculated
**
** Transforms screen coordinates to complex plane coordinates for Mandelbrot
** variations (sinh and eye types). Maps pixel positions to complex c values
** for use in modified Mandelbrot formulas. Dispatches to appropriate
** variation-specific rendering function based on fractal type.
*/
static void	calculate_c(t_data *data, t_vector2 screen_pos)
{
	t_complex	c;		/* Complex coordinate for this pixel */

	/* Map X coordinate to real part of complex number */
	c.real = (double)screen_pos.x / SCREEN_WIDTH - 0.5;
	c.real *= data -> max.real - data -> min.real;
	/* Map Y coordinate to imaginary part of complex number */
	c.imag = (double)screen_pos.y / SCREEN_HEIGHT - 0.5;
	c.imag *= data -> max.imag - data -> min.imag;
	c.imag *= (double)SCREEN_HEIGHT / SCREEN_WIDTH;	/* Aspect ratio correction */
	
	/* Dispatch to appropriate Mandelbrot variation */
	if (data -> type == SINH_MANDELBROT)
		draw_sinh_mandelbrot(data, c, screen_pos);
	else if (data -> type == EYE_MANDELBROT)
		draw_eye_mandelbrot(data, c, screen_pos);
}

/*
** render_fractal_threaded - Thread worker function for parallel computation
** @arg: Pointer to t_thread_data containing thread-specific parameters
**
** Worker function executed by each thread to render its assigned portion
** of the fractal image. Each thread processes a specific range of rows
** (start_y to end_y) to distribute the computational workload across
** multiple CPU cores. This significantly improves performance for
** fractal calculations which are highly parallelizable operations.
*/
void	*render_fractal_threaded(void *arg)
{
	t_thread_data	*thread_data;	/* Thread-specific data */
	t_data			*data;		/* Main application data */
	t_vector2		screen_pos;	/* Current pixel position */

	thread_data = (t_thread_data *)arg;	/* Cast argument to thread data */
	data = thread_data->data;		/* Extract main data reference */
	
	/* Initialize screen position for this thread's assigned rows */
	screen_pos.y = thread_data->start_y - 1;	/* Start before first row */
	screen_pos.x = -1;
	
	/* Process all rows assigned to this thread */
	while (++screen_pos.y < thread_data->end_y)
	{
		screen_pos.x = -1;		/* Reset X for each new row */
		/* Process all pixels in current row */
		while (++screen_pos.x < SCREEN_WIDTH)
		{
			/* Dispatch to appropriate fractal calculation based on type */
			if (data->type == MANDELBROT)
				calculate_c_off(data, screen_pos);
			else if (data->type == JULIA)
				calculate_z(data, screen_pos);
			else if (data->type == SINH_MANDELBROT
				|| data->type == EYE_MANDELBROT)
				calculate_c(data, screen_pos);
		}
	}
	return (NULL);				/* Thread completion */
}

/*
** redraw_fractal - Render complete fractal image using multithreading
** @data: Application data with fractal parameters and graphics context
**
** Main rendering function that generates the complete fractal image using
** multiple threads for performance optimization. Divides the screen into
** horizontal strips and assigns each thread a portion of rows to process.
** This parallel approach significantly reduces rendering time on multi-core
** systems while maintaining visual quality and accuracy.
*/
void	redraw_fractal(t_data *data)
{
	pthread_t		threads[NUM_THREADS];	/* Thread handles array */
	t_thread_data	thread_data[NUM_THREADS]; /* Thread data array */
	int				rows_per_thread;	/* Rows assigned per thread */
	int				remaining_rows;		/* Extra rows for distribution */
	int				i;			/* Thread index counter */

	mlx_clear_window(data->mlx, data->win);	/* Clear previous image */
	
	/* Calculate optimal row distribution across threads */
	rows_per_thread = SCREEN_HEIGHT / NUM_THREADS;
	remaining_rows = SCREEN_HEIGHT % NUM_THREADS;
	
	/* Create and launch worker threads */
	i = -1;
	while (++i < NUM_THREADS)
	{
		/* Initialize thread-specific data */
		thread_data[i].data = data;		/* Reference to main data */
		thread_data[i].thread_id = i;		/* Unique thread identifier */
		thread_data[i].start_y = i * rows_per_thread; /* Starting row */
		thread_data[i].end_y = (i + 1) * rows_per_thread; /* Ending row */
		
		/* Distribute remaining rows to first threads */
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
		
		/* Launch worker thread */
		pthread_create(&threads[i], NULL, render_fractal_threaded,
			&thread_data[i]);
	}
	
	/* Wait for all threads to complete */
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	
	/* Display the completed fractal image */
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
