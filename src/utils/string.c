/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:34:28 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** STRING UTILITIES - String comparison and fractal type identification
**
** This file implements string comparison functions and fractal type
** detection utilities for command-line argument parsing. It provides
** case-sensitive string matching and categorizes fractal types into
** Mandelbrot variants and Julia sets for proper initialization and
** parameter handling in the fractal explorer application.
*/

/*
** ft_strcmp - Compare two strings for exact equality
** @a: First string to compare
** @b: Second string to compare
**
** Performs character-by-character comparison of two strings to
** determine if they are identical. Unlike standard strcmp which
** returns difference values, this function returns 1 for exact
** matches and 0 for any difference. Used for command-line argument
** validation where exact string matches are required.
** Returns 1 if strings are identical, 0 if different.
*/
int	ft_strcmp(char *a, char *b)
{
	while (*a && *b)			/* Compare while both have characters */
	{
		if (*a != *b)			/* Characters differ */
			return (0);		/* Strings are not equal */
		a++;				/* Advance first string pointer */
		b++;				/* Advance second string pointer */
	}
	return (*a == *b);			/* Check if both strings ended */
}

/*
** is_mandelbrot - Check if fractal type is a Mandelbrot variant
** @type: String containing fractal type name
**
** Determines whether the specified fractal type belongs to the
** Mandelbrot family of fractals. Recognizes "mandelbrot" (classic),
** "sinh" (hyperbolic sine variant), and "eye" (cubic variant) as
** Mandelbrot-type fractals. These fractals share similar parameter
** requirements and initialization procedures, distinguishing them
** from Julia sets which need different setup.
** Returns 1 if type is a Mandelbrot variant, 0 otherwise.
*/
int	is_mandelbrot(char *type)
{
	if (ft_strcmp(type, "mandelbrot")		/* Classic Mandelbrot */
		|| ft_strcmp(type, "sinh")		/* Sinh Mandelbrot variant */
		|| ft_strcmp(type, "eye"))		/* Eye Mandelbrot variant */
		return (1);				/* Is Mandelbrot type */
	return (0);					/* Not Mandelbrot type */
}

/*
** is_julia - Check if fractal type is a Julia set
** @type: String containing fractal type name
**
** Determines whether the specified fractal type is a Julia set.
** Julia sets require different initialization parameters compared
** to Mandelbrot sets, including a complex constant c value that
** defines the specific Julia set shape. This function enables
** the application to apply appropriate initialization procedures
** for Julia set fractals.
** Returns 1 if type is Julia set, 0 otherwise.
*/
int	is_julia(char *type)
{
	if (ft_strcmp(type, "julia"))			/* Julia set type */
		return (1);				/* Is Julia set */
	return (0);					/* Not Julia set */
}
