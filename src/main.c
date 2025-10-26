/**
 * @file main.c
 * @author Lilith Estévez Boeta
 * @brief Main entry point of the Fract-ol application with window initialization and argument validation.
 */

#include "fract_ol.h"

/**
 * @brief Initializes the initial Z or C values based on the fractal type.
 * 
 * @param data Pointer to the main data structure containing fractal parameters.
 * @param argv Command line arguments containing the fractal type specification.
 */
static void	initial_variables(t_data *data, char **argv)
{
	if (str_compare_all(argv[1], "mandelbrot"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 0;
	}
	else if (str_compare_all(argv[1], "sinh"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 1;
	}
	else if (str_compare_all(argv[1], "eye"))
	{
		data -> initial_z.real = 0;
		data -> initial_z.imag = 0;
	}
	else if (str_compare_all(argv[1], "dragon"))
	{
		data -> initial_z.real = 1;
		data -> initial_z.imag = 0.1;
	}
	else if (str_compare_all(argv[1], "julia"))
	{
		data -> initial_c.real = str_to_float(argv[2]);
		data -> initial_c.imag = str_to_float(argv[3]);
	}
}

/**
 * @brief Sets up the initial conditions for the fractal rendering.
 * @details Initializes zoom, color offset, coordinate bounds, and fractal type.
 * 
 * @param data Pointer to the main data structure to be initialized.
 * @param argv Command line arguments containing the fractal type specification.
 */
static void	initial_conditions(t_data *data, char **argv)
{
	data -> color_off = 0.0;
	data -> max.real = 0.5;
	data -> max.imag = 1;
	data -> min.real = -1;
	data -> min.imag = -0.5;
	data -> zoom_factor = 1.0;
	initial_variables(data, argv);
	if (str_compare_all(argv[1], "mandelbrot"))
		data -> type = MANDELBROT;
	else if (str_compare_all(argv[1], "sinh"))
		data -> type = SINH_MANDELBROT;
	else if (str_compare_all(argv[1], "eye"))
		data -> type = EYE_MANDELBROT;
	else if (str_compare_all(argv[1], "julia"))
		data -> type = JULIA;
	else if (str_compare_all(argv[1], "dragon"))
		data -> type = DRAGON_MANDELBROT;
}

/**
 * @brief Initializes the MLX window and sets up event handlers.
 * @details Creates the rendering window, image buffer, and registers input handlers.
 * 
 * @param vars Pointer to the main data structure containing window parameters.
 */
void	init_window(t_data *vars)
{
	pthread_mutex_init(&vars->img_mutex, NULL);

	vars -> mlx = mlx_init();
	vars -> win = mlx_new_window(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol");
	vars -> img = mlx_new_image(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	vars -> addr = mlx_get_data_addr(vars -> img, &(vars -> bits_per_pixel),
			&(vars -> line_length), &(vars -> endian));
	mlx_key_hook(vars -> win, key_handler, vars);
	mlx_mouse_hook(vars -> win, zoom, vars);
	mlx_hook(vars -> win, 17, 0, close_window, vars);
	redraw_fractal(vars);
	mlx_loop(vars -> mlx);
}

/**
 * @brief Main entry point of the fractal renderer application.
 * @details Validates command line arguments and initializes the fractal rendering window.
 * 
 * @param argc The number of command line arguments.
 * @param argv Array of command line arguments (fractal type and optional parameters).
 * 
 * @return int Exit status code.
 */
int	main(int argc, char **argv)
{
	t_data	vars;

	if (argc < 2 || argc > 4)
	{
		print_format("\033[0;91mPlease introduce a valid parameter\n");
		print_format("\033[0;39mValid parameters:\n");
		print_format("\033[0;92m\tmandelbrot\n");
		print_format("\033[0;95m\tjulia \033[0;93mx y\n");
		print_format("\033[0;96m\teye\n");
		print_format("\033[0;94m\tsinh\n");
		exit(0);
	}
	if ((is_julia(argv[1]) && argc != 4) ||
		(is_mandelbrot(argv[1]) && argc != 2))
	{
		print_format("\033[0;91mPlease introduce a valid parameter\n");
		print_format("\033[0;39mValid parameters:\n");
		print_format("\033[0;92m\tmandelbrot\n");
		print_format("\033[0;95m\tjulia \033[0;93mx y\n");
		print_format("\033[0;96m\teye\n");
		print_format("\033[0;94m\tsinh\n");
		exit(0);
	}
	initial_conditions(&vars, argv);
	init_window(&vars);
}
