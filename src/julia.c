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

void 				compute_julia_pixel(t_env *e, int x, int y)
{
	t_julia	*data;
	int		i;

	data = (t_julia*)e->data;
	i = -1;
	while((++i) < 128)
	{
		data->oldRe = data->newRe;
		data->oldIm = data->newIm;
		data->newRe = data->oldRe * data->oldRe - data->oldIm * data->oldIm + data->cRe;
		data->newIm = 2 * data->oldRe * data->oldIm + data->cIm;
		if((data->newRe * data->newRe + data->newIm * data->newIm) > 4)
			break ;
	}
	set_pixel(e->render, x, y, RGB(i % 256, 255, 255 * (i < 128)));
}
void					render_julia(t_env *e)
{
	int		x;
	int		y;
	t_julia	*data;

	y = -1;
	data = (t_julia*)e->data;
	while ((++y) < HEIGHT)
	{
		x = -1;
		while ((++x) < WIDTH)
		{
			data->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH);
			data->newRe += e->moveX;
			data->newIm = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT);
			data->newIm += e->moveY;
			compute_julia_pixel(e, x, y);
		}
	}
}
