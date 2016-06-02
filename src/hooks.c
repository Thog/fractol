#include "fractol.h"

void			recompile_render(t_env *env)
{
	if (env->render && env->render->data)
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);

	if (!ft_strcmp(env->type, "julia"))
		render_julia(env);
	else if (!ft_strcmp(env->type, "mandelbrot"))
		render_mandelbrot(env);
}

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
			recompile_render(env);
			expose_hook(param);
		}
	}
	return (env == NULL);
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

	if (param)
	{
		env = (t_env*)param;
		if (keycode == ESCAPE)
			exit(destroy_env(env, 0));
	}
	return (env == NULL);
}

int				motion_hook(int x, int y, void *param)
{
	t_env		*env;

	if (param)
	{
		env = (t_env*)param;
		env->moveX = x / WIDTH;
		env->moveY = y / HEIGHT;
	}
	return (env == NULL);
}
