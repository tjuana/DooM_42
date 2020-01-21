/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:34:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/21 15:28:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	t_list *ft_gui_search_elem_by_name(t_list *dom, char *name)
**	
**	Function that search elem by name.
*/
t_list	*ft_gui_search_elem_by_name(t_list *dom, char *name)
{
	t_list		*list;
	t_gui_elem	*elem;
	int			cmp;

	list = dom;
	while (list != NULL)
	{
		elem = list->content;
		cmp = ft_strcmp(name, elem->name);
		if (cmp == 0)
			return (list);
		else if (cmp == '_')
			return (ft_gui_search_elem_by_name(elem->child, name));
		list = list->next;
	}
	return (NULL);
}

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that initialize gui element.
*/
void	ft_gui_elem_init(t_list **dom, char *name, t_gui_coord v1, t_gui_coord v2)
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
	elem->status = GUI_ELEM_VISIBLE | GUI_ELEM_NORMAL;
	elem->parent = NULL;
	elem->child = NULL;
	elem->events = NULL;
	elem->type = GUI_BLOCK;
	elem->str = NULL;

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
**	void ft_gui_elem_set_status(t_list *list, int status)
**	
**	Function that set special status for gui element.
*/
void	ft_gui_elem_set_status(t_list *list, int status)
{
	t_gui_elem	*elem;

	if (list == NULL)
		return ;
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

char	*ft_gui_elem_get_value(t_list *list)
{
	t_gui_elem	*elem;

	if (list == NULL)
		return (NULL);
	elem = list->content;
	return (elem->str);
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
**	void ft_gui_elem_set_event(t_list *list, int type, void *func)
**	
**	Function that set event for gui element.
*/
void			ft_gui_elem_set_redraw(t_list *list, void *func)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->redraw = func;
}

void			ft_gui_elem_set_redraw_font(t_list *list, void *func)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->redraw_font = func;
}

void			ft_gui_elem_set_image(t_list *list, char *path)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_IMAGE;
	elem->surf = IMG_Load(path);
	elem->surf == NULL ? ft_error("IMAGE LOAD ERROR") : 0;
}

/*
**	void ft_gui_elem_set_block(t_list *list)
**	
**	Function that set block type for gui element.
*/
void			ft_gui_elem_set_block(t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_BLOCK;
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_block, SDL_MOUSEBUTTONUP, 0);
}

/*
**	void ft_gui_elem_set_button(t_list *list, void *str)
**	
**	Function that set button type for gui element.
*/
void			ft_gui_elem_set_button(t_list *list, void *str)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_BUTTON;
	elem->str = ft_strdup(str);
	ft_gui_elem_set_event(list, ft_gui_mousemotion_button, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttondown_button, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_button, SDL_MOUSEBUTTONUP, 0);
}

/*
**	void ft_gui_elem_set_input(t_list *list, void *str)
**	
**	Function that set input type for gui element.
*/
void			ft_gui_elem_set_input(t_list *list, void *str, int flag_numb)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_INPUT;
	if (flag_numb)
		elem->type = GUI_INPUT_NUMB;
	elem->str = ft_strdup(str);
	ft_gui_elem_set_event(list, ft_gui_mousemotion_input, SDL_MOUSEMOTION, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttondown_input, SDL_MOUSEBUTTONDOWN, 0);
	ft_gui_elem_set_event(list, ft_gui_mousebuttonup_input, SDL_MOUSEBUTTONUP, 0);
}

/*
**	void ft_gui_elem_set_text(t_list *list, void *str)
**	
**	Function that set text type for gui element.
*/
void			ft_gui_elem_set_text(t_list *list, void *str)
{
	t_gui_elem	*elem;

	elem = list->content;
	elem->type = GUI_TEXT;
	elem->str = ft_strdup(str);
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
	// child_elem->pos.top = child_elem->v1.y - parent_elem->v1.y;
	// child_elem->pos.bottom = parent_elem->v2.y - child_elem->v2.y;
	// child_elem->pos.left = child_elem->v1.x - parent_elem->v1.x;
	// child_elem->pos.right = parent_elem->v2.x - child_elem->v2.x;
}

/*
**	void ft_gui_delete_status_focus(t_list *dom)
**	
**	Function that delete all focus status of gui elements.
*/
void	ft_gui_delete_status_focus(t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	while (list != NULL)
	{
		ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
		elem = list->content;
		ft_gui_delete_status_focus(elem->child);
		list = list->next;
	}
}

/*
**	void ft_gui_delete_status(t_list *dom)
**	
**	Function that delete all status except focus of gui elements.
*/
void	ft_gui_delete_status(t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	while (list != NULL)
	{
		// ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
		elem = list->content;
		if (!(elem->status & GUI_ELEM_FOCUS))
			ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
		ft_gui_delete_status(elem->child);
		list = list->next;
	}
}