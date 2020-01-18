/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_map_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:36:39 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/18 20:06:23 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	t_vector3 ft_gui_map_coord_to_vertex(t_wolf3d *w, t_gui_rect rect, t_ui_coord c)

**	Function that convert vertex to screen coordinate.
** **************************************************************************
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
** **************************************************************************
**	t_ui_coord ft_gui_map_vertex_to_coord(t_wolf3d *w, t_gui_rect rect, t_vector3 v)

**	Function that convert vertex to screen coordinate.
** **************************************************************************
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
** **************************************************************************
**	t_ui_coord	ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_ui_coord c, t_gui_elem *elem)

**	Function that check mouse position (for map!!!)
** **************************************************************************
*/
t_ui_coord	ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_ui_coord c, \
	t_gui_elem *elem)
{
	t_vector3	pos;
	t_ui_coord	pos_start;
	t_ui_coord	offset;
	int			v_d;

	if ((c.x <= elem->v1.x || c.x > elem->v2.x) ||
		(c.y <= elem->v1.y || c.y > elem->v2.y))
		return ((t_ui_coord){0, 0, 0});

	v_d = (w->gui_map.grid_scale / 8) < 4 ? 4 : (w->gui_map.grid_scale / 8);

	pos_start = ft_gui_map_vertex_to_coord(w, (t_gui_rect){elem->v1, elem->v2, \
		elem->w, elem->h}, (t_vector3){0, 0, 0, 0});

	offset = (t_ui_coord){0, 0, 0};
	offset.x = (c.x - pos_start.x) % w->gui_map.grid_scale;
	offset.y = (c.y - pos_start.y) % w->gui_map.grid_scale;

	pos = (t_vector3){0, 0, 0, 0};
	pos.x = (double)(c.x - pos_start.x) / w->gui_map.grid_scale;
	pos.y = (double)(c.y - pos_start.y) / w->gui_map.grid_scale;

	if (pos.x < (-1.0 / v_d) || pos.y < (-1.0 / v_d))
		return ((t_ui_coord){0, 0, 0});

	if (
		(offset.x < v_d || offset.x > w->gui_map.grid_scale - v_d) &&
		(offset.y < v_d || offset.y > w->gui_map.grid_scale - v_d)
	)
	{
		c = ft_gui_map_vertex_to_coord(w, \
			(t_gui_rect){elem->v1, elem->v2, elem->w, elem->h}, \
			(t_vector3){\
				(c.x - pos_start.x) / w->gui_map.grid_scale + (offset.x > w->gui_map.grid_scale - v_d), \
				(c.y - pos_start.y) / w->gui_map.grid_scale + (offset.y > w->gui_map.grid_scale - v_d), \
				0, 0
			}
		);
		c.w = 1;
		return (c);
	}
	return ((t_ui_coord){0, 0, 0});
}