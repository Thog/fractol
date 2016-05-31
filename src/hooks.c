#include "fractol.h"

void					recompile_render(t_env *env)
{
	if (env->render && env->render->data)
	{
		ft_bzero(env->render->data, env->render->line_size * HEIGHT);
	}
	render_julia(env);
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

	env = (t_env*)param;
	if (keycode == ESCAPE)
		exit(destroy_env(env));
	return (env == NULL);
}