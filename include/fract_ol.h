/**
 * @mainpage Fract-ol Documentation
 *
 * @section intro_sec Introduction
 * Fract-ol is a high-performance interactive fractal renderer written in C.
 * It enables real-time visualization and exploration of mathematical fractals
 * with smooth zoom capabilities, dynamic color schemes, and multi-threaded
 * rendering for optimal performance. The project implements various fractal
 * types including Mandelbrot, Julia, and custom variations.
 *
 * @section features_sec Features
 * - Real-time fractal rendering with multi-threaded computation (8 workers)
 * - Interactive zoom centered on cursor position
 * - Multiple fractal types: Mandelbrot, Julia, Sinh, Eye, and Dragon variants
 * - Dynamic color schemes including HSV mapping and psychedelic effects
 * - Complex number arithmetic with trigonometric operations
 * - SDL2-based graphics rendering with hardware acceleration
 * - Thread-safe pixel buffer management with mutex synchronization
 *
 * @section architecture_sec Architecture
 * The application is organized into specialized modules:
 * - Complex Operations: Arithmetic and trigonometric functions for complex numbers
 * - Fractal Rendering: Multi-threaded computation engine with divergence detection
 * - Utilities: Color mapping, event handling, and pixel buffer management
 * - Each fractal type has its own iteration formula and divergence criteria
 *
 * @ref complex_ops Complex Number Operations
 *
 * @ref fractal_render Fractal Rendering Engine
 *
 * @ref utils Utility Functions
 *
 * @section implementation_sec Implementation
 * The renderer uses a divide-and-conquer approach where the screen is split
 * into horizontal sections, each computed by a separate thread. Complex number
 * operations are performed to iterate fractal formulas until divergence is
 * detected or maximum iterations are reached. Color is assigned based on the
 * iteration count using HSV or psychedelic color mapping algorithms.
 *
 * @section dependencies_sec Dependencies
 * - SDL2 (Simple DirectMedia Layer 2): Graphics rendering and event handling
 * - POSIX Threads (pthread): Multi-threaded parallel computation
 * - Standard C Math Library: Trigonometric and mathematical functions
 * - Survival Library: Custom utility functions for string handling and I/O
 *
 * @section install_sec Installation
 * Requirements: GCC/Clang compiler, SDL2 development libraries, Make
 * Build process:
 * 1. Clone the repository
 * 2. Run 'make' to compile the project
 * 3. Execute './fractol [type] [parameters]'
 * Example: './fractol mandelbrot' or './fractol julia 0.285 0.01'
 *
 * @section usage_sec Usage
 * Command line syntax:
 * - ./fractol mandelbrot (for Mandelbrot set)
 * - ./fractol julia [real] [imag] (for Julia set with custom constant)
 * - ./fractol eye (for Eye Mandelbrot variant)
 * - ./fractol sinh (for Sinh Mandelbrot variant)
 * - ./fractol dragon (for Dragon Mandelbrot variant)
 * Controls: Mouse wheel for zoom in/out, ESC to exit
 *
 * @section links_sec Related Links
 * - GitHub Repository: https://github.com/Alelith/fract-ol
 * - Survival Library documentation: https://alelith.github.io/survival_lib-documentation/
 * 
 * @section contrib_sec Contributing
 * Contributions are welcome. Please ensure code follows the existing style,
 * includes appropriate Doxygen comments, and passes compilation without
 * warnings. Test all fractal types before submitting changes.
 *
 * @section license_sec License
 * This project is licensed under the GNU General Public License v3 (GPL3).
 * See LICENSE file for full terms. Any derivative work must be distributed
 * under the same GPL3 license with source code availability.
 */

/**
 * @file fract_ol.h
 * @brief Main header file for the Fract-ol fractal renderer
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
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
 * @defgroup constants Configuration Constants
 * @brief Compile-time configuration parameters for the fractal renderer
 *
 * @details These macros define the rendering window dimensions, iteration
 * limits, mathematical constants, and threading configuration. They can be
 * modified at compile time to adjust performance and visual quality.
 *
 * @section module_features_sec Features
 * - Configurable screen resolution
 * - Adjustable iteration depth for fractal computation
 * - Multi-threading configuration for parallel rendering
 * - Mathematical constants for trigonometric operations
 *
 * @section module_usage_sec Usage
 * These constants are used throughout the rendering engine. Modifying them
 * requires recompilation. Higher ITER values increase detail but reduce
 * performance. NUM_THREADS should match CPU core count for optimal performance.
 *
 * @{
 */

# ifndef SCREEN_WIDTH
/**
 * @def SCREEN_WIDTH
 * @brief Horizontal resolution of the rendering window in pixels
 *
 * @details Defines the width of the SDL2 window and texture buffer.
 * Default is 960 pixels. Higher values increase detail but reduce performance.
 *
 * @ingroup constants
 */
#  define SCREEN_WIDTH 960
# endif

# ifndef SCREEN_HEIGHT
/**
 * @def SCREEN_HEIGHT
 * @brief Vertical resolution of the rendering window in pixels
 *
 * @details Defines the height of the SDL2 window and texture buffer.
 * Default is 540 pixels. Must maintain aspect ratio with SCREEN_WIDTH.
 *
 * @ingroup constants
 */
#  define SCREEN_HEIGHT 540
# endif

# ifndef ITER
/**
 * @def ITER
 * @brief Base maximum iteration count for fractal divergence detection
 *
 * @details Determines the maximum number of iterations before a point is
 * considered part of the fractal set. Higher values reveal more detail at
 * deeper zoom levels but increase computation time. Dynamically adjusted
 * based on zoom level during rendering.
 *
 * @ingroup constants
 */
#  define ITER 20
# endif

# ifndef PI
/**
 * @def PI
 * @brief Mathematical constant Pi for trigonometric calculations
 *
 * @details High-precision value of π used in complex trigonometric functions,
 * color mapping algorithms, and psychedelic color generation.
 *
 * @ingroup constants
 */
#  define PI 3.14159265358979323846
# endif

# ifndef NUM_THREADS
/**
 * @def NUM_THREADS
 * @brief Number of worker threads for parallel fractal computation
 *
 * @details Defines how many POSIX threads are spawned for parallel rendering.
 * Default is 8. Should be set to match the number of CPU cores for optimal
 * performance. The screen is divided horizontally into NUM_THREADS sections.
 *
 * @ingroup constants
 */
#  define NUM_THREADS 8
# endif

/** @} */

/**
 * @enum e_fractals
 * @brief Enumeration of supported fractal types
 *
 * Defines the different fractal rendering modes available in the application.
 * Each type uses a different iteration formula to generate unique visual
 * patterns and mathematical structures.
 */
typedef enum e_fractals
{
	MANDELBROT = 0,          ///< Classic Mandelbrot set: z = z² + c
	JULIA = 1,               ///< Julia set with fixed c parameter
	SINH_MANDELBROT = 2,     ///< Mandelbrot variant using hyperbolic sine
	EYE_MANDELBROT = 3,      ///< Mandelbrot variant with z³ iteration
	DRAGON_MANDELBROT = 4    ///< Dragon fractal variant with sinh and inverse
}	t_fractals; 	         ///< Typedef of enum e_fractals

/**
 * @struct s_vector2
 * @brief 2D integer vector representing screen coordinates
 *
 * Represents a position on the screen in pixel coordinates. Used for
 * identifying specific pixels in the rendering buffer during fractal
 * computation and color assignment.
 */
typedef struct s_vector2
{
	int	x;         ///< Horizontal screen coordinate (0 to SCREEN_WIDTH-1)
	int	y;         ///< Vertical screen coordinate (0 to SCREEN_HEIGHT-1)
}	t_vector2; 	   ///< Typedef of struct s_vector2

/**
 * @struct s_complex
 * @brief Complex number representation with real and imaginary components
 *
 * Fundamental data structure for all fractal computations. Represents a
 * complex number in Cartesian form (a + bi) where 'real' is the real part
 * and 'imag' is the imaginary coefficient.
 */
typedef struct s_complex
{
	double	real;   ///< Real component of the complex number
	double	imag;   ///< Imaginary component of the complex number
}	t_complex; 		///< Typedef of struct s_complex

/**
 * @struct s_data
 * @brief Main application state containing SDL resources and fractal parameters
 *
 * Central data structure holding all rendering state, SDL2 resources, fractal
 * configuration, and synchronization primitives. Shared across all rendering
 * threads through read-only access to most fields and mutex-protected writes
 * to the pixel buffer.
 */
typedef struct s_data
{
	SDL_Window		*window;        ///< SDL2 window handle
	SDL_Renderer	*renderer;      ///< SDL2 hardware renderer
	SDL_Texture		*texture;       ///< SDL2 texture for pixel buffer
	Uint32			*pixels;        ///< ARGB8888 pixel buffer array
	int				pitch;          ///< Byte stride for texture rows
	double			color_off;      ///< Phase offset for color cycling animation
	double			zoom_factor;    ///< Current zoom level multiplier
	t_complex		max;            ///< Maximum complex plane coordinate (top-right)
	t_complex		min;            ///< Minimum complex plane coordinate (bottom-left)
	t_complex		initial_z;      ///< Starting Z value for Mandelbrot variants
	t_complex		initial_c;      ///< Fixed C parameter for Julia sets
	t_fractals		type;           ///< Current fractal type being rendered
	pthread_mutex_t	pixels_mutex;   ///< Mutex protecting pixel buffer writes
	int				running;        ///< Application running flag (0 = exit)
}	t_data;                         ///< Typedef of struct s_data

/**
 * @struct s_thread_data
 * @brief Thread-specific data for parallel fractal rendering
 *
 * Contains the parameters needed by each worker thread to compute its assigned
 * section of the fractal. Includes a pointer to shared application state and
 * the vertical range of scanlines this thread is responsible for rendering.
 */
typedef struct s_thread_data
{
	t_data		*data;      ///< Pointer to shared application state
	int			start_y;    ///< Starting scanline (inclusive)
	int			end_y;      ///< Ending scanline (exclusive)
	int			thread_id;  ///< Unique thread identifier (0 to NUM_THREADS-1)
}	t_thread_data;          ///< Typedef of struct s_thread_data

/**
 * @defgroup utils Utility Functions
 * @brief Helper functions for rendering, event handling, and string operations
 *
 * @details This module provides essential utility functions including pixel
 * buffer management, color generation algorithms, event handlers for user
 * input, and string validation for command-line argument parsing.
 *
 * @section utils_features Features
 * - Thread-safe pixel writing with mutex synchronization
 * - HSV and psychedelic color mapping algorithms
 * - Interactive zoom with mouse wheel support
 * - Keyboard event handling for application control
 * - String comparison for fractal type validation
 *
 * @section utils_usage Usage
 * These functions are called throughout the rendering pipeline and event loop.
 * Color functions are invoked per-pixel during fractal computation. Event
 * handlers respond to user input and trigger re-rendering when necessary.
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
 * @brief Arithmetic and trigonometric operations on complex numbers
 *
 * @details Implements the mathematical operations required for fractal
 * computation including basic arithmetic (addition, multiplication, division)
 * and advanced functions (hyperbolic sine, complex inversion). All operations
 * work on the s_complex structure representing numbers in Cartesian form.
 *
 * @section complex_features Features
 * - Complex multiplication using (a+bi)(c+di) = (ac-bd) + (ad+bc)i
 * - Complex division with denominator normalization
 * - Complex inversion: 1/(a+bi) = (a-bi)/(a²+b²)
 * - Hyperbolic sine: sinh(a+bi) = sinh(a)cos(b) + icosh(a)sin(b)
 * - Modulus calculation for divergence detection: |z| = √(a²+b²)
 *
 * @section complex_usage Usage
 * These functions are the mathematical foundation for all fractal iterations.
 * Each fractal type applies a specific sequence of these operations to
 * determine if a point diverges from the set. The modulus function is used
 * to check divergence conditions.
 */

double		complx_module(t_complex num);
t_complex	inv_complx(t_complex a);
t_complex	sinh_complx(t_complex num);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	div_complx(t_complex a, t_complex b);
t_complex	multiply_complx(t_complex a, t_complex b);

/**
 * @defgroup fractal_render Fractal Rendering Engine
 * @brief Core rendering engine with multi-threaded fractal computation
 *
 * @details Implements the main rendering pipeline including thread management,
 * coordinate mapping from screen to complex plane, and fractal-specific
 * iteration functions. Each fractal type has its own drawing function with
 * a unique iteration formula and divergence detection logic.
 *
 * @section render_features Features
 * - Multi-threaded parallel rendering with POSIX threads
 * - Dynamic iteration count based on zoom level
 * - Screen-to-complex-plane coordinate transformation
 * - Separate rendering functions for each fractal type
 * - Thread-safe pixel buffer updates with mutex protection
 * - Adaptive divergence limits per fractal variant
 *
 * @section render_usage Usage
 * The redraw_fractal function is called whenever the view changes (zoom, pan).
 * It spawns NUM_THREADS workers, each computing a horizontal strip of the
 * image. Each worker maps screen pixels to complex coordinates and calls the
 * appropriate draw function based on the fractal type.
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
