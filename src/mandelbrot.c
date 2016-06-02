#include "fractol.h"

static void		reset_parts(t_julia *data)
{
	data->oldRe = 0;
	data->oldIm = 0;
	data->newRe = 0;
	data->newIm = 0;
}

void 			render_mandelbrot(t_env *e)
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
			data->cRe = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH);
			data->cRe += e->moveX;
			data->cIm = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT);
			data->cIm += e->moveY;
			reset_parts(data);
			compute_julia_pixel(e, x, y);
		}
	}
}
