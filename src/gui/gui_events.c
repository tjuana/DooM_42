/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:44:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 12:52:46 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_events(t_wolf3d *w)
**
**	Function that handle user mouse events.
** **************************************************************************
*/

void	ft_gui_events_mouse(t_wolf3d *w, SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
			ft_gui_mousebuttondown(w, *e, w->gui.dom);
	}
	if (e->type == SDL_MOUSEWHEEL)
		ft_gui_mousewheel(w, *e, w->gui.dom);
	if (e->type == SDL_MOUSEBUTTONUP)
		ft_gui_mousebuttonup(w, *e, w->gui.dom);
	if (e->type == SDL_MOUSEMOTION)
		ft_gui_mousemotion(w, *e, w->gui.dom);
}

void	ft_gui_events_keydown(t_wolf3d *w, SDL_Event *e)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (w->gui.mode == GUI_MD_ME)
		{
			(e->key.keysym.scancode == SDL_SCANCODE_S) ? \
				ft_gui_mousebuttonup_win_menu_btnsector(w, *e, \
				w->gui.dom, 0) : 0;
			(e->key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? \
				ft_gui_mousebuttonup_win_editor_menu_btnmenu(w, *e, \
				w->gui.dom, 0) : 0;
			(e->key.keysym.scancode == SDL_SCANCODE_0) ? \
				ft_me_generate_triangles(w) : 0;
			ft_gui_redraw(w);
		}
		else if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
		{
			(e->key.keysym.scancode == SDL_SCANCODE_SPACE) ? \
				ft_gui_mousebuttonup_win_setsector_btnsavemap(w, *e, \
				w->gui.dom, 0) : 0;
			(e->key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? \
				ft_gui_mousebuttonup_win_setsector_btncancel(w, *e, \
				w->gui.dom, 0) : 0;
			ft_gui_redraw(w);
		}
		else
		{
			(e->key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? \
				w->sdl->running = 0 : 0;
		}
		if (w->gui.focus_elem != NULL)
			ft_gui_focus_keydown(w, *e, w->gui.focus_elem);
	}
}

/*
** **************************************************************************
**	void ft_gui_events(t_wolf3d *w)
**
**	Function that handle user events.
** **************************************************************************
*/

void	ft_gui_events(t_wolf3d *w)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		e.type == SDL_QUIT ? w->sdl->running = 0 : 0;
		ft_gui_events_keydown(w, &e);
		ft_gui_events_mouse(w, &e);
	}
	if (w->gui.search_elem == GUI_EVENT_ON || \
		w->gui.search_elem == GUI_EVENT_SEARCH)
	{
		ft_gui_redraw(w);
		w->gui.search_elem = GUI_EVENT_OFF;
	}
}
