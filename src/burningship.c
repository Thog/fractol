/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 13:42:31 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/30 16:22:36 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal			*init_burningshop(void)
{
	t_fractal		*result;

	if (!(result = (t_fractal*)ft_memalloc(sizeof(t_fractal))))
		return (NULL);
	result->c_re = -2.5;
	result->c_im = 2.5;
	result->iteration_max = 512;
	return (result);
}

void				compute_burningship_pixel(t_env *e, int x, int y)
{
	t_fractal	*data;
	int			i;
	int			it_max;

	data = e->data;
	it_max = data->iteration_max;
	i = -1;
	while ((++i) < it_max)
	{
		data->prev_cx = data->cx;
		data->prev_cy = data->cy;
		data->cx = data->prev_cx * data->prev_cx - data->prev_cy
			* data->prev_cy + data->c_re;
		data->cy = 2 * fabs(data->prev_cx * data->prev_cy) + data->c_im;
		if ((data->cx * data->cx + data->cy * data->cy) > 4)
			break ;
	}
	put_pixel(e->render, x, y, ft_hsl_to_hex(i % 360, 1, 0.5 * (i < it_max)));
}

void				render_burningship(t_env *e)
{
	int			x;
	int			y;
	t_fractal	*data;

	y = -1;
	data = (t_fractal*)e->data;
	while ((++y) < HEIGHT)
	{
		x = -1;
		while ((++x) < WIDTH)
		{
			data->c_re = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH)
				+ (2 * e->move_x) - 0.45;
			data->c_im = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT)
				+ (2 * e->move_y) - 0.52;
			reset_parts(data);
			compute_burningship_pixel(e, x, y);
		}
	}
}
