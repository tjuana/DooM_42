/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:00:40 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 21:31:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_FUNC_H
# define FUNC_FUNC_H

# include <libft.h>
# include "func_struct.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"

/*
** **************************************************************************
**	src/func/func_color.c
** **************************************************************************
*/
Uint32		ft_rgb_to_hex(Uint32 r, Uint32 g, Uint32 b);
Uint32		ft_color_struct_to_hex(t_color color);
Uint32		ft_hex_transform(int color, float percent);

/*
** **************************************************************************
**	src/func/func_help.c
** **************************************************************************
*/
int			ft_error(char *code);
void		*ft_my_malloc(size_t s);
void		ft_clean_sdl(t_wolf3d *w);

/*
** **************************************************************************
**	src/func/func_sdl.c
** **************************************************************************
*/
void		ft_set_window_icon(t_sdl *sdl);
void		sdl_create_background_music(t_sdl *sdl);
void		sound(t_new_player *pl, char *name, int channel);
t_sdl		*sdl_init(t_sdl *sdl);

/*
** **************************************************************************
**	src/func/func_wu.c
** **************************************************************************
*/
void		ft_fdf_swap_double(double *n1, double *n2);
void		ft_fdf_wu(t_vector3 *dot_1, t_vector3 *dot_2, t_wolf3d *data);
void		ft_fdf_wu_color(t_vector3 *dot_1, t_vector3 *dot_2, \
				t_wolf3d *data, int color);
void		ft_fdf_wu_rect_color(t_wolf3d *data, t_gui_rect coord, \
				t_gui_rect area, int color);

/*
** **************************************************************************
**	src/func/func_wu_color.c
** **************************************************************************
*/
int			ft_fdf_ipart(double x);
double		ft_fdf_round(double x);
double		ft_fdf_fpart(double x);
int			ft_fdf_get_color(int color1, int color2, double f1);

/*
** **************************************************************************
**	src/func/func_wu_draw.c
** **************************************************************************
*/
void		ft_fdf_plot(t_wolf3d *data, t_fdf_wu *wu, int x, int y);
void		ft_fdf_draw_line_first_pixels(t_wolf3d *data, t_fdf_wu **wu);
void		ft_fdf_draw_line_last_pixels(t_wolf3d *data, t_fdf_wu **wu);
void		ft_fdf_wu_cycle_x(t_wolf3d *data, t_fdf_wu *wu, double x);
void		ft_fdf_wu_cycle_y(t_wolf3d *data, t_fdf_wu *wu, double x);

/*
** **************************************************************************
**	src/func/func_wu_init.c
** **************************************************************************
*/
void		ft_fdf_init_wu(t_fdf_wu **wu, t_vector3 *dot_1, t_vector3 *dot_2);
void		ft_fdf_init_wu_color(t_fdf_wu **wu, t_vector3 *dot_1, \
				t_vector3 *dot_2, int color);
void		ft_fdf_init_wu_rect_color(t_fdf_wu **wu, t_gui_rect coord, \
				t_gui_rect area, int color);

/*
** **************************************************************************
**	src/func/func_wu_line.c
** **************************************************************************
*/
void		ft_fdf_draw_line_swap(t_fdf_wu **wu);
void		ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);

#endif
