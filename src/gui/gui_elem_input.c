/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:25:10 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:41:43 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_mousemotion_input(void *data, SDL_Event e,
**		t_list *dom, int type)
**
**	Function that transform input status for mousemotuin event.
** **************************************************************************
*/

void	ft_gui_mousemotion_input(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	elem = dom->content;
	if (!(elem->status & GUI_ELEM_FOCUS))
		ft_gui_elem_set_status(dom, GUI_ELEM_HOVER);
}

/*
** **************************************************************************
**	void ft_gui_mousebuttondown_input(void *data, SDL_Event e,
**		t_list *dom, int type)
**
**	Function that transform input status for mousebuttondown event.
** **************************************************************************
*/

void	ft_gui_mousebuttondown_input(void *data, SDL_Event e, \
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
**	void ft_gui_mousebuttonup_input(void *data, SDL_Event e,
**		t_list *dom, int type)
**
**	Function that transform input status for mousebuttonup event.
** **************************************************************************
*/

void	ft_gui_mousebuttonup_input(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	(void)e;
	(void)type;
	(void)dom;
	w = (t_wolf3d*)data;
	ft_gui_delete_status_focus(w->gui.dom);
	w->gui.focus_elem = NULL;
	ft_gui_elem_set_status(dom, GUI_ELEM_FOCUS);
	w->gui.focus_elem = dom;
}
