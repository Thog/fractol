#include "fractol.h"

static void *init_fractal(char *type)
{
	if (!ft_strcmp(type, "julia"))
		return ((void*)init_julia());
	return (NULL);
}

int			init_display(t_env *env)
{
	if (!(env->mlx = mlx_init()) ||
			!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "fractol")))
		return (1);
	env->render = new_img(env->mlx, WIDTH, HEIGHT);
	ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	mlx_key_hook(env->win, key_hook, env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
	if (!ft_strcmp(env->type, "julia"))
		mlx_hook(env->win, 6, (1L << 6), motion_hook, env);
	return (0);
}

int			init_data(t_env *env, int ac, char **av)
{
	env->zoom = 1;
	if (ac == 2)
	{
		env->type = *(av + 1);
		env->data = init_fractal(env->type);
	}
	if (env->data == NULL)
		print_usage(*av);
	return (env->data == NULL);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))) || init_data(env, ac, av))
		return (destroy_env(env, 1));
	init_display(env);
	recompile_render(env);
	mlx_loop(env->mlx);
	return (destroy_env(env, 0));
}
