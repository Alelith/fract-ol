/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/25 23:45:23 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#define W 1920
#define H 1080

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

/*Color functions*/
int			get_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/*Complex numbers operators*/
t_complex	multiply_complx(t_complex a, t_complex b);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	subs_complx(t_complex a, t_complex b);
void		print_complx(t_complex num);
double		complx_module(t_complex num);

t_complex	iteration(t_complex z, t_complex c);
int			diverge(t_complex z, t_complex c, int iter, double limit);

#endif
