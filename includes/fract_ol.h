/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 22:33:13 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# ifndef W
#  define W 1920
# endif
# ifndef H
#  define H 1080
# endif

# ifndef ITER
#  define ITER 40
# endif

# define PI 3.14159265358979323846

# include "ft_printf.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	x_max;
	double	x_min;
	double	y_max;
	double	y_min;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
double		atod(const char *nptr);

/*Color functions*/
int			psychedelic_color(int iter, double phase);
int			get_color_hsv(int iter);

/*Complex numbers operators*/
t_complex	multiply_complx(t_complex a, t_complex b);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	sinh_complx(t_complex num);
t_complex	div_complx(t_complex a, t_complex b);
double		complx_module(t_complex num);

void		draw_mandelbrot(t_data *img);
void		draw_sinh_mandelbrot(t_data *img);
void		draw_julia(t_data *img, double c_real, double c_img);

#endif
