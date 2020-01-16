/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_event_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:41:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/16 15:30:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	[!] [TEMPORARY]
**	
**	It's temporary list with some events.
*/

#include "wolf3d.h"

void	ft_gui_mousebuttonup_win_menu_btn_sector(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_VISIBLE);

}

void	ft_gui_mousebuttonup_win_setsector_btn_cancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
}
