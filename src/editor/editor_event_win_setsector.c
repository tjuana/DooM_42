/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_setsector.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:17:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/15 13:26:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_setsector_btnsavemap(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*s;

	w = (t_wolf3d*)data;
	s = w->sector->content;
	if (s->status != SECTOR_STATUS_POLYGON && s->status != SECTOR_STATUS_READY)
		return ;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_sctr"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	w->sector_status = 0;
	s->height = ft_atoi(ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, \
			"win_me_sctr_inputh")));
	s->floor = ft_atoi(ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, \
			"win_me_sctr_inputf")));
	ft_map_set_new_sector(w, s);
}

void	ft_gui_mousebuttonup_win_setsector_btncancel(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_sctr"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sector == NULL)
		return ;
	if (w->sector_status == 0 && ((t_sector*)w->sector->content)->status == 1)
		return ;
	ft_delete_sector(w);
	w->sector_status = 0;
}
