/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:34:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 18:51:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_init(t_wolf3d *w)
**	
**	Function that initialize gui element.
*/
void	ft_gui_elem_init(t_list **dom, t_ui_coord v1, t_ui_coord v2, int status)
{
	t_list		*list;
	t_gui_elem	*elem;

	elem = ft_my_malloc(sizeof(t_gui_elem));
	bzero(elem, sizeof(t_gui_elem)); // need to use standart slow bzero
	elem->v1 = v1;
	elem->v2 = v2;
	elem->w = elem->v2.x - elem->v1.x;
	elem->h = elem->v2.y - elem->v1.y;
	elem->status = status | GUI_ELEM_NORMAL;
	elem->parent = NULL;
	elem->child = NULL;

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
**	void ft_gui_elem_set_parent(t_list *parent, t_list *child)
**	
**	Function that set parent for gui element.
*/
void	ft_gui_elem_set_parent(t_list *parent, t_list *child)
{
	t_gui_elem	*elem;

	if (elem == NULL)
		ft_error("ERROR");
	elem = child->content;
	elem->parent = parent;
}