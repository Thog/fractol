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
	double				moveX;
	double				moveY;
}						t_env;

typedef struct			s_julia
{
	double				cRe;
	double				cIm;
	double				newRe;
	double				newIm;
	double				oldRe;
	double				oldIm;
}						t_julia;

int						init_display(t_env *env);
int						init_data(t_env *env, int ac, char **av);
t_julia					*init_julia(void);
int						destroy_env(t_env *env, int exit_code);
void					recompile_render(t_env *env);
void 					compute_julia_pixel(t_env *e, int x, int y);
void					render_julia(t_env *env);
void 					render_mandelbrot(t_env *env);
void					print_usage(char *prg);

#endif
