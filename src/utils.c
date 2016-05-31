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

int				destroy_env(t_env *env)
{
	if (env->render)
	{
		if (env->mlx)
		{
			if (env->win)
				mlx_destroy_window(env->mlx, env->win);
			mlx_destroy_image(env->mlx, env->render->ptr);
		}
	}
	ft_memdel((void*)&env->render);
	ft_memdel((void*)&env);
	return (EXIT_SUCCESS);
}
