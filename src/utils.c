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

void					set_rgb(t_color *color, char red, char green,
	char blue)
{
	color->red = red;
	color->green = green;
	color->blue = blue;
	color->alpha = 0;
}

int		ft_HSLtoHex(int h, float s, float l)
{
	t_color		color;
	float		C;
	float		X;
	float		m;

	C = (1.0 - fabs(2 * l - 1.0)) * s;
	X = C * (1.0 - fabs(fmod((h / 60.0), 2) - 1.0));
	m = l - 0.5 * C;
	//printf("C = %f, X = %f, m = %f\n", C, X, m);
	if (h >= 0 && h < 60)
		set_rgb(&color, (C + m) * 255, (X + m) * 255, (0 + m) * 255);
	else if (h >= 60 && h < 120)
		set_rgb(&color, (X + m) * 255, (C + m) * 255, (0 + m) * 255);
	else if (h >= 120 && h < 180)
		set_rgb(&color, (0 + m) * 255, (C + m) * 255, (X + m) * 255);
	else if (h >= 180 && h < 240)
		set_rgb(&color, (0 + m) * 255, (X + m) * 255, (C + m) * 255);
	else if (h >= 240 && h < 300)
		set_rgb(&color, (X + m) * 255, (0 + m) * 255, (C + m) * 255);
	else if (h >= 300 && h < 360)
		set_rgb(&color, (C + m) * 255, (0 + m) * 255, (X + m) * 255);
	else
		set_rgb(&color, 255, 255, 255);
	return (RGB(color.red, color.green, color.blue));
}
