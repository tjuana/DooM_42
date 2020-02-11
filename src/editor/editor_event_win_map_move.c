/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_move.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:38:48 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 17:44:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void	ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
**				t_list *dom, int type)
**
**	Function that transform map status for mousemotuin event.
** **************************************************************************
*/

void	ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_coord	coord;

	w = (t_wolf3d*)data;
	if (w->gui.mode == GUI_MD_ME_SET_DOOR)
		ft_gui_mousemotion_win_map_door(w, e, dom);
	else
	{
		coord = ft_gui_map_check_mouse_vertex_pos(w, \
			w->gui.mouse_pos, dom->content);
		if (coord.w && ft_new_editor_map_check_area(w))
		{
			w->gui.mouse_pos = coord;
			w->gui_map.check_vertex = 1;
		}
	}
	return ;
}
