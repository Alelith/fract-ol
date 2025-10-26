#include "fract_ol.h"

void	my_mlx_pixel_put(t_data *data, t_vector2 pos, int color)
{
	char	*dst;

	pthread_mutex_lock(&data->img_mutex);

	dst = data->addr;
	dst += (pos.y * data->line_length + pos.x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;

	pthread_mutex_unlock(&data->img_mutex);
}
