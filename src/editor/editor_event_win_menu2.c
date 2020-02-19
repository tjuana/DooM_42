/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_menu2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:16:02 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:39:47 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_menu_btnsavemap(\
			void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	w->file.name = ft_gui_elem_get_value(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu_name"));
	ft_save_the_file(w);
}

void	ft_gui_mousebuttonup_win_editor_menu_btnmenu(\
			void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
	w->player_status = 0;
}
