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
 * @param data Pointer to the main data structure containing pixel buffer information.
 * @param pos Screen position (x, y coordinates) of the pixel.
 * @param color Color value to write (ARGB format).
 */
void	my_mlx_pixel_put(t_data *data, t_vector2 pos, int color)
{
	int	index;

	pthread_mutex_lock(&data->pixels_mutex);

	if (pos.x >= 0 && pos.x < SCREEN_WIDTH && pos.y >= 0 && pos.y < SCREEN_HEIGHT)
	{
		index = pos.y * SCREEN_WIDTH + pos.x;
		data->pixels[index] = (Uint32)color;
	}

	pthread_mutex_unlock(&data->pixels_mutex);
}
