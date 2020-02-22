/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_click.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:02:36 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:16:26 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
**
**	Function that call function for set sector or objects.
** **************************************************************************
*/

void	ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
		ft_gui_event_set_sector(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_PLAYER)
		ft_gui_event_set_player(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_SPRITE)
		ft_gui_event_set_sprite(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_ENEMY)
		ft_gui_event_set_enemy(w, e, elem);
}

/*
** **************************************************************************
**	void ft_gui_mousebuttondown_map(void *data, SDL_Event e, t_list *dom,
**	int type)
**
**	Function that transform map status for mousebuttondown event.
** **************************************************************************
*/

void	ft_gui_mousebuttondown_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_coord	coord;

	(void)e;
	(void)type;
	w = (t_wolf3d*)data;
	coord = ft_gui_map_check_mouse(w, w->gui.mouse_pos, \
		dom->content);
	if (coord.w)
	{
		w->gui.mouse_pos = coord;
		ft_gui_mouse_click_map(w, e, dom);
	}
	return ;
}

/*
** **************************************************************************
**	void ft_gui_mousebuttonup_map(void *data, SDL_Event e,
**		t_list *dom, int type)
**
**	Function that transform map status for mousebuttonup event.
** **************************************************************************
*/

void	ft_gui_mousebuttonup_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)dom;
	(void)type;
	w = (t_wolf3d*)data;
	return ;
}
