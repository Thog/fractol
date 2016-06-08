/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:23 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/07 15:13:56 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_julia				*init_julia(void)
{
	t_julia		*result;

	if (!(result = (t_julia*)ft_memalloc(sizeof(t_julia))))
		return (NULL);
	result->c_re = -0.7;
	result->c_im = 0.27015;
	return (result);
}

void				compute_julia_pixel(t_env *e, int x, int y)
{
	t_julia	*data;
	int		i;

	data = (t_julia*)e->data;
	i = -1;
	while ((++i) < 1024)
	{
		data->old_re = data->new_re;
		data->old_im = data->new_im;
		data->new_re = data->old_re * data->old_re - data->old_im
			* data->old_im + data->c_re;
		data->new_im = 2 * data->old_re * data->old_im + data->c_im;
		if ((data->new_re * data->new_re + data->new_im * data->new_im) > 4)
			break ;
	}
	set_pixel(e->render, x, y, ft_hsl_to_hex(i % 360, 1, 0.5 * (i < 1024)));
}

void				render_julia(t_env *e)
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
			data->new_re = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH);
			data->new_re += e->move_x;
			data->new_im = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT);
			data->new_im += e->move_y;
			compute_julia_pixel(e, x, y);
		}
	}
}
