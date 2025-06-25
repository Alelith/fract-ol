/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:22:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/25 23:50:54 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

int	hsv_to_rgb(float h, float S, float V)
{
    float C = V * S;
    float X = C * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
    float m = V - C;
    float r1, g1, b1;

    if      (h <  60) { r1 = C; g1 = X; b1 = 0; }
    else if (h < 120) { r1 = X; g1 = C; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = C; b1 = X; }
    else if (h < 240) { r1 = 0; g1 = X; b1 = C; }
    else if (h < 300) { r1 = X; g1 = 0; b1 = C; }
    else              { r1 = C; g1 = 0; b1 = X; }

	get_trgb(0, round((r1 + m) * 255.0), round((g1 + m) * 255.0), round((b1 + m) * 255.0));
}

int trgb_rainbow(int v) {
    if (v < 0)   v = 0;
    if (v > 255) v = 255;

    float h = (360.0f * v) / 255.0f;
    return(hsv_to_rgb(h, 1.0f, 1.0f));
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data   img;
    t_complex c, z;
    int      i, j;
    double   centerX = -0.5;    // centro en x
    double   centerY =  0.0;    // centro en y
    double   zoom    = 0.25;     // >1 hace “zoom in”, <1 hace “zoom out”
    double   aspect  = (double)H / W;
    double   viewW   = 3.5 / zoom;    // ancho de ventana en el plano complejo
    double   viewH   = viewW * aspect; // alto para conservar proporción

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W, H, "Hello world!");
	img.img = mlx_new_image(mlx, W, H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (j = 0; j < H; j++)
    {
        for (i = 0; i < W; i++)
        {
            // transformo i,j en un punto centrado y escalado
            c.real = centerX + ( (double)i / W  - 0.5 ) * viewW;
            c.imag = centerY + ( (double)j / H  - 0.5 ) * viewH;

            z.real = 0;
            z.imag = 0;
            int dives = diverge(z, c, 255, 10000000);
            if (dives)
                my_mlx_pixel_put(&img, i, j, trgb_rainbow(dives));
            else
                my_mlx_pixel_put(&img, i, j, 0x00330033);
        }
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
