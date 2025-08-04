/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:30:39 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FRACT_OL - Fractal Explorer Header File
**
** This header file contains all the type definitions, constants, and function
** prototypes for the fractal exploration program. The program renders various
** types of mathematical fractals including Mandelbrot, Julia, and custom
** variations using the MLX graphics library.
**
** Features:
** - Multiple fractal types (Mandelbrot, Julia, Sinh Mandelbrot, Eye Mandelbrot)
** - Interactive zoom and navigation
** - Complex number arithmetic operations
** - Advanced color mapping algorithms
** - Real-time parameter adjustment
*/

#ifndef FRACT_OL_H
# define FRACT_OL_H

/* Screen dimension constants */
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 960		/* Default window width in pixels */
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 540		/* Default window height in pixels */
# endif

/* Fractal calculation constants */
# ifndef ITER
#  define ITER 60			/* Maximum iterations for fractal calculation */
# endif

/* Mathematical constants */
# ifndef PI
#  define PI 3.14159265358979323846	/* Pi constant for trigonometric operations */
# endif

/* Threading constants for performance optimization */
# ifndef NUM_THREADS
#  define NUM_THREADS 8			/* Number of threads for parallel computation */
# endif

# include "ft_printf.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>

/*
** t_fractals - Enumeration of supported fractal types
**
** Defines the different fractal algorithms available in the program.
** Each type corresponds to a specific mathematical formula and rendering method.
*/
typedef enum e_fractals
{
	MANDELBROT = 0,			/* Classic Mandelbrot set: z = z² + c */
	JULIA = 1,			/* Julia set with fixed parameter c */
	SINH_MANDELBROT = 2,		/* Hyperbolic sine variation of Mandelbrot */
	EYE_MANDELBROT = 3		/* Custom eye-shaped Mandelbrot variation */
}	t_fractals;

/*
** t_vector2 - 2D integer coordinate structure
**
** Represents a point or coordinate in 2D space using integer values.
** Used primarily for pixel positions and screen coordinates in the
** fractal rendering process.
*/
typedef struct s_vector2
{
	int	x;				/* X coordinate (horizontal position) */
	int	y;				/* Y coordinate (vertical position) */
}	t_vector2;

/*
** t_complex - Complex number structure
**
** Represents a complex number with real and imaginary components.
** Essential for fractal mathematics as fractals are defined in the
** complex plane. All fractal calculations use complex arithmetic.
*/
typedef struct s_complex
{
	double	real;			/* Real component of the complex number */
	double	imag;			/* Imaginary component of the complex number */
}	t_complex;

/*
** t_data - Main application data structure
**
** Contains all the necessary data for the fractal rendering application.
** Includes MLX graphics context, fractal parameters, and viewing boundaries.
** This structure is passed to most functions to maintain application state.
*/
typedef struct s_data
{
	void		*mlx;		/* MLX library instance pointer */
	void		*win;		/* MLX window pointer */
	void		*img;		/* MLX image buffer pointer */
	char		*addr;		/* Image buffer memory address */
	int			bits_per_pixel;	/* Color depth information */
	int			line_length;	/* Image line length in bytes */
	int			endian;		/* Byte order information */
	double		color_off;	/* Color phase offset for dynamic coloring */
	t_complex	max;		/* Maximum complex plane coordinates (top-right) */
	t_complex	min;		/* Minimum complex plane coordinates (bottom-left) */
	t_complex	initial_z;	/* Initial Z value for Julia sets */
	t_complex	initial_c;	/* Initial C parameter for Julia sets */
	t_fractals	type;		/* Current fractal type being rendered */
}	t_data;

/*
** t_thread_data - Thread-specific data for parallel fractal computation
**
** Contains the data needed for each worker thread to compute its assigned
** portion of the fractal image. Each thread processes a specific range of
** screen rows to enable parallel computation and performance optimization.
*/
typedef struct s_thread_data
{
	t_data		*data;		/* Pointer to main application data */
	int			start_y;	/* Starting Y coordinate (row) for this thread */
	int			end_y;		/* Ending Y coordinate (row) for this thread */
	int			thread_id;	/* Unique identifier for this thread */
}	t_thread_data;

/* ===== UTILITY FUNCTIONS ===== */

/*
** atod - Convert string to double precision floating point
** @nptr: String to convert
**
** Converts a string representation of a number to double precision.
** Used for parsing command line arguments and user input.
*/
double		atod(const char *nptr);

/*
** my_mlx_pixel_put - Set pixel color in image buffer
** @data: Application data containing image buffer
** @pos: Pixel coordinates to set
** @color: Color value to set
**
** Directly writes a pixel color to the image buffer at specified coordinates.
** More efficient than MLX's pixel_put for intensive rendering operations.
*/
void		my_mlx_pixel_put(t_data *data, t_vector2 pos, int color);

/* ===== COLOR FUNCTIONS ===== */

/*
** get_color_hsv - Generate HSV-based color from iteration count
** @iter: Iteration count from fractal calculation
**
** Creates smooth color gradients using HSV color space based on the
** number of iterations required for fractal escape. Provides natural
** color transitions in fractal visualizations.
*/
int			get_color_hsv(int iter);

/*
** psychedelic_color - Generate dynamic psychedelic colors
** @iter: Iteration count from fractal calculation
** @phase: Color phase offset for animation
**
** Creates vibrant, animated color schemes with phase shifting for
** dynamic fractal visualizations. Produces psychedelic color effects.
*/
int			psychedelic_color(int iter, double phase);

/* ===== COMPLEX NUMBER OPERATIONS ===== */

/*
** complx_module - Calculate modulus (magnitude) of complex number
** @num: Complex number to calculate modulus for
**
** Returns the distance from origin in the complex plane.
** Essential for fractal escape condition testing.
*/
double		complx_module(t_complex num);

/*
** inv_complx - Calculate multiplicative inverse of complex number
** @a: Complex number to invert
**
** Returns 1/a for complex number a. Used in advanced fractal variations
** that require complex division operations.
*/
t_complex	inv_complx(t_complex a);

/*
** sinh_complx - Calculate hyperbolic sine of complex number
** @num: Complex number input
**
** Computes sinh(z) for complex z. Used in hyperbolic fractal variations
** that apply trigonometric transformations to the standard formulas.
*/
t_complex	sinh_complx(t_complex num);

/*
** sum_complx - Add two complex numbers
** @a: First complex number
** @b: Second complex number
**
** Returns a + b for complex numbers. Fundamental operation for
** fractal iteration formulas.
*/
t_complex	sum_complx(t_complex a, t_complex b);

/*
** div_complx - Divide two complex numbers
** @a: Dividend complex number
** @b: Divisor complex number
**
** Returns a / b for complex numbers. Used in fractal variations
** that require complex division.
*/
t_complex	div_complx(t_complex a, t_complex b);

/*
** multiply_complx - Multiply two complex numbers
** @a: First complex number
** @b: Second complex number
**
** Returns a * b for complex numbers. Core operation for fractal
** iteration formulas like z² in Mandelbrot set.
*/
t_complex	multiply_complx(t_complex a, t_complex b);

/* ===== FRACTAL RENDERING FUNCTIONS ===== */

/*
** redraw_fractal - Regenerate entire fractal image
** @data: Application data with fractal parameters
**
** Renders the complete fractal based on current parameters and view bounds.
** Called when parameters change or window needs refreshing.
*/
void		redraw_fractal(t_data *data);

/*
** render_fractal_threaded - Thread worker function for parallel rendering
** @arg: Thread data containing rendering parameters and bounds
**
** Worker function executed by each thread to render a specific portion
** of the fractal image. Processes assigned rows in parallel to optimize
** performance on multi-core systems. Returns NULL when complete.
*/
void		*render_fractal_threaded(void *arg);

/*
** draw_julia - Render Julia set at specific pixel
** @img: Application data with rendering context
** @z: Initial z value for Julia iteration
** @pos: Pixel position to render
**
** Calculates and renders one pixel of the Julia set fractal.
** Uses the iteration formula z = z² + c with fixed c parameter.
*/
void		draw_julia(t_data *img, t_complex z, t_vector2 pos);

/*
** draw_mandelbrot - Render Mandelbrot set at specific pixel
** @img: Application data with rendering context
** @c: C parameter for Mandelbrot iteration
** @pos: Pixel position to render
**
** Calculates and renders one pixel of the Mandelbrot set fractal.
** Uses the iteration formula z = z² + c with z starting at origin.
*/
void		draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

/*
** draw_eye_mandelbrot - Render eye variation Mandelbrot at specific pixel
** @img: Application data with rendering context
** @c: C parameter for iteration
** @pos: Pixel position to render
**
** Renders a custom "eye-shaped" variation of the Mandelbrot set with
** modified iteration formula for unique visual effects.
*/
void		draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

/*
** draw_sinh_mandelbrot - Render hyperbolic sine Mandelbrot at specific pixel
** @img: Application data with rendering context
** @c: C parameter for iteration
** @pos: Pixel position to render
**
** Renders Mandelbrot variation using hyperbolic sine transformation.
** Creates unique fractal patterns through trigonometric modifications.
*/
void		draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

/* ===== EVENT HANDLERS ===== */

/*
** key_handler - Process keyboard input events
** @keycode: Key code from MLX event system
** @vars: Application data for state management
**
** Handles keyboard controls for navigation, zoom, parameter adjustment,
** and application control. Returns 0 for continued execution.
*/
int			key_handler(int keycode, t_data *vars);

/*
** zoom - Process mouse zoom events
** @mousecode: Mouse button code from MLX
** @x: Mouse X coordinate
** @y: Mouse Y coordinate
** @img: Application data for zoom calculations
**
** Implements zoom in/out functionality centered on mouse position.
** Adjusts complex plane viewing bounds for detailed exploration.
*/
int			zoom(int mousecode, int x, int y, t_data *img);

/* ===== UTILITY AND HELPER FUNCTIONS ===== */

/*
** ft_strcmp - Compare two strings
** @a: First string to compare
** @b: Second string to compare
**
** Standard string comparison function for command line argument parsing.
** Returns 0 if strings are equal, non-zero otherwise.
*/
int			ft_strcmp(char *a, char *b);

/*
** is_mandelbrot - Check if string matches Mandelbrot fractal name
** @type: String to check
**
** Validates if the input string corresponds to a Mandelbrot-type fractal.
** Used for command line argument parsing and fractal type selection.
*/
int			is_mandelbrot(char *type);

/*
** is_julia - Check if string matches Julia fractal name
** @type: String to check
**
** Validates if the input string corresponds to a Julia set fractal.
** Used for command line argument parsing and fractal type selection.
*/
int			is_julia(char *type);

/*
** close - Application cleanup and exit handler
** @vars: Application data to clean up
**
** Properly closes MLX resources and exits the application.
** Called on window close events or exit commands.
*/
int			close(t_data *vars);

#endif
