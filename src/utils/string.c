/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:34:28 by acesteve          #+#    #+#             */
/*   Updated: 2025/07/05 17:25:35 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *a, char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	return (*a == *b);
}

int	is_mandelbrot(char *type)
{
	if (ft_strcmp(type, "mandelbrot")
		|| ft_strcmp(type, "sinh")
		|| ft_strcmp(type, "eye"))
		return (1);
	return (0);
}

int	is_julia(char *type)
{
	if (ft_strcmp(type, "julia"))
		return (1);
	return (0);
}
