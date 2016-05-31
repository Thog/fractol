#include "fractol.h"

void					render_julia(t_env *env)
{
	int		x;
	int		y;
	int		i;
	t_julia	*data;

	y = 0;
	data = (t_julia*)env->data;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			i = 0;
			data->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * env->zoom * WIDTH) + env->moveX;
			data->newIm = (y - HEIGHT / 2) / (0.5 * env->zoom * HEIGHT) + env->moveY;
			while(i < 128)
			{
				data->oldRe = data->newRe;
				data->oldIm = data->newIm;
				data->newRe = data->oldRe * data->oldRe - data->oldIm * data->oldIm + data->cRe;
				data->newIm = 2 * data->oldRe * data->oldIm + data->cIm;
				if((data->newRe * data->newRe + data->newIm * data->newIm) > 4)
					break ;
				i++;
	        }
	        set_pixel(env->render, x, y, RGB(i % 256, 255, 255 * (i < 128)));
			x++;
		}
		y++;
	}
}
