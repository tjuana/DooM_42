/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:34:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/15 12:59:23 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that initialize gui element.
*/
void	ft_gui_elem_init(t_list **dom, char *name, t_ui_coord v1, t_ui_coord v2)
{
	t_list		*list;
	t_gui_elem	*elem;

	elem = ft_my_malloc(sizeof(t_gui_elem));
	bzero(elem, sizeof(t_gui_elem)); // need to use standart slow bzero
	elem->name = ft_strdup(name);
	elem->v1 = v1;
	elem->v2 = v2;
	elem->w = elem->v2.x - elem->v1.x;
	elem->h = elem->v2.y - elem->v1.y;
	elem->status = GUI_ELEM_HIDDEN | GUI_ELEM_NORMAL;
	elem->parent = NULL;
	elem->child = NULL;
	elem->events = NULL;

	list = ft_lstnew(elem, sizeof(t_gui_elem));
	if (list == NULL)
		ft_error("ERROR");
	if (*dom == NULL)
		*dom = list;
	else
		ft_lstadd(dom, list);
}

/*
**	[TEMPORARY]
**	void ft_gui_elem_set_color(t_gui_elem *elem, int color)
**	
**	Function that set gui element color.
*/
void	ft_gui_elem_set_color(t_list *list, int color)
{
	t_gui_elem *elem;

	if (list == NULL)
		ft_error("ERROR");
	elem = list->content;
	elem->color = color;
}

/*
**	[TEMPORARY]
**	void ft_gui_elem_set_status(t_list *list, unsigned char status)
**	
**	Function that set special status for gui element.
*/
void	ft_gui_elem_set_status(t_list *list, unsigned char status)
{
	t_gui_elem	*elem;

	elem = list->content;
	if (status > GUI_ELEM_ACT_MASK)
	{
		elem->status = elem->status & GUI_ELEM_ACT_MASK;
		elem->status = elem->status | status;
	}
	if (status & (GUI_ELEM_HIDDEN | GUI_ELEM_VISIBLE))
		elem->status = (elem->status ^ (GUI_ELEM_HIDDEN | GUI_ELEM_VISIBLE)) | status;
	if (status & (GUI_ELEM_STATIC | GUI_ELEM_DYNAMIC))
		elem->status = (elem->status ^ (GUI_ELEM_STATIC | GUI_ELEM_DYNAMIC)) | status;
}

/*
**	void ft_gui_elem_set_event(t_list *list, int type, void *func)
**	
**	Function that set event for gui element.
*/
void			ft_gui_elem_set_event(t_list *list, void *func, int type, int code)
{
	t_gui_elem	*elem;
	t_gui_event	*event;
	t_list		*new_list;

	elem = list->content;
	event = ft_my_malloc(sizeof(t_gui_event));
	event->type = type;
	event->func = func;
	event->code = code;
	event->elem = list;
	new_list = ft_lstnew(event, sizeof(t_gui_event));
	if (elem->events == NULL)
		elem->events = new_list;
	else
		ft_lstadd(&elem->events, new_list);
}

/*
**	void ft_gui_elem_set_parent(t_list *parent, t_list *child)
**	
**	Function that set parent for gui element.
*/
void	ft_gui_elem_set_parent(t_list *parent, t_list *child)
{
	t_gui_elem	*child_elem;
	t_gui_elem	*parent_elem;

	if (child_elem == NULL)
		ft_error("ERROR");
	if (parent_elem == NULL)
		ft_error("ERROR");
	child_elem = child->content;
	parent_elem = parent->content;
	child_elem->parent = parent;
	child_elem->pos.top = child_elem->v1.y - parent_elem->v1.y;
	child_elem->pos.bottom = parent_elem->v2.y - child_elem->v2.y;
	child_elem->pos.left = child_elem->v1.x - parent_elem->v1.x;
	child_elem->pos.right = parent_elem->v2.x - child_elem->v2.x;
}