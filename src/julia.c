/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:23 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/30 15:25:52 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

t_fractal			*init_julia(void)
{
	t_fractal		*result;

	if (!(result = (t_fractal*)ft_memalloc(sizeof(t_fractal))))
		return (NULL);
	return (result);
}

void				compute_julia_pixel(t_env *e, int x, int y)
{
	t_fractal	*data;
	int			i;

	data = (t_fractal*)e->data;
	i = -1;
	while ((++i) < 128)
	{
		data->prev_cx = data->cx;
		data->prev_cy = data->cy;
		data->cx = data->prev_cx * data->prev_cx - data->prev_cy
			* data->prev_cy + data->c_re;
		data->cy = 2 * data->prev_cx * data->prev_cy + data->c_im;
		if ((data->cx * data->cx + data->cy * data->cy) > 4)
			break ;
	}
	put_pixel(e->render, x, y, ft_hsl_to_hex(i % 360, 1, 0.5 * (i < 128)));
}

void				render_julia(t_env *e)
{
	int			x;
	int			y;
	t_fractal	*data;

	y = -1;
	data = (t_fractal*)e->data;
	data->c_re = -0.8 + e->k;
	data->c_im = 0.156 + e->j;
	while ((++y) < HEIGHT)
	{
		x = -1;
		while ((++x) < WIDTH)
		{
			data->cx = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH)
				+ (2 * e->move_x);
			data->cy = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT)
				+ (2 * e->move_y);
			compute_julia_pixel(e, x, y);
		}
	}
}
