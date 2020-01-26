/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:58:53 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 21:40:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	int ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
**	
**	Function that check event area.
*/
int		ft_gui_check_event_area(t_gui_coord v, t_gui_coord v1, t_gui_coord v2)
{
	return (v.x >= v1.x && v.x < v2.x \
		&& v.y >= v1.y && v.y < v2.y);
}

/*
**	int ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
**	
**	Function that check event area.
*/
int		ft_gui_check_event_elem_area(t_gui_coord v, t_gui_elem *c)
{
	return (v.x >= c->v1.x && v.x < c->v2.x \
		&& v.y >= c->v1.y && v.y < c->v2.y && c->status);
}

/*
**	void ft_gui_init_mouse_pos(t_wolf3d *w)
**	
**	Function that initialize mouse position.
*/
void	ft_gui_init_mouse_pos(t_wolf3d *w)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	w->gui.mouse_pos = (t_gui_coord){x, y, 0};
}

/*
**	int ft_gui_event_call_func(t_wolf3d *w, SDL_Event e,
**		t_gui_event *event, int type)
**	
**	Function that call event function.
*/
int		ft_gui_event_call_func(t_wolf3d *w, SDL_Event e, \
			t_gui_event *event, int type)
{
	event->func(w, e, event->elem, type);
	return (1);
}

/*
**	int ft_gui_event_action(t_wolf3d *w, SDL_Event e, t_list *dom)
**	
**	Function that set status for gui hover element for mouse_move event.
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
**	void ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, t_list *dom)
**	
**	Function that search elem for mouse_move event action.
*/
int		ft_gui_event_search_elem(t_wolf3d *w, SDL_Event e, t_list *dom, int type)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	if (list != NULL)
	{
		elem = list->content;

		if (ft_gui_check_event_elem_area(w->gui.mouse_pos, elem) && elem->status & GUI_ELEM_VISIBLE)
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

/*
**	Однотипные функции, возможно объединение
**	
**	void ft_gui_mousemotion(t_wolf3d *w, SDL_Event e, t_list *dom)
**	
**	Function that search mouse position area.
*/
void	ft_gui_mousemotion(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	ft_gui_init_mouse_pos(w);
	w->gui.search_elem = GUI_EVENT_SEARCH;
	ft_gui_event_search_elem(w, e, dom, SDL_MOUSEMOTION);
}

void	ft_gui_mousebuttondown(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	ft_gui_init_mouse_pos(w);
	w->gui.search_elem = GUI_EVENT_SEARCH;
	ft_gui_event_search_elem(w, e, dom, SDL_MOUSEBUTTONDOWN);
}

void	ft_gui_mousebuttonup(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	ft_gui_init_mouse_pos(w);
	w->gui.search_elem = GUI_EVENT_SEARCH;
	ft_gui_event_search_elem(w, e, dom, SDL_MOUSEBUTTONUP);
}

void	ft_gui_mousewheel(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	ft_gui_init_mouse_pos(w);
	w->gui.search_elem = GUI_EVENT_SEARCH;
	ft_gui_event_search_elem(w, e, dom, SDL_MOUSEWHEEL);
}