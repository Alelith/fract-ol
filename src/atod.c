/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:36:26 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/29 12:45:26 by acesteve         ###   ########.fr       */
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
	return (result);
}

double	atod(const char *nptr)
{
	double	sign;
	double	result;
	double	decimals;

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
	result = result * sign;
	return (result);
}
