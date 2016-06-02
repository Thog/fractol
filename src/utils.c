#include "fractol.h"

t_pos			*new_pos(int x, int y, int z)
{
	t_pos *result;

	if (!(result = (t_pos*)malloc(sizeof(t_pos))))
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

int				destroy_env(t_env *env, int exit_code)
{
	if (env)
	{
		if (env->render)
		{
			if (env->mlx)
			{
				if (env->win)
					mlx_destroy_window(env->mlx, env->win);
				mlx_destroy_image(env->mlx, env->render->ptr);
			}
			ft_memdel((void*)&env->render);
		}
		ft_memdel((void*)&env);
	}
	return (exit_code);
}

void					print_usage(char *prg)
{
	ft_printf_fd(2, "Usage: %s [type]\nType: julia, mandelbrot\n", prg);
}
