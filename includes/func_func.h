/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:00:40 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 21:30:32 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_FUNC_H
# define FUNC_FUNC_H

# include <libft.h>
# include "func_struct.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

/*
** **************************************************************************
**	func/func_fpc.c
** **************************************************************************
*/
void			fpsinit();
void			fpsthink();

/*
** **************************************************************************
**	func/func_help.c
** **************************************************************************
*/
SDL_Surface		*ft_sdl_load_bmp(char *str);
int				ft_error(char *code);
void			*ft_my_malloc(size_t s);
int				ft_cleanmem(t_list **lst);
void			ft_clean_sdl(t_wolf3d *w);

/*
** **************************************************************************
**	func/func_sdl.c
** **************************************************************************
*/
t_sdl			*sdl_init(t_sdl *sdl);

/*
** **************************************************************************
**	func/func_wu_color.c
** **************************************************************************
*/
int				ft_fdf_ipart(double x);
double			ft_fdf_round(double x);
double			ft_fdf_fpart(double x);
int				ft_fdf_get_color(int color1, int color2, double f1);

/*
** **************************************************************************
**	func/func_wu_draw.c
** **************************************************************************
*/
void			ft_fdf_plot(t_wolf3d *data, t_fdf_wu *wu, int x, int y);
void			ft_fdf_draw_line_first_pixels(t_wolf3d *data, t_fdf_wu **wu);
void			ft_fdf_draw_line_last_pixels(t_wolf3d *data, t_fdf_wu **wu);
void			ft_fdf_wu_cycle_x(t_wolf3d *data, t_fdf_wu *wu, double x);
void			ft_fdf_wu_cycle_y(t_wolf3d *data, t_fdf_wu *wu, double x);

/*
** **************************************************************************
**	func/func_wu.c
** **************************************************************************
*/
void			ft_fdf_init_wu(t_fdf_wu **wu, t_vector3 *dot_1, \
					t_vector3 *dot_2);
void			ft_fdf_init_wu_color(t_fdf_wu **wu, t_vector3 *dot_1, \
					t_vector3 *dot_2, int color);
void			ft_fdf_swap_double(double *n1, double *n2);
void			ft_fdf_draw_line_swap(t_fdf_wu **wu);
void			ft_fdf_draw_line_param(t_wolf3d *data, t_fdf_wu **wu);
void			ft_fdf_wu(t_vector3 *dot_1, t_vector3 *dot_2, t_wolf3d *data);
void			ft_fdf_wu_color(t_vector3 *dot_1, t_vector3 *dot_2, \
					t_wolf3d *data, int color);

#endif
