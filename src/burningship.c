/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 13:42:31 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/09 14:45:08 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_julia				*init_burningshop(void)
{
	t_julia		*result;

	if (!(result = (t_julia*)ft_memalloc(sizeof(t_julia))))
		return (NULL);
	result->c_re = -2.5;
	result->c_im = 2.5;
	return (result);
}

void				compute_burningship_pixel(t_env *e, int x, int y)
{
	t_julia	*data;
	int		i;

	data = (t_julia*)e->data;
	i = -1;
	while ((++i) < 512)
	{
		data->prev_cx = data->cx;
		data->prev_cy = data->cy;
		data->cx = data->prev_cx * data->prev_cx - data->prev_cy
			* data->prev_cy + data->c_re;
		data->cy = 2 * fabs(data->prev_cx * data->prev_cy) + data->c_im;
		if ((data->cx * data->cx + data->cy * data->cy) > 4)
			break ;
	}
	put_pixel(e->render, x, y, ft_hsl_to_hex(i % 360, 1, 0.5 * (i < 512)));
}

void				render_burningship(t_env *e)
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
			data->c_re = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH) - 0.45;
			data->c_re += 2 * e->move_x;
			data->c_im = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT) - 0.52;
			data->c_im += 2 * e->move_y;
			reset_parts(data);
			compute_burningship_pixel(e, x, y);
		}
	}
}
