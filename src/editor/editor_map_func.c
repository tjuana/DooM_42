/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:36:39 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/13 16:25:10 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_map_check_straight_line(t_vector3 v1, t_vector3 v2)
**
**	Function that check straight perpendicular line.
** **************************************************************************
*/

int			ft_map_check_straight_line(t_vector3 v1, t_vector3 v2)
{
	return (v1.x == v2.x || v1.y == v2.y);
}

/*
** **************************************************************************
**	t_vector3 ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_coord c)
**
**	Function that convert vertex to screen coordinate.
** **************************************************************************
*/

t_vector3	ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_coord c)
{
	t_vector3	v;
	t_gui_elem	*elem;

	elem = w->gui_map.ptr->content;
	v = (t_vector3){0, 0, 0, 0};
	v.x = (double)(c.x - elem->v1.x) / w->gui_map.grid_scale + w->gui_map.v.x;
	v.y = (double)(c.y - elem->v1.y) / w->gui_map.grid_scale + w->gui_map.v.y;
	return (v);
}

/*
** **************************************************************************
**	t_gui_coord ft_gui_map_vertex_to_coord(t_wolf3d *w, t_vector3 v)
**
**	Function that convert vertex to screen coordinate.
** **************************************************************************
*/

t_gui_coord	ft_gui_map_vertex_to_coord(t_wolf3d *w, t_vector3 v)
{
	t_gui_coord	c;
	t_gui_elem	*elem;

	elem = w->gui_map.ptr->content;
	c = (t_gui_coord){0, 0, 0};
	c.x = (v.x - w->gui_map.v.x) * w->gui_map.grid_scale + elem->v1.x;
	c.y = (v.y - w->gui_map.v.y) * w->gui_map.grid_scale + elem->v1.y;
	return (c);
}

/*
** **************************************************************************
**	t_gui_coord	ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_gui_coord c, \
**	t_gui_elem *elem)
**
**	Function that check mouse position (for map!!!)
** **************************************************************************
*/

t_gui_coord	ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_gui_coord c, \
	t_gui_elem *elem)
{
	t_vector3	mp_vertex;

	mp_vertex = ft_gui_map_coord_to_vertex(w, c);
	if (mp_vertex.x < w->gui_map.r1.x || mp_vertex.x > w->gui_map.r2.x ||
		mp_vertex.y < w->gui_map.r1.y || mp_vertex.y > w->gui_map.r2.y)
		return ((t_gui_coord){0, 0, 0});
	if ((c.x <= elem->v1.x || c.x > elem->v2.x) ||
		(c.y <= elem->v1.y || c.y > elem->v2.y))
		return ((t_gui_coord){0, 0, 0});
	ft_help_check_mouse_ver(w, c);
	if (w->pos.x < (-1.0 / w->v_d) || w->pos.y < (-1.0 / w->v_d))
		return ((t_gui_coord){0, 0, 0});
	if ((w->offset.x < w->v_d || w->offset.x > w->gui_map.grid_scale - w->v_d) \
	&& (w->offset.y < w->v_d || w->offset.y > w->gui_map.grid_scale - w->v_d))
	{
		c = ft_gui_map_vertex_to_coord(w, \
			(t_vector3){\
				(c.x - w->pos_start.x) / w->gui_map.grid_scale +\
				(w->offset.x > w->gui_map.grid_scale - w->v_d), \
				(c.y - w->pos_start.y) / w->gui_map.grid_scale + \
				(w->offset.y > w->gui_map.grid_scale - w->v_d), 0, 0});
		c.w = 1;
		return (c);
	}
	return ((t_gui_coord){0, 0, 0});
}

void		ft_help_check_mouse_ver(t_wolf3d *w, t_gui_coord c)
{
	w->v_d = (w->gui_map.grid_scale / 8) < 4 ? 4 : (w->gui_map.grid_scale / 8);
	w->pos_start = ft_gui_map_vertex_to_coord(w, (t_vector3){0, 0, 0, 0});
	w->offset = (t_gui_coord){0, 0, 0};
	w->offset.x = (c.x - w->pos_start.x) % w->gui_map.grid_scale;
	w->offset.y = (c.y - w->pos_start.y) % w->gui_map.grid_scale;
	w->pos = (t_vector3){0, 0, 0, 0};
	w->pos.x = (double)(c.x - w->pos_start.x) / w->gui_map.grid_scale;
	w->pos.y = (double)(c.y - w->pos_start.y) / w->gui_map.grid_scale;
}
