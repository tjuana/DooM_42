/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_zoom.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:33:29 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 13:47:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void	ft_gui_mousewheel_win_map(void *data, SDL_Event e, \
**				t_list *dom, int type)
**
**	Function that transform map status for mousewheel event.
** **************************************************************************
*/

void	ft_gui_mousewheel_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_vector3	new_offset;
	t_vector3	old_offset;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	old_offset = ft_gui_map_coord_to_vertex(w, w->gui.mouse_pos);
	if (e.wheel.y > 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale - 1 < 8) ? \
			8 : w->gui_map.grid_scale - 2;
	else if (e.wheel.y < 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale + 1 > 64) ? \
			64 : w->gui_map.grid_scale + 2;
	new_offset = ft_gui_map_coord_to_vertex(w, w->gui.mouse_pos);
	w->gui_map.v = (t_vector3){
		w->gui_map.v.x - new_offset.x + old_offset.x, \
		w->gui_map.v.y - new_offset.y + old_offset.y, \
		0, 0};
	return ;
}
