/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:36:26 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:50 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ASCII TO DOUBLE - String to floating-point number conversion
**
** This file implements a custom ASCII to double conversion function
** for parsing command-line arguments containing floating-point values.
** It handles both integer and decimal portions of numbers, supports
** negative values, and provides precise conversion for mathematical
** parameters used in fractal calculations.
*/

/*
** get_decimals - Parse decimal portion of floating-point number
** @nptr: Pointer to string containing decimal digits
**
** Processes the fractional part of a floating-point number by
** converting each decimal digit and dividing by appropriate power
** of 10. Accumulates the fractional value by progressively reducing
** the weight of each digit (0.1, 0.01, 0.001, etc.). This allows
** precise representation of decimal values for mathematical
** calculations requiring fractional precision.
** Returns the decimal portion as a double value.
*/
static double	get_decimals(const char *nptr)
{
	double	result;		/* Accumulated decimal value */
	double	decimals;	/* Current decimal place divisor */

	result = 0;
	decimals = 10.0;	/* Start with tenths place */
	while (*nptr >= '0' && *nptr <= '9')	/* Process decimal digits */
	{
		/* Add digit value divided by current decimal place */
		result += (*nptr - 48) / decimals;
		nptr++;				/* Move to next digit */
		decimals *= 10;			/* Next decimal place */
	}
	return (result);			/* Return fractional part */
}

/*
** atod - Convert ASCII string to double-precision floating-point
** @nptr: Pointer to null-terminated string containing number
**
** Converts a string representation of a number to a double-precision
** floating-point value. Handles negative signs, integer portions,
** and decimal portions with full precision. Used for parsing
** command-line arguments that specify complex number parameters
** for Julia sets and other fractal customizations. Follows standard
** atof behavior but with custom implementation for portability.
** Returns the converted double value.
*/
double	atod(const char *nptr)
{
	double	sign;		/* Sign multiplier (1 or -1) */
	double	result;		/* Accumulated numeric result */

	sign = 1;
	result = 0;
	if (*nptr == '-')		/* Check for negative sign */
	{
		sign = -1;		/* Set negative multiplier */
		nptr++;			/* Skip sign character */
	}
	while (*nptr >= '0' && *nptr <= '9')	/* Process integer digits */
	{
		result = result * 10 + (*nptr - 48);	/* Accumulate integer value */
		nptr++;					/* Move to next digit */
	}
	if (*nptr == '.')				/* Decimal point found */
	{
		nptr++;					/* Skip decimal point */
		result += get_decimals(nptr);		/* Add fractional part */
	}
	result = result * sign;				/* Apply sign */
	return (result);				/* Return final value */
}
