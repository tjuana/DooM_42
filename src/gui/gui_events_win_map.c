/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events_win_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:43:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/17 16:22:04 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

/*
**	void ft_gui_mousemotion_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousemotuin event.
*/
void	ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;
	t_ui_coord	coord;

	w = (t_wolf3d*)data;
	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content);
	if (coord.w)
	{
		w->gui.mouse_pos = coord;
		w->gui_map.check_vertex = 1;
	}
	return ;
}

/*
**	void ft_gui_mousebuttondown_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousebuttondown event.
*/
void	ft_gui_mousebuttondown_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	return ;
}

/*
**	void ft_gui_mousebuttonup_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousebuttonup event.
*/
void	ft_gui_mousebuttonup_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	return ;
}

/*
**	void ft_gui_mousewheel_win_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousewheel event.
*/
void	ft_gui_mousewheel_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_vector3	new_offset;
	t_vector3	old_offset;
	t_vector3	v;

	w = (t_wolf3d*)data;
	if (e.wheel.y > 0)
	{
		old_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);
		w->gui_map.grid_scale = (w->gui_map.grid_scale - 1 < 8) ? 8 : w->gui_map.grid_scale - 2;
		new_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);
		w->gui_map.v = (t_vector3){
			w->gui_map.v.x - new_offset.x + old_offset.x, \
			w->gui_map.v.y - new_offset.y + old_offset.y, \
			0, 0
		};
	}
	else if(e.wheel.y < 0)
	{
		old_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);
		w->gui_map.grid_scale = (w->gui_map.grid_scale + 1 > 64) ? 64 : w->gui_map.grid_scale + 2;
		new_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);
		w->gui_map.v = (t_vector3){
			w->gui_map.v.x - new_offset.x + old_offset.x, \
			w->gui_map.v.y - new_offset.y + old_offset.y, \
			0, 0
		};
	}
	return ;
}