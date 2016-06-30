/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:56:10 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/30 15:23:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "graphics.h"
# ifdef __APPLE__
#  define ESCAPE 53
# else
#  define ESCAPE 65307
# endif

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	char				*type;
	void				*data;
	t_image				*render;
	double				zoom;
	double				move_x;
	double				move_y;
	double				k;
	double				j;
	int					update;
}						t_env;

typedef struct			s_fractal
{
	double				c_re;
	double				c_im;
	double				cx;
	double				cy;
	double				prev_cx;
	double				prev_cy;
}						t_fractal;

int						init_display(t_env *env);
int						init_data(t_env *env, int ac, char **av);
t_fractal				*init_julia(void);
int						destroy_env(t_env *env, int exit_code);
void					recompile_render(t_env *env);
void					compute_julia_pixel(t_env *e, int x, int y);
int						ft_hsl_to_hex(int h, float s, float l);
void					render_julia(t_env *env);
void					render_mandelbrot(t_env *env);
void					print_usage(char *prg);
t_fractal				*init_burningshop(void);
void					render_burningship(t_env *env);
void					reset_parts(t_fractal *data);
#endif
