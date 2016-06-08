/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:28 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/08 17:43:48 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		reset_parts(t_julia *data)
{
	data->old_cx = 0;
	data->old_cy = 0;
	data->cx = 0;
	data->cy = 0;
}

void			render_mandelbrot(t_env *e)
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
			data->cx = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH);
			data->cx += e->move_x;
			data->cy = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT);
			data->cy += e->move_y;
			reset_parts(data);
			compute_julia_pixel(e, x, y);
		}
	}
}
