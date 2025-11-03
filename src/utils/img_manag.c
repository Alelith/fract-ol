/**
 * @file img_manag.c
 * @brief Pixel buffer management with thread-safe write operations
 *
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#include "fract_ol.h"

/**
 * @brief Thread-safe pixel write to the rendering buffer
 *
 * @details Writes a color value to the pixel buffer at the specified screen
 * coordinates. Uses mutex locking to ensure thread safety during multi-threaded
 * rendering. Performs bounds checking to prevent buffer overruns. The pixel
 * buffer is a flat array indexed as (y * width + x) in ARGB8888 format.
 *
 * @ingroup utils
 *
 * @param[in,out] data Pointer to application state containing pixel buffer and mutex
 * @param[in] pos Screen coordinates of the pixel to write
 * @param[in] color 32-bit ARGB color value to write
 *
 * @note Mutex-protected to allow safe concurrent writes from multiple threads
 * @warning Silently ignores writes outside screen bounds
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
