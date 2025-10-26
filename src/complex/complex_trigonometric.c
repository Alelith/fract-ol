#include "fract_ol.h"

t_complex	sinh_complx(t_complex num)
{
	t_complex	result;

	result.real = sinh(num.real) * cos(num.imag);

	result.imag = cosh(num.real) * sin(num.imag);
	return (result);
}
