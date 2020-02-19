/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_grid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:48:33 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:45:59 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void	ft_gui_draw_map_grid_limit_sector(t_wolf3d *w, t_gui_elem *elem,
**	t_vector3 v, int type)
**
**	Function that fill limit sector for map grid.
** **************************************************************************
*/

void	ft_gui_draw_map_grid_limit_sector(t_wolf3d *w, t_gui_elem *elem, \
			t_vector3 v, int type)
{
	t_gui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, v);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_TR)
		ft_gui_fill_area(w,
			(t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
			(t_gui_coord){elem->v2.x, \
			(pos.y > elem->v2.y ? elem->v2.y : pos.y), 0},
			0x120000);
	else
		ft_gui_fill_area(w,
			(t_gui_coord){elem->v1.x, \
			(pos.y < elem->v1.y ? elem->v1.y : pos.y), 0},
			(t_gui_coord){elem->v2.x, elem->v2.y, 0}, 0x120000);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_BL)
		ft_gui_fill_area(w,
			(t_gui_coord){elem->v1.x, elem->v1.y, 0}, \
			(t_gui_coord){(pos.x > elem->v2.x ? elem->v2.x : pos.x), \
			elem->v2.y, 0},
			0x120000);
	else
		ft_gui_fill_area(w,
			(t_gui_coord){(pos.x < elem->v1.x ? elem->v1.x : pos.x), \
			elem->v1.y, 0},
			(t_gui_coord){elem->v2.x, elem->v2.y, 0}, 0x120000);
}

/*
** **************************************************************************
**	void ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_elem *elem,
**		t_vector3 v, int scale)
**
**	Function that draw limit line for map grid.
** **************************************************************************
*/

void	ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_elem *elem, \
			t_vector3 v)
{
	t_gui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, v);
	if (pos.y >= elem->v1.y && pos.y <= elem->v2.y)
		ft_fdf_wu_color(
			&(t_vector3){elem->v1.x, pos.y, 0, 0}, \
			&(t_vector3){elem->v2.x, pos.y, 0, 0}, \
			w, 0x888888);
	if (pos.x >= elem->v1.x && pos.x <= elem->v2.x)
		ft_fdf_wu_color(
			&(t_vector3){pos.x, elem->v1.y, 0, 0}, \
			&(t_vector3){pos.x, elem->v2.y, 0, 0}, \
			w, 0x888888);
}

/*
** **************************************************************************
**	void ft_gui_draw_map_grid(t_wolf3d *w, t_gui_elem *elem, int scale)
**
**	Function that draw map grid.
** **************************************************************************
*/

void	ft_gui_draw_map_grid(t_wolf3d *w, t_gui_elem *elem, int scale)
{
	t_gui_coord	pos;
	t_gui_coord	vrtx;

	vrtx = (t_gui_coord){(int)floor(w->gui_map.v.x), \
		(int)floor(w->gui_map.v.y), 0};
	pos = ft_gui_map_vertex_to_coord(w, \
		(t_vector3){floor(vrtx.x), floor(vrtx.y), 0, 0});
	while (pos.y < elem->v2.y && pos.y < WIN_HEIGHT)
	{
		if (!(vrtx.y % 10))
			ft_fdf_wu_color(
				&(t_vector3){elem->v1.x, pos.y, 0, 0}, \
				&(t_vector3){elem->v2.x, pos.y, 0, 0}, \
				w, 0x666666);
		else if (!(vrtx.y % 2))
		{
			ft_fdf_wu_color(
				&(t_vector3){elem->v1.x, pos.y, 0, 0}, \
				&(t_vector3){elem->v2.x, pos.y, 0, 0}, \
				w, 0x333333);
		}
		else
			ft_fdf_wu_color(
				&(t_vector3){elem->v1.x, pos.y, 0, 0}, \
				&(t_vector3){elem->v2.x, pos.y, 0, 0}, \
				w, 0x222222);
		pos.y += w->gui_map.grid_scale;
		vrtx.y++;
	}
	while (pos.x < elem->v2.x && pos.x < WIN_WIDTH)
	{
		if (!(vrtx.x % 10))
			ft_fdf_wu_color(
				&(t_vector3){pos.x, elem->v1.y, 0, 0}, \
				&(t_vector3){pos.x, elem->v2.y, 0, 0}, \
				w, 0x666666);
		else if (!(vrtx.x % 2))
		{
			ft_fdf_wu_color(
				&(t_vector3){pos.x, elem->v1.y, 0, 0}, \
				&(t_vector3){pos.x, elem->v2.y, 0, 0}, \
				w, 0x333333);
		}
		else
			ft_fdf_wu_color(
				&(t_vector3){pos.x, elem->v1.y, 0, 0}, \
				&(t_vector3){pos.x, elem->v2.y, 0, 0}, \
				w, 0x222222);
		pos.x += w->gui_map.grid_scale;
		vrtx.x++;
	}
}
