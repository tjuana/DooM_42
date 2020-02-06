/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:34:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/06 17:58:24 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void	ft_gui_elem_init(t_list **dom, char *name, \
**		t_gui_coord v1, t_gui_coord v2)
**
**	Function that initialize gui element.
** **************************************************************************
*/

void	ft_gui_elem_init(t_list **dom, char *name, \
			t_gui_coord v1, t_gui_coord v2)
{
	t_list		*list;
	t_gui_elem	elem;

	ft_bzero(&elem, sizeof(t_gui_elem));
	elem.name = ft_strdup(name);
	elem.v1 = v1;
	elem.v2 = v2;
	elem.w = elem.v2.x - elem.v1.x;
	elem.h = elem.v2.y - elem.v1.y;
	elem.status = GUI_ELEM_VISIBLE | GUI_ELEM_NORMAL;
	elem.parent = NULL;
	elem.child = NULL;
	elem.events = NULL;
	elem.type = GUI_BLOCK;
	elem.str = NULL;
	list = ft_lstnew(&elem, sizeof(t_gui_elem));
	if (list == NULL)
		ft_error("ERROR (N1)");
	if (*dom == NULL)
		*dom = list;
	else
		ft_lstadd(dom, list);
}

/*
** **************************************************************************
**	void ft_gui_elem_set_parent(t_list *parent, t_list *child)
**
**	Function that set parent for gui element.
** **************************************************************************
*/

void	ft_gui_elem_set_parent(t_list *parent, t_list *child)
{
	t_gui_elem	*child_elem;
	t_gui_elem	*parent_elem;

	if (child == NULL)
		ft_error("ERROR (N3)");
	if (parent == NULL)
		ft_error("ERROR (N4)");
	child_elem = child->content;
	parent_elem = parent->content;
	child_elem->parent = parent;
}

/*
** **************************************************************************
**	t_list *ft_gui_search_elem_by_name(t_list *dom, char *name)
**
**	Function that search elem by name.
** **************************************************************************
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
