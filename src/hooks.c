/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:04 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/30 16:37:05 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int				mouse_hook(int button, int x, int y, void *param)
{
	t_env		*env;
	int			old_zoom;

	if (param && x <= WIDTH && y <= HEIGHT)
	{
		env = (t_env*)param;
		old_zoom = env->zoom;
		if (button == 5 || button == 1)
			env->zoom += 1;
		else if ((button == 4 || button == 2) && env->zoom > 1)
			env->zoom -= 1;
		if (old_zoom != env->zoom)
		{
			env->move_x = env->zoom > 1 ? env->move_x
				+ (1.5 * (((double)x / WIDTH) - 0.5) / (env->zoom - 1)) : 0;
			env->move_y = env->zoom > 1 ? env->move_y
				+ (((double)y / HEIGHT) - 0.5) / (env->zoom - 1) : 0;
			env->update = 1;
		}
	}
	return (param == NULL);
}

int				expose_hook(void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		mlx_put_image_to_window(env->mlx, env->win, env->render->ptr, 0, 0);
	}
	return (param == NULL);
}

int				key_hook(int keycode, void *param)
{
	t_env		*env;
	int			iteration_modifier;

	if (param)
	{
		iteration_modifier = (keycode == NUM_MINUS ? -1 : keycode == NUM_PLUS);
		env = (t_env*)param;
		if (iteration_modifier)
		{
			if (iteration_modifier == 1)
				env->data->iteration_max *= 2;
			else
				env->data->iteration_max /= 2;
			if (env->data->iteration_max == 0)
				env->data->iteration_max = 1;
			env->update = 1;
		}
		else if (keycode == ESCAPE)
			exit(destroy_env(env, 0));
		else if (keycode == SPACE)
			env->locked = !env->locked;
	}
	return (param == NULL);
}

int				loop_hook(void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		if (env->update)
		{
			recompile_render(env);
			expose_hook(param);
			env->update = 0;
		}
	}
	return (param == NULL);
}

int				motion_hook(int x, int y, void *param)
{
	t_env		*env;

	if (param && x <= WIDTH && y <= HEIGHT)
	{
		env = (t_env*)param;
		if (!env->locked)
		{
			env->k = x * 0.003;
			env->j = y * 0.003;
			env->update = 1;
		}
	}
	return (param == NULL);
}
