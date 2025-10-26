#ifndef FRACT_OL_H
# define FRACT_OL_H

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 960
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 540
# endif

# ifndef ITER
#  define ITER 20
# endif

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef NUM_THREADS
#  define NUM_THREADS 8
# endif

# include "survival_lib.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

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
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			color_off;
	double			zoom_factor;
	t_complex		max;
	t_complex		min;
	t_complex		initial_z;
	t_complex		initial_c;
	t_fractals		type;
	pthread_mutex_t	img_mutex;
}	t_data;

typedef struct s_thread_data
{
	t_data		*data;
	int			start_y;
	int			end_y;
	int			thread_id;
}	t_thread_data;

void		my_mlx_pixel_put(t_data *data, t_vector2 pos, int color);
int			get_color_hsv(int iter, int max_iter);
int			psychedelic_color(int iter, double phase, int iterations);

double		complx_module(t_complex num);
t_complex	inv_complx(t_complex a);
t_complex	sinh_complx(t_complex num);
t_complex	sum_complx(t_complex a, t_complex b);
t_complex	div_complx(t_complex a, t_complex b);
t_complex	multiply_complx(t_complex a, t_complex b);

int			calculate_iterations(t_data *data, int max_iter);
void		redraw_fractal(t_data *data);
void		*render_fractal_threaded(void *arg);
void		draw_julia(t_data *img, t_complex z, t_vector2 pos);
void		draw_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_eye_mandelbrot(t_data *img, t_complex c, t_vector2 pos);
void		draw_sinh_mandelbrot(t_data *img, t_complex c, t_vector2 pos);

int			key_handler(int keycode, t_data *vars);
int			zoom(int mousecode, int x, int y, t_data *img);

int			is_mandelbrot(char *type);
int			is_julia(char *type);

int			close_window(t_data *vars);

#endif
