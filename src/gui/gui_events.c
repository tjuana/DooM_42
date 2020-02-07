/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:44:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/05 18:09:45 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	void ft_gui_events(t_wolf3d *w)
**	
**	Function that get events and call necessary functions.
*/

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
		if (e.type == SDL_KEYDOWN)
		{
			(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? w->sdl->running = 0 : 0;
			if (w->gui.focus_elem != NULL)
				ft_gui_focus_keydown(w, e, w->gui.focus_elem);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				ft_gui_mousebuttondown(w, e, w->gui.dom);
		}
		if (e.type == SDL_MOUSEWHEEL)
			ft_gui_mousewheel(w, e, w->gui.dom);
		if (e.type == SDL_MOUSEBUTTONUP)
			ft_gui_mousebuttonup(w, e, w->gui.dom);
		// if (e.type == SDL_MOUSEMOTION)
		// 	ft_gui_mousemotion(w, e, w->gui.dom);
	}
	if (w->gui.search_elem == GUI_EVENT_ON || \
		w->gui.search_elem == GUI_EVENT_SEARCH)
	{
		ft_gui_redraw(w);
		w->gui.search_elem = GUI_EVENT_OFF;
	}
}