/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 12:51:10 by acesteve         ###   ########.fr       */
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
#  define ITER 50
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
}	t_data;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
double		atod(const char *nptr);

/*Color functions*/
int			psychedelic_color(int iter, int max_iter, double phase);

/*Complex numbers operators*/
t_complex	multiply_complx(t_complex a, t_complex b);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	subs_complx(t_complex a, t_complex b);
void		print_complx(t_complex num);
double		complx_module(t_complex num);

void		draw_mandelbrot(t_data *img);
void		draw_julia(t_data *img, double c_real, double c_img);

#endif
