/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:22:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:20 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FRACT_OL - Main Application Entry Point
**
** This file contains the main application logic for the fractal explorer.
** Handles initialization, command line argument parsing, and MLX window setup.
** The program supports multiple fractal types with interactive exploration
** capabilities including zoom, navigation, and real-time parameter adjustment.
*/

#include "fract_ol.h"

/*
** initial_variables - Set fractal-specific initial parameters
** @data: Application data structure to initialize
** @argv: Command line arguments array
**
** Configures initial mathematical parameters for different fractal types.
** Each fractal type requires specific starting values for proper rendering:
** - Mandelbrot variants: z starts at origin (0,0)
** - Julia sets: c parameter from command line arguments
** - Sinh variant: modified initial z for hyperbolic effects
*/
static void	initial_variables(t_data *data, char **argv)
{
	if (ft_strcmp(argv[1], "mandelbrot"))		/* Classic Mandelbrot set */
	{
		data -> initial_z.real = 0;		/* Z starts at origin */
		data -> initial_z.imag = 0;
	}
	else if (ft_strcmp(argv[1], "sinh"))		/* Sinh Mandelbrot variation */
	{
		data -> initial_z.real = 0;		/* Modified initial conditions */
		data -> initial_z.imag = 1;		/* For hyperbolic transformation */
	}
	else if (ft_strcmp(argv[1], "eye"))		/* Eye Mandelbrot variation */
	{
		data -> initial_z.real = 0;		/* Standard Mandelbrot start */
		data -> initial_z.imag = 0;
	}
	else if (ft_strcmp(argv[1], "julia"))		/* Julia set */
	{
		/* Parse c parameter from command line arguments */
		data -> initial_c.real = atod(argv[2]);	/* Real part of c */
		data -> initial_c.imag = atod(argv[3]);	/* Imaginary part of c */
	}
}

/*
** initial_conditions - Initialize application state and fractal parameters
** @data: Application data structure to configure
** @argv: Command line arguments for fractal type selection
**
** Sets up the initial viewing area in the complex plane and configures
** fractal-specific parameters. Establishes the default zoom level covering
** the standard fractal viewing area from -2 to +2 in both axes. Determines
** fractal type based on command line arguments and calls appropriate
** parameter initialization.
*/
static void	initial_conditions(t_data *data, char **argv)
{
	data -> color_off = 0.0;			/* Initialize color animation phase */
	data -> max.real = 2;				/* Right boundary of complex plane view */
	data -> max.imag = 2;				/* Top boundary of complex plane view */
	data -> min.real = -2;				/* Left boundary of complex plane view */
	data -> min.imag = -2;				/* Bottom boundary of complex plane view */
	initial_variables(data, argv);			/* Set fractal-specific parameters */
	
	/* Determine fractal type from command line argument */
	if (ft_strcmp(argv[1], "mandelbrot"))
		data -> type = MANDELBROT;
	else if (ft_strcmp(argv[1], "sinh"))
		data -> type = SINH_MANDELBROT;
	else if (ft_strcmp(argv[1], "eye"))
		data -> type = EYE_MANDELBROT;
	else if (ft_strcmp(argv[1], "julia"))
		data -> type = JULIA;
}

/*
** init_window - Initialize MLX graphics system and event handlers
** @vars: Application data structure with window configuration
**
** Sets up the complete MLX graphics environment for fractal rendering.
** Creates window, image buffer, and configures event handlers for
** interactive exploration. Establishes the rendering pipeline and
** starts the main event loop for user interaction.
*/
void	init_window(t_data *vars)
{
	vars -> mlx = mlx_init();			/* Initialize MLX library */
	/* Create application window with specified dimensions */
	vars -> win = mlx_new_window(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Fractol");
	/* Create image buffer for pixel manipulation */
	vars -> img = mlx_new_image(vars -> mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	/* Get direct access to image buffer memory */
	vars -> addr = mlx_get_data_addr(vars -> img, &(vars -> bits_per_pixel),
			&(vars -> line_length), &(vars -> endian));
	
	/* Register event handlers for user interaction */
	mlx_key_hook(vars -> win, key_handler, vars);	/* Keyboard events */
	mlx_mouse_hook(vars -> win, zoom, vars);	/* Mouse click events */
	mlx_hook(vars -> win, 17, 0, close, vars);	/* Window close event */
	
	redraw_fractal(vars);				/* Initial fractal rendering */
	mlx_loop(vars -> mlx);				/* Start event loop */
}

/*
** main - Application entry point and argument validation
** @argc: Number of command line arguments
** @argv: Array of command line argument strings
**
** Main application entry point that validates command line arguments
** and initializes the fractal explorer. Supports multiple fractal types
** with different argument requirements:
** - Mandelbrot variants: require only fractal type name
** - Julia sets: require fractal type and two numeric parameters (c real, c imag)
** Provides helpful usage information for invalid argument combinations.
*/
int	main(int argc, char **argv)
{
	t_data	vars;				/* Main application data structure */

	/* Validate command line arguments based on fractal type */
	if ((argc != 2 && is_mandelbrot(argv[1]))	/* Mandelbrot variants need 1 arg */
		|| (argc != 4 && is_julia(argv[1])))	/* Julia sets need 3 args */
	{
		/* Display usage information with color-coded examples */
		ft_printf("\033[0;91mPlease introduce a valid parameter\n");
		ft_printf("\033[0;39mValid parameters:\n");
		ft_printf("\033[0;92m\tmandelbrot\n");		/* Green: Mandelbrot */
		ft_printf("\033[0;95m\tjulia \033[0;93mx y\n");	/* Magenta/Yellow: Julia with params */
		ft_printf("\033[0;96m\teye\n");			/* Cyan: Eye variant */
		ft_printf("\033[0;94m\tsinh\n");		/* Blue: Sinh variant */
		exit(0);
	}
	initial_conditions(&vars, argv);		/* Initialize fractal parameters */
	init_window(&vars);				/* Start graphics system and main loop */
}
