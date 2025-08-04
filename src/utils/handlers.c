/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:37:58 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:48 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INTERACTIVE HANDLERS - Mouse and keyboard event handling
**
** This file implements interactive fractal exploration through mouse
** scroll wheel zooming and keyboard commands. Users can zoom into
** fractals with mouse wheel, exit with ESC key, and enjoy automatic
** color animation. The handlers provide smooth real-time interaction
** with the fractal rendering system using coordinate scaling.
*/

#include "fract_ol.h"

/*
** close - Clean application shutdown handler
** @vars: Application data containing MLX window and context
**
** Handles clean application shutdown by properly destroying the MLX
** window and exiting the program. This ensures proper cleanup of
** graphics resources and prevents memory leaks. Called when the
** window close button is clicked or ESC key is pressed.
*/
int	close(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);	/* Clean up MLX window */
	exit(0);					/* Exit program */
}

/*
** key_handler - Process keyboard input events
** @keycode: X11 keycode for the pressed key
** @vars: Application data containing fractal parameters
**
** Handles keyboard input for fractal control. Currently supports:
** - ESC key (keycode 65307): Exit the application cleanly
** Additional key commands can be added here for navigation,
** color changes, or fractal type switching. The X11 keycode
** system is used for cross-platform compatibility.
*/
int	key_handler(int keycode, t_data *vars)
{
	if (keycode == 65307)			/* ESC key pressed (X11 keycode) */
		close(vars);			/* Exit application */
	return (0);				/* Continue processing events */
}

/*
** zoom - Handle mouse scroll wheel zoom events
** @mousecode: Mouse event code (4=scroll up, 5=scroll down)
** @x: X coordinate of mouse cursor (for zoom centering)
** @y: Y coordinate of mouse cursor (for zoom centering)
** @img: Application data containing fractal view parameters
**
** Implements smooth zooming by scaling the complex plane bounds.
** Scroll up (code 4) zooms in by reducing the view area, while
** scroll down (code 5) zooms out by expanding it. The zoom is
** applied uniformly to both real and imaginary bounds, maintaining
** aspect ratio. Color animation is advanced with each zoom for
** dynamic visual effects.
*/
int	zoom(int mousecode, int x, int y, t_data *img)
{
	double	zoom;			/* Zoom scaling factor */

	if (x < 0 && y < 0)			/* Invalid mouse coordinates */
		return (0);			/* Ignore event */
	if (mousecode == 4)			/* Scroll up - zoom in */
		zoom = 0.9;			/* Reduce view area by 10% */
	else if (mousecode == 5)		/* Scroll down - zoom out */
		zoom = 1.1;			/* Expand view area by 10% */
	else
		return (0);			/* Unknown mouse event */
	
	/* Scale complex plane bounds uniformly */
	img -> max.real *= zoom;		/* Scale maximum real bound */
	img -> max.imag *= zoom;		/* Scale maximum imaginary bound */
	img -> min.real *= zoom;		/* Scale minimum real bound */
	img -> min.imag *= zoom;		/* Scale minimum imaginary bound */
	
	img -> color_off += 0.125;		/* Advance color animation */
	redraw_fractal(img);			/* Redraw with new zoom level */
	return (0);				/* Continue processing events */
}
