/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:28 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/08 18:29:27 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			reset_parts(t_julia *data)
{
	data->prev_cx = 0;
	data->prev_cy = 0;
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
			data->c_re = 1.5 * (x - WIDTH / 2 + (e->move_x * e->zoom)) / (0.5 * e->zoom * WIDTH);
			data->c_im = (y - HEIGHT / 2 + (e->move_y * e->zoom)) / (0.5 * e->zoom * HEIGHT);
			reset_parts(data);
			compute_julia_pixel(e, x, y);
		}
	}
}
