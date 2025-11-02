/**
 * @mainpage Fract-ol - Interactive Fractal Renderer
 * 
 * Fract-ol is a high-performance interactive fractal renderer written in C,
 * designed to visualize and explore beautiful mathematical fractals in real-time.
 * The application features smooth zooming, dynamic color schemes, and multi-threaded
 * rendering for optimal performance.
 * 
 * @section intro_sec Introduction
 * Fractals are infinitely complex patterns that are self-similar across different scales.
 * Fract-ol provides an interactive environment to explore four different fractal types:
 * - The classic Mandelbrot set
 * - The Julia set with customizable parameters
 * - The Eye Mandelbrot (a variation with z³ iteration)
 * - The Sinh Mandelbrot (using hyperbolic sine operations)
 * 
 * @section features_sec Key Features
 * - **Real-time Rendering**: Multi-threaded fractal computation for responsive interaction
 * - **Interactive Zoom**: Mouse wheel zoom centered at cursor position
 * - **Dynamic Coloring**: Multiple color schemes including HSV mapping and psychedelic effects
 * - **High Performance**: Parallel thread-based rendering for 8 simultaneous workers
 * - **Complex Math**: Supports complex number arithmetic including trigonometric operations
 * 
 * @section usage_sec Usage
 * Launch the application with one of the following commands:
 * 
 * @code
 * ./fractol mandelbrot
 * ./fractol julia <real_part> <imaginary_part>
 * ./fractol eye
 * ./fractol sinh
 * @endcode
 * 
 * **Controls:**
 * - Mouse Wheel Up: Zoom in at cursor position
 * - Mouse Wheel Down: Zoom out at cursor position
 * - ESC: Close the application
 * 
 * @section architecture_sec Architecture
 * 
 * The project is organized into the following modules:
 * 
 * **Complex Number Operations** (src/complex/):
 * - Implements arithmetic operations: multiplication, addition, division, inversion
 * - Provides complex trigonometric functions (hyperbolic sine)
 * - Calculates modulus for divergence detection
 * 
 * **Fractal Rendering** (src/fractals/):
 * - Mandelbrot Set: z = z² + c with c as pixel coordinate
 * - Julia Set: z_{n+1} = z_n² + c with fixed c parameter
 * - Eye Mandelbrot: z = z³ * (1/c) for unique visual effects
 * - Sinh Mandelbrot: z = sinh(z/c) using hyperbolic functions
 * - Rendering engine with multi-threaded pixel computation
 * 
 * **Graphics & Utilities** (src/utils/):
 * - Image buffer management with thread-safe pixel operations
 * - Color generation (HSV-based and psychedelic color schemes)
 * - Event handling (keyboard and mouse input)
 * - String validation for fractal type selection
 * 
 * @section implementation_sec Implementation Details
 * 
 * **Threading Model:**
 * The renderer distributes the screen into horizontal strips, with each thread
 * responsible for computing pixels in its assigned region. A mutex protects
 * concurrent access to the image buffer, ensuring data consistency.
 * 
 * **Coordinate Mapping:**
 * Screen coordinates (pixel space) are mapped to complex plane coordinates based on:
 * - Current zoom factor
 * - Pan position (min/max bounds)
 * - Screen aspect ratio correction
 * 
 * **Iteration Depth:**
 * The maximum iteration count dynamically scales with zoom level using the formula:
 * max_iter = base_iter × log₂(zoom_factor + 1)
 * 
 * This ensures finer detail visualization at higher zoom levels.
 * 
 * **Color Schemes:**
 * - HSV Model: Maps iteration count to hue (0-360°) for smooth color gradients
 * - Psychedelic: Uses sine waves with phase offsets for each RGB channel,
 *   creating animated color effects that cycle through the spectrum
 * 
 * @section dependencies_sec Dependencies
 * - MinilibX (mlx): Graphics library for window creation and rendering
 * - Survival Library: Custom utility functions for string comparison and memory operations
 * - POSIX Threads (pthread): For multi-threaded rendering
 * - Standard C Math Library: For mathematical operations (sqrt, sin, cos, sinh, cosh)
 * 
 * @section author_sec Author
 * This project was developed by:
 * - Lilith Estévez Boeta
 */

/**
 * @file fract_ol.h
 * @author Lilith Estévez Boeta
 * @brief Header for the Fract-ol fractal renderer application with structures, constants, and function prototypes.
 */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 960
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 540
# endif

# ifndef ITER
#  define ITER 20
# endif

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef NUM_THREADS
#  define NUM_THREADS 8
# endif

# include "survival_lib.h"
# include <SDL2/SDL.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

/**
 * @enum e_fractals
 * @brief Enumeration of supported fractal types.
 * 
 * This enum defines the four types of fractals that can be rendered by Fract-ol.
 * Each fractal type has a unique mathematical formula for iteration.
 */
typedef enum e_fractals
{
	MANDELBROT = 0,			/**< Classic Mandelbrot set: z = z² + c */
	JULIA = 1,				/**< Julia set: z_{n+1} = z_n² + c with fixed parameter */
	SINH_MANDELBROT = 2,	/**< Sinh Mandelbrot: z = sinh(z/c) */
	EYE_MANDELBROT = 3,		/**< Eye Mandelbrot: z = z³ * (1/c) */
	DRAGON_MANDELBROT = 4	/**< Dragon Mandelbrot: z = z³ * (1/c) */
}	t_fractals;

/**
 * @struct s_vector2
 * @brief Represents a 2D integer vector or screen coordinate.
 * 
 * Used to store screen coordinates (pixel positions) in the window.
 * All values are integers to represent exact pixel locations.
 */
typedef struct s_vector2
{
	int	x;	/**< X coordinate (column/horizontal position) */
	int	y;	/**< Y coordinate (row/vertical position) */
}	t_vector2;

/**
 * @struct s_complex
 * @brief Represents a complex number in rectangular form.
 * 
 * Used to represent points in the complex plane and perform complex
 * number arithmetic operations for fractal calculations.
 * A complex number is of the form: z = real + i*imag
 */
typedef struct s_complex
{
	double	real;	/**< Real part of the complex number */
	double	imag;	/**< Imaginary part of the complex number */
}	t_complex;

/**
 * @struct s_data
 * @brief Main application data structure containing all rendering and graphics state.
 * 
 * This is the central data structure that holds all information needed for
 * fractal rendering, window management, and event handling. It is passed to
 * most functions throughout the application.
 */
typedef struct s_data
{
	SDL_Window		*window;				/**< SDL2 window pointer */
	SDL_Renderer	*renderer;				/**< SDL2 renderer pointer */
	SDL_Texture		*texture;				/**< SDL2 texture for pixel buffer */
	Uint32			*pixels;				/**< Pixel buffer (32-bit ARGB) */
	int				pitch;					/**< Pitch of the pixel buffer (bytes per row) */
	double			color_off;				/**< Color phase offset for animation effects */
	double			zoom_factor;			/**< Current zoom level (1.0 = no zoom) */
	t_complex		max;					/**< Maximum bounds (top-right) in complex plane */
	t_complex		min;					/**< Minimum bounds (bottom-left) in complex plane */
	t_complex		initial_z;				/**< Initial Z value for Mandelbrot variants */
	t_complex		initial_c;				/**< Initial C parameter for Julia set */
	t_fractals		type;					/**< Current fractal type being rendered */
	pthread_mutex_t	pixels_mutex;			/**< Mutex for thread-safe pixel buffer access */
	int				running;				/**< Flag to control main loop (1 = running, 0 = exit) */
}	t_data;

/**
 * @struct s_thread_data
 * @brief Thread-specific data passed to worker threads for parallel rendering.
 * 
 * Each rendering thread receives its own instance of this structure,
 * which defines the vertical strip of the screen it is responsible for rendering.
 * This allows the screen to be divided among multiple threads for parallel computation.
 */
typedef struct s_thread_data
{
	t_data		*data;		/**< Pointer to the main application data structure */
	int			start_y;	/**< Starting Y coordinate (row) for this thread's work region */
	int			end_y;		/**< Ending Y coordinate (row) for this thread's work region */
	int			thread_id;	/**< Unique identifier for this thread (0 to NUM_THREADS-1) */
}	t_thread_data;

void		my_mlx_pixel_put(t_data *data, t_vector2 pos, int color);
int			get_color_hsv(int iter, int max_iter);
int			psychedelic_color(int iter, double phase, int iterations);

double		complx_module(t_complex num);
t_complex	inv_complx(t_complex a);
t_complex	sinh_complx(t_complex num);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	div_complx(t_complex a, t_complex b);
t_complex	multiply_complx(t_complex a, t_complex b);

int			calculate_iterations(t_data *data, int max_iter);
void		redraw_fractal(t_data *data);
void		*render_fractal_threaded(void *arg);
void		draw_julia(t_data *img, t_complex z, t_vector2 pos);
void		draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_dragon_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

int			key_handler(SDL_Keycode keycode, t_data *vars);
int			zoom(Uint8 mousecode, int x, int y, t_data *img);

int			is_mandelbrot(char *type);
int			is_julia(char *type);

int			close_window(t_data *vars);

#endif
