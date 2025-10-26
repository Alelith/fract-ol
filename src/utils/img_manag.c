/**
 * @file img_manag.c
 * @author Lilith Estévez Boeta
 * @brief This file contains image buffer management functions for pixel operations with thread-safe access.
 */

#include "fract_ol.h"

/**
 * @brief Puts a pixel at a specific position in the image buffer.
 * @details Thread-safe pixel writing using mutex lock protection.
 * 
 * @param data Pointer to the main data structure containing image information.
 * @param pos Screen position (x, y coordinates) of the pixel.
 * @param color Color value to write (TRGB format).
 */
void	my_mlx_pixel_put(t_data *data, t_vector2 pos, int color)
{
	char	*dst;

	pthread_mutex_lock(&data->img_mutex);

	dst = data->addr;
	dst += (pos.y * data->line_length + pos.x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;

	pthread_mutex_unlock(&data->img_mutex);
}
