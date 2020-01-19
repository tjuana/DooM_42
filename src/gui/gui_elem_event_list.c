/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_event_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:41:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 16:30:22 by dorange-         ###   ########.fr       */
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
	// ft_gui_print_element_list(w->gui.dom, 0);
	w->gui.mode = GUI_MD_ME_SET_SECTOR;
}

void	ft_gui_mousebuttonup_win_setsector_btn_cancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsector"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	// ft_gui_print_element_list(w->gui.dom, 0);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setplayer_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setsprite_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_setenemy_btncancel(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME;
}

void	ft_gui_mousebuttonup_win_menu_btn_player(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setplayer"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
}

void	ft_gui_mousebuttonup_win_menu_btn_sprite(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setsprite"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_SPRITE;
}

void	ft_gui_mousebuttonup_in_menu_btn_enemy(void *data, SDL_Event e, t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list	*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_menu"), GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, "win_setenemy"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_ENEMY;
}