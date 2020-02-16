/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_setsprite.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:22:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:44:26 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_setsprite_btnsaveplayer(void *data, \
			SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_sprt"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setsprite_btncancel(void *data, \
			SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_sprt"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
	if (w->sprite == NULL)
		return ;
	if (w->sprite_status == 0 && ((t_sector*)w->sprite->content)->status == 1)
		return ;
	ft_delete_sprite(w);
}
