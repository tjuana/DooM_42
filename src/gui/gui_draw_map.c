/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/17 20:30:00 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	t_vector3 ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_rect rect, t_ui_coord c)
**	
**	Function that convert vertex to screen coordinate.
*/
t_vector3	ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_rect rect, t_ui_coord c)
{
	t_vector3	v;

	v = (t_vector3){0, 0, 0, 0};
	v.x = (double)(c.x - rect.v1.x) / w->gui_map.grid_scale + w->gui_map.v.x;
	v.y = (double)(c.y - rect.v1.y) / w->gui_map.grid_scale + w->gui_map.v.y;
	return (v);
}

/*
**	t_ui_coord ft_gui_map_vertex_to_coord(t_wolf3d *w, t_gui_rect rect, t_vector3 v)
**	
**	Function that convert vertex to screen coordinate.
*/
t_ui_coord	ft_gui_map_vertex_to_coord(t_wolf3d *w, t_gui_rect rect, t_vector3 v)
{
	t_ui_coord	c;

	c = (t_ui_coord){0, 0, 0};
	c.x = (v.x - w->gui_map.v.x) * w->gui_map.grid_scale + rect.v1.x;
	c.y = (v.y - w->gui_map.v.y) * w->gui_map.grid_scale + rect.v1.y;
	return (c);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw limit line for map grid.
*/
void	ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_rect rect, t_vector3 v, int scale)
{
	t_ui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, v);
	ft_fdf_wu_color(
		&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
		&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
		w, 0x888888 \
	);
	ft_fdf_wu_color(
		&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
		&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
		w, 0x888888 \
	);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map grid.
*/
void	ft_gui_draw_map_grid(t_wolf3d *w, t_gui_rect rect, int scale)
{
	t_ui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, \
		(t_vector3){floor(w->gui_map.v.x), floor(w->gui_map.v.y), 0, 0});
	while (pos.y < rect.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
			&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.y += w->gui_map.grid_scale;
	}
	while (pos.x < rect.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
			&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.x += w->gui_map.grid_scale;
	}
}

int		ft_gui_draw_map_vertex(t_wolf3d *w, t_ui_coord c, int status)
{
	int	v_d;
	int	color;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	if (status == 1 && w->gui.mode != GUI_MD_ME)
	{
		color = GUI_CL_STANDART;
		if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
			color = GUI_CL_SECTOR;
		if (w->gui.mode == GUI_MD_ME_SET_PLAYER)
			color = GUI_CL_PLAYER;
		if (w->gui.mode == GUI_MD_ME_SET_SPRITE)
			color = GUI_CL_SPRITE;
		if (w->gui.mode == GUI_MD_ME_SET_ENEMY)
			color = GUI_CL_ENEMY;
		ft_gui_fill_area(w, (t_ui_coord){c.x - v_d, c.y - v_d, 0}, \
			(t_ui_coord){c.x + v_d, c.y + v_d, 0}, color);

	}
	return (0);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map.
*/
void	ft_gui_draw_map(t_wolf3d *w, t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	ft_gui_draw_map_grid(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, (t_vector3){0, 0, 0, 0}, w->gui_map.grid_scale);
	w->gui_map.check_vertex = ft_gui_draw_map_vertex(w, w->gui.mouse_pos, \
		w->gui_map.check_vertex);
}