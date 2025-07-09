/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 19:41:37 by lilith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# ifndef WIDTH
#  define SCREEN_WIDTH 960
# endif
# ifndef HEIGHT
#  define SCREEN_HEIGHT 540
# endif

# ifndef ITER
#  define ITER 60
# endif

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# include "ft_printf.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>

typedef enum e_fractals
{
	MANDELBROT = 0,
	JULIA = 1,
	SINH_MANDELBROT = 2,
	EYE_MANDELBROT = 3
}	t_fractals;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	double		color_off;
	t_complex	max;
	t_complex	min;
	t_complex	initial_z;
	t_complex	initial_c;
	t_fractals	type;
}	t_data;

double		atod(const char *nptr);
void		my_mlx_pixel_put(t_data *data, t_vector2 pos, int color);

/*Color functions*/
int			get_color_hsv(int iter);
int			psychedelic_color(int iter, double phase);

/*Complex numbers operators*/
double		complx_module(t_complex num);
t_complex	inv_complx(t_complex a);
t_complex	sinh_complx(t_complex num);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	div_complx(t_complex a, t_complex b);
t_complex	multiply_complx(t_complex a, t_complex b);

/*Fractal render*/
void		redraw_fractal(t_data *data);
void		draw_julia(t_data *img, t_complex z, t_vector2 pos);
void		draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

/*Handlers*/
int			key_handler(int keycode, t_data *vars);
int			zoom(int mousecode, int x, int y, t_data *img);

int			ft_strcmp(char *a, char *b);
int			is_mandelbrot(char *type);
int			is_julia(char *type);
int			close(t_data *vars);
#endif
