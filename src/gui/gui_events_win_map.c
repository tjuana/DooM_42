/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events_win_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:43:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/16 22:05:54 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ui_coord	ft_gui_map_check_mouse_vertex_pos(t_wolf3d *w, t_ui_coord c, \
	t_gui_elem *elem)
{
	t_ui_coord	pos_start;
	t_ui_coord	pos;
	int			v_d;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	if ((c.x <= elem->v1.x || c.x > elem->v2.x) ||
		(c.y <= elem->v1.y || c.y > elem->v2.y))
		return ((t_ui_coord){0, 0, 0});

	pos_start = (t_ui_coord){0, 0, 0};
	pos_start.x -= w->gui_map.v.x * w->gui_map.grid_scale;
	pos_start.y -= w->gui_map.v.y * w->gui_map.grid_scale;

	pos = (t_ui_coord){0, 0, 0};
	pos.x = (c.x - pos_start.x) % w->gui_map.grid_scale;
	pos.y = (c.y - pos_start.y) % w->gui_map.grid_scale;

	if (
		(pos.x < v_d || pos.x > w->gui_map.grid_scale - v_d) &&
		(pos.y < v_d || pos.y > w->gui_map.grid_scale - v_d)
	)
		pos.x = (c.x - pos_start.x) / w->gui_map.grid_scale;
		pos.y = (c.y - pos_start.y) / w->gui_map.grid_scale;
		// return ((t_ui_coord){c.x, \
		// 	c.y, 1});
		return ((t_ui_coord){pos_start.x + pos.x * w->gui_map.grid_scale, \
			pos_start.y + pos.y * w->gui_map.grid_scale, 1});
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

	w = (t_wolf3d*)data;
	if (e.wheel.y > 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale - 1 < 8) ? 8 : w->gui_map.grid_scale - 2;
	else if(e.wheel.y < 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale + 1 > 64) ? 64 : w->gui_map.grid_scale + 2;
	return ;
}