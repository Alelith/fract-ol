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
 * @brief Initializes the SDL2 window and rendering components.
 * @details Creates window, renderer, texture, and sets up the main render loop.
 * 
 * @param vars Pointer to the main data structure containing window parameters.
 */
void	init_window(t_data *vars)
{
	pthread_mutex_init(&vars->pixels_mutex, NULL);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		print_format("\033[0;91mSDL2 initialization failed: %s\n", SDL_GetError());
		exit(1);
	}

	vars->window = SDL_CreateWindow(
		"Fractol",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!vars->window)
	{
		print_format("\033[0;91mWindow creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	vars->renderer = SDL_CreateRenderer(
		vars->window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!vars->renderer)
	{
		print_format("\033[0;91mRenderer creation failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(vars->window);
		SDL_Quit();
		exit(1);
	}

	vars->texture = SDL_CreateTexture(
		vars->renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);

	if (!vars->texture)
	{
		print_format("\033[0;91mTexture creation failed: %s\n", SDL_GetError());
		SDL_DestroyRenderer(vars->renderer);
		SDL_DestroyWindow(vars->window);
		SDL_Quit();
		exit(1);
	}

	vars->pixels = (Uint32 *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	if (!vars->pixels)
	{
		print_format("\033[0;91mPixel buffer allocation failed\n");
		SDL_DestroyTexture(vars->texture);
		SDL_DestroyRenderer(vars->renderer);
		SDL_DestroyWindow(vars->window);
		SDL_Quit();
		exit(1);
	}

	vars->pitch = SCREEN_WIDTH * sizeof(Uint32);
	vars->running = 1;

	redraw_fractal(vars);
}

/**
 * @brief Main event loop for SDL2.
 * @details Handles events and calls redraw when needed.
 * 
 * @param vars Pointer to the main data structure.
 */
void	sdl_loop(t_data *vars)
{
	SDL_Event	event;
	int			mouse_x;
	int			mouse_y;

	while (vars->running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				vars->running = 0;
			else if (event.type == SDL_KEYDOWN)
				key_handler(event.key.keysym.sym, vars);
			else if (event.type == SDL_MOUSEWHEEL)
			{
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
				{
					if (event.wheel.y > 0)
						zoom(SDL_BUTTON_LEFT, mouse_x, mouse_y, vars);
					else if (event.wheel.y < 0)
						zoom(SDL_BUTTON_RIGHT, mouse_x, mouse_y, vars);
				}
				else
				{
					if (event.wheel.y > 0)
						zoom(SDL_BUTTON_RIGHT, mouse_x, mouse_y, vars);
					else if (event.wheel.y < 0)
						zoom(SDL_BUTTON_LEFT, mouse_x, mouse_y, vars);
				}
			}
		}

		SDL_UpdateTexture(vars->texture, NULL, vars->pixels, vars->pitch);
		SDL_RenderClear(vars->renderer);
		SDL_RenderCopy(vars->renderer, vars->texture, NULL, NULL);
		SDL_RenderPresent(vars->renderer);
	}
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
	sdl_loop(&vars);
}
