/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_menu.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:12:57 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:39:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_gui_mousebuttonup_win_menu_btnsector(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(\
		w->gui.dom, "win_me_sctr"), GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_SECTOR;
	w->sector_status = 0;
	if (w->sector_status == 0)
	{
		ft_editor_sector_create(w);
		w->sector_count++;
		w->sector_status = 1;
	}
}

void	ft_gui_mousebuttonup_win_menu_btnplayer(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_pl"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_PLAYER;
	w->player_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnsprite(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_sprt"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_SPRITE;
	w->sprite_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btnenemy(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_enemy"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_ENEMY;
	w->enemy_status = 0;
}

void	ft_gui_mousebuttonup_win_menu_btndoor(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_list		*list;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_menu"), \
		GUI_ELEM_HIDDEN);
	ft_gui_elem_set_status(\
		ft_gui_search_elem_by_name(w->gui.dom, "win_me_door"), \
		GUI_ELEM_VISIBLE);
	w->gui.mode = GUI_MD_ME_SET_DOOR;
	w->door_status = 0;
	ft_create_sector_door(w);
}
