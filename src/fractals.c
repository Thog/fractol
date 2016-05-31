#include "fractol.h"

t_julia			*init_julia(void)
{
	t_julia		*result;

	if (!(result = (t_julia*)ft_memalloc(sizeof(t_julia))))
		return (NULL);
	result->cRe = -0.7;
	result->cIm = 0.27015;
	return (result);
}
