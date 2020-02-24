/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:39:41 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:41:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_mousemotion_button(void *data, SDL_Event e,
**		t_list *dom, int type)
**
**	Function that transform button status for mousemotuin event.
** **************************************************************************
*/

void	ft_gui_mousemotion_button(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	elem = dom->content;
	ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}

/*
** **************************************************************************
**	void ft_gui_mousebuttondown_button(void *data, SDL_Event e,
**	t_list *dom, int type)
**
**	Function that transform button status for mousebuttondown event.
** **************************************************************************
*/

void	ft_gui_mousebuttondown_button(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	ft_gui_elem_set_status(dom, GUI_ELEM_ACTIVE);
}

/*
** **************************************************************************
**	void ft_gui_mousebuttonup_button(void *data, SDL_Event e,
**	t_list *dom, int type)
**
**	Function that transform button status for mousebuttonup event.
** **************************************************************************
*/

void	ft_gui_mousebuttonup_button(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	ft_gui_delete_status_focus(w->gui.dom);
	w->gui.focus_elem = NULL;
	ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}

/*
** **************************************************************************
**	void ft_gui_mousebuttonup_block(void *data, SDL_Event e,
**	t_list *dom, int type)
**
**	Function that transform block status for mousemotuin event.
** **************************************************************************
*/

void	ft_gui_mousebuttonup_block(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	ft_gui_delete_status_focus(w->gui.dom);
	w->gui.focus_elem = NULL;
}
