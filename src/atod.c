/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:36:26 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/26 19:59:40 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	get_decimals(const char *nptr)
{
	double	result;
	double	decimals;

	result = 0;
	decimals = 10.0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result += (*nptr - 48) / decimals;
		nptr++;
		decimals *= 10;
	}
}

double	atod(const char *nptr)
{
	int		sign;
	double	result;
	int		decimals;

	sign = 1;
	result = 0;
	decimals = 10;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		result += get_decimals(nptr);
	}
	return (result * sign);
}
