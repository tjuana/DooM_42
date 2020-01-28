/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_btn_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:48:07 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/28 18:13:21 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_menu_btngame(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_game"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_GAME;
	w->player_status = 0;
	SDL_ShowCursor(SDL_DISABLE);
}

void	ft_gui_mousebuttonup_win_menu_btneditor(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_editor"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
	w->player_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnexit(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	// ft_gui_elem_set_status(\
	// 	ft_gui_search_elem_by_name(w->gui.dom, "win_editor_menu"), \
	// 	GUI_ELEM_HIDDEN);
	// ft_gui_elem_set_status(\
	// 	ft_gui_search_elem_by_name(w->gui.dom, "win_editor_setplayer"), \
	// 	GUI_ELEM_VISIBLE);
	// w->gui.mode = GUI_MD_ME_SET_PLAYER;
	// w->player_status = 0;
}
