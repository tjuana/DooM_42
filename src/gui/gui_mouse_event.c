/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mouse_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:30:13 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 15:32:47 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_gui_event_call_func(t_wolf3d *w, SDL_Event e,
**		t_gui_event *event, int type)
**
**	Function that call event function.
** **************************************************************************
*/

int		ft_gui_event_call_func(t_wolf3d *w, SDL_Event e, \
			t_gui_event *event, int type)
{
	event->func(w, e, event->elem, type);
	return (1);
}

/*
** **************************************************************************
**	int ft_gui_event_action(t_wolf3d *w, SDL_Event e, t_list *dom)
**
**	Function that set status for gui hover element for mouse_move event.
** **************************************************************************
*/

int		ft_gui_event_action(t_wolf3d *w, SDL_Event e, t_list *dom, int type)
{
	t_gui_elem	*elem;
	t_gui_event	*event;
	t_list		*event_list;

	elem = dom->content;
	event_list = elem->events;
	while (event_list)
	{
		event = event_list->content;
		if (event->type == type)
			return (ft_gui_event_call_func(w, e, event, type));
		event_list = event_list->next;
	}
	return (0);
}

/*
** **************************************************************************
**	void ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, t_list *dom)
**
**	Function that search elem for mouse_move event action.
** **************************************************************************
*/

int		ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, \
			t_list *dom, int type)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	if (list != NULL)
	{
		elem = list->content;
		if (ft_gui_check_event_elem_area(w->gui.mouse_pos, elem) && \
			elem->status & GUI_ELEM_VISIBLE)
		{
			ft_gui_event_search_elem(w, e, elem->child, type);
			if (w->gui.search_elem == GUI_EVENT_SEARCH)
			{
				if (ft_gui_event_action(w, e, list, type))
					w->gui.search_elem = GUI_EVENT_ON;
				else
				{
					if (!(w->gui.search_elem & GUI_ELEM_FOCUS))
						ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
				}
			}
		}
		ft_gui_event_search_elem(w, e, list->next, type);
	}
	return (0);
}
