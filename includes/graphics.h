/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:26:50 by tguillem          #+#    #+#             */
/*   Updated: 2016/05/27 13:15:47 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <mlx.h>
# include "libft.h"
# define WIDTH 1366
# define HEIGHT 768
# define ISO_C1 0.5F
# define ISO_C2 0.5F
# define PROJ_ISO_X(X, Y, Z) ISO_C1 * X - ISO_C2 * Y
# define PROJ_ISO_Y(X, Y, Z) -Z + (ISO_C1 / 2) * X + (ISO_C2 / 2) * Y
# define RGB(R, G, B) (R << 16)| (G << 8) | B

typedef int				(*t_transformer)(int x, int y, int z);
typedef unsigned int	(*t_colorizer)(int iteration);

typedef struct			s_pos
{
	int					x;
	int					y;
	int					z;
}						t_pos;

typedef struct			s_image
{
	void				*ptr;
	char				*data;
	int					byte_per_pixel;
	int					endian;
	int					line_size;
	int					width;
	int					height;
}						t_image;

t_pos					*new_pos(int x, int y, int z);
t_image					*new_img(void *mlx, int width, int height);
void					set_pixel(t_image *img, int x, int y,
	unsigned int color);
int						draw_line_d(t_image *img, t_pos *start, t_pos *end,
	t_colorizer *colorizer);
int						draw_line_3d(t_image *img, t_pos *start, t_pos *end,
	t_colorizer *colorizer);
int						expose_hook(void *param);
int						key_hook(int keycode, void *param);
int						mouse_hook(int button, int x, int y, void *param);
int						motion_hook(int x, int y, void *param);
#endif
