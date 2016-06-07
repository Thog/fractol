/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 13:56:10 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/07 15:09:39 by tguillem         ###   ########.fr       */
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
}						t_env;

typedef struct			s_julia
{
	double				c_re;
	double				c_im;
	double				new_re;
	double				new_im;
	double				old_re;
	double				old_im;
}						t_julia;

int						init_display(t_env *env);
int						init_data(t_env *env, int ac, char **av);
t_julia					*init_julia(void);
int						destroy_env(t_env *env, int exit_code);
void					recompile_render(t_env *env);
void					compute_julia_pixel(t_env *e, int x, int y);
int						ft_hsl_to_hex(int h, float s, float l);
void					render_julia(t_env *env);
void					render_mandelbrot(t_env *env);
void					print_usage(char *prg);

#endif
