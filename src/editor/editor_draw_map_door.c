/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_door.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 21:40:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_draw_area_hatch(t_wolf3d *w, t_gui_rect rect, int color)
**
**	Function that draw area hatch.
** **************************************************************************
*/

void	ft_draw_area_hatch(t_wolf3d *w, t_gui_rect rect, int color)
{
	t_gui_coord	v;
	t_gui_coord	c;
	t_vector3	vec;
	vec = (t_vector3){1, 0, 0, 0};
	vec = ft_transform_vertex(vec, \
		ft_rz_matrix((t_matrix_4x4){1, 0, 0, 0}, -M_PI_4));
	v.y = rect.v1.y >= 0 ? rect.v1.y : 0;
	while (v.y + w->gui_map.grid_scale <= rect.v2.y && v.y < WIN_HEIGHT)
	{
		v.x = rect.v1.x >= 0 ? rect.v1.x : 0;
		while (v.x + w->gui_map.grid_scale <= rect.v2.x && v.x < WIN_WIDTH)
		{
			c.x = v.x + w->gui_map.grid_scale;
			c.y = v.y + w->gui_map.grid_scale;
			ft_fdf_wu_rect_color(w, (t_gui_rect){v, c, 0, 0}, rect, color);
			v.x += w->gui_map.grid_scale;
		}
		v.y += w->gui_map.grid_scale;
	}
}

/*
** **************************************************************************
**	t_gui_rect ft_sector_get_rect(t_wolf3d *w, t_sector *s)
**
**	Function that get sector area.
** **************************************************************************
*/

t_gui_rect	ft_sector_get_rect(t_wolf3d *w, t_sector *s)
{
	t_vector3	v1;
	t_vector3	v2;
	t_gui_rect	rect;
	int			i;

	if (s->vertex_count == 0)
		return ((t_gui_rect){0, 0, 0, 0});
	rect = (t_gui_rect){0, 0, 0, 0};
	v1 = *s->vertex[0];
	v2 = *s->vertex[0];
	i = 1;
	while (i < s->vertex_count)
	{
		(s->vertex[i]->x < v1.x) ? v1.x = s->vertex[i]->x : 0;
		(s->vertex[i]->x > v2.x) ? v2.x = s->vertex[i]->x : 0;
		(s->vertex[i]->y < v1.y) ? v1.y = s->vertex[i]->y : 0;
		(s->vertex[i]->y > v2.y) ? v2.y = s->vertex[i]->y : 0;
		i++;
	}
	rect.v1 = ft_gui_map_vertex_to_coord(w, v1);
	rect.v2 = ft_gui_map_vertex_to_coord(w, v2);
	rect.w = v2.x - v1.x;
	rect.h = v2.y - v2.x;
	return (rect);
}

/*
** **************************************************************************
**	void ft_editor_draw_door(t_wolf3d *w, t_sector *s)
**
**	Function that draw door for editor map.
** **************************************************************************
*/

void	ft_editor_draw_door(t_wolf3d *w, t_sector *s)
{
	if (s->status == SECTOR_STATUS_READY || \
		s->status == SECTOR_STATUS_PRESET ||
		s->status == SECTOR_STATUS_SET)
	{
		s->color = GUI_CL_DOOR;
		ft_draw_sector_walls(w, s);
	}
	if (s->status == SECTOR_STATUS_PRESET ||
		s->status == SECTOR_STATUS_SET)
		ft_draw_area_hatch(w, ft_sector_get_rect(w, s), s->color);
}
