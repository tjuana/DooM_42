/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_setdoor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:22:48 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/27 20:59:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_setdoor_btnsave(void *data, \
			SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;
	t_sector	*s;

	w = (t_wolf3d*)data;
	s = w->sector->content;
	ft_map_set_new_sector(w, s);

	s->status = SECTOR_STATUS_SET;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_setdoor"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setdoor_btncancel(void *data, \
			SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_setdoor"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sector == NULL)
		return ;
	if (w->door_status == 0 && ((t_sector*)w->sector->content)->status == 1)
		return ;
	ft_delete_sector(w);
	w->door_status = 0;
}