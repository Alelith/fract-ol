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
 * Fract-ol provides an interactive environment to explore multiple different fractal types:
 * - The classic Mandelbrot set
 * - The Julia set with customizable parameters
 * - The Eye Mandelbrot (a variation with z³ iteration)
 * - The Sinh Mandelbrot (using hyperbolic sine operations)
 * - The Dragon Mandelbrot (another z³ variant)
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
 * ./fractol dragon
 * @endcode
 * 
 * **Controls:**
 * - Mouse Wheel Up: Zoom in at cursor position
 * - Mouse Wheel Down: Zoom out at cursor position
 * - ESC: Close the application
 * 
 * @section architecture_sec Architecture
 * 
 * The project is organized into the following modules (each with its own dedicated group):
 * 
 * - @ref complex_ops - Complex number arithmetic and mathematical operations
 * - @ref fractal_rendering - Fractal computation and multi-threaded rendering engine
 * - @ref graphics_module - Graphics, colors, and event handling
 * - @ref data_structures - Core data structures and constants
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
 * - **SDL2 (Simple DirectMedia Layer)**: Graphics library for window creation, rendering, and event handling
 * - **Survival Library**: Custom utility functions for string comparison, memory operations, and file handling
 * - **POSIX Threads (pthread)**: For multi-threaded rendering with mutex synchronization
 * - **Standard C Math Library (libm)**: For mathematical operations (sqrt, sin, cos, sinh, cosh, log2)
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

# include "survival_lib.h"
# include <SDL2/SDL.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

/**
 * @defgroup data_structures Core Data Structures and Constants
 * @brief Main structures and configuration constants for the Fract-ol renderer.
 * @details
 * This group contains all core data structures used throughout the application,
 * including the main application data structure, thread configuration, and constants
 * for window dimensions, rendering parameters, and mathematical definitions.
 */

/** @ingroup data_structures
 * @brief Default window width in pixels */
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 960
# endif
/** @ingroup data_structures
 * @brief Default window height in pixels */
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 540
# endif

/** @ingroup data_structures
 * @brief Maximum iteration count for fractal computation */
# ifndef ITER
#  define ITER 20
# endif

/** @ingroup data_structures
 * @brief Mathematical constant PI */
# ifndef PI
#  define PI 3.14159265358979323846
# endif

/** @ingroup data_structures
 * @brief Number of worker threads for parallel rendering */
# ifndef NUM_THREADS
#  define NUM_THREADS 8
# endif

/**
 * @ingroup data_structures
 * @brief Enumeration of supported fractal types.
 * 
 * This enum defines the five types of fractals that can be rendered by Fract-ol.
 * Each fractal type has a unique mathematical formula for iteration.
 */
typedef enum e_fractals
{
	MANDELBROT = 0,			/**< Classic Mandelbrot set: z = z² + c */
	JULIA = 1,				/**< Julia set: z_{n+1} = z_n² + c with fixed parameter */
	SINH_MANDELBROT = 2,	/**< Sinh Mandelbrot: z = sinh(z/c) */
	EYE_MANDELBROT = 3,		/**< Eye Mandelbrot: z = z³ * (1/c) */
	DRAGON_MANDELBROT = 4	/**< Dragon Mandelbrot: z = z³ * (1/c) */
}	t_fractals; ///< Typedef for enum e_fractals

/**
 * @ingroup data_structures
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
}	t_vector2; ///< Typedef for struct s_vector2

/**
 * @ingroup data_structures
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
}	t_complex; ///< Typedef for struct s_complex

/**
 * @ingroup data_structures
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
}	t_data; ///< Typedef for struct s_data

/**
 * @ingroup data_structures
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
}	t_thread_data; ///< Typedef for struct s_thread_data

/**
 * @defgroup graphics_module Graphics, Colors, and Event Handling
 * @brief Graphics rendering, color generation, and user input handling.
 * @details
 * This module manages all graphical output and user interaction:
 * - SDL2-based window and renderer management
 * - Pixel buffer operations with thread-safe access
 * - Color generation algorithms (HSV and psychedelic color schemes)
 * - Keyboard and mouse event handling for zoom and navigation
 * - Texture and display updates for smooth rendering
 */

void		my_mlx_pixel_put(t_data *data, t_vector2 pos, int color);
int			get_color_hsv(int iter, int max_iter);
int			psychedelic_color(int iter, double phase, int iterations);
int			key_handler(SDL_Keycode keycode, t_data *vars);
int			zoom(Uint8 mousecode, int x, int y, t_data *img);
int			is_mandelbrot(char *type);
int			is_julia(char *type);
int			close_window(t_data *vars);

/**
 * @defgroup complex_ops Complex Number Operations
 * @brief Complex number arithmetic and mathematical functions.
 * @details
 * This module implements complete complex number arithmetic including addition,
 * multiplication, division, and inversion. It also provides specialized functions
 * like modulus calculation and hyperbolic sine for complex arguments.
 * Used extensively in fractal iteration calculations.
 */

double		complx_module(t_complex num);
t_complex	inv_complx(t_complex a);
t_complex	sinh_complx(t_complex num);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	div_complx(t_complex a, t_complex b);
t_complex	multiply_complx(t_complex a, t_complex b);

/**
 * @defgroup fractal_rendering Fractal Rendering Engine
 * @brief Fractal computation and multi-threaded rendering.
 * @details
 * This module handles the core fractal calculations including:
 * - Mandelbrot set computation (z = z² + c)
 * - Julia set computation (z_{n+1} = z_n² + c)
 * - Eye Mandelbrot variant (z = z³ * (1/c))
 * - Sinh Mandelbrot variant (z = sinh(z/c))
 * - Dragon Mandelbrot variant
 * 
 * Features multi-threaded rendering using worker threads for parallel computation
 * and real-time responsive interaction.
 */

int			calculate_iterations(t_data *data, int max_iter);
void		redraw_fractal(t_data *data);
void		*render_fractal_threaded(void *arg);
void		draw_julia(t_data *img, t_complex z, t_vector2 pos);
void		draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_dragon_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

#endif
