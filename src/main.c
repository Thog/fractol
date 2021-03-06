/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:44:32 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/30 15:35:27 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*init_fractal(char *type)
{
	if (!ft_strcmp(type, "julia") || !ft_strcmp(type, "mandelbrot"))
		return ((void*)init_julia());
	else if (!ft_strcmp(type, "burningship"))
		return ((void*)init_burningshop());
	return (NULL);
}

int			init_display(t_env *env)
{
	if (!(env->mlx = mlx_init()) ||
			!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "fractol"))
			|| !(env->render = new_img(env->mlx, WIDTH, HEIGHT)))
		return (ft_error_retint("Display cannot be initialized!\n", 1));
	ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	mlx_key_hook(env->win, key_hook, env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
	if (!ft_strcmp(env->type, "julia"))
		mlx_hook(env->win, 6, (1L << 6), motion_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	return (0);
}

int			init_data(t_env *env, int ac, char **av)
{
	env->locked = 0;
	env->zoom = 1;
	env->move_x = 0;
	env->move_y = 0;
	if (ac == 2)
	{
		env->type = *(av + 1);
		env->data = init_fractal(env->type);
	}
	if (env->data == NULL)
		print_usage(*av);
	return (env->data == NULL);
}

void		recompile_render(t_env *env)
{
	if (env->render && env->render->data)
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	if (!ft_strcmp(env->type, "julia"))
		render_julia(env);
	else if (!ft_strcmp(env->type, "mandelbrot"))
		render_mandelbrot(env);
	else if (!ft_strcmp(env->type, "burningship"))
		render_burningship(env);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))) || init_data(env, ac, av) ||
		init_display(env))
		return (destroy_env(env, 1));
	env->update = 1;
	mlx_loop(env->mlx);
	return (destroy_env(env, 0));
}
