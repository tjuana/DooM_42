/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_elem_set_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:23:08 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 18:54:03 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	[TEMPORARY]
**	void ft_gui_elem_set_status(t_list *list, int status)
**
**	Function that set special status for gui element.
** **************************************************************************
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
		elem->status = \
			(elem->status ^ (GUI_ELEM_HIDDEN | GUI_ELEM_VISIBLE)) | status;
	if (status & (GUI_ELEM_STATIC | GUI_ELEM_DYNAMIC))
		elem->status = \
			(elem->status ^ (GUI_ELEM_STATIC | GUI_ELEM_DYNAMIC)) | status;
}

/*
** **************************************************************************
**	void ft_gui_delete_status_focus(t_list *dom)
**
**	Function that delete all focus status of gui elements.
** **************************************************************************
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
** **************************************************************************
**	void ft_gui_delete_status(t_list *dom)
**
**	Function that delete all status except focus of gui elements.
** **************************************************************************
*/

void	ft_gui_delete_status(t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	while (list != NULL)
	{
		elem = list->content;
		if (!(elem->status & GUI_ELEM_FOCUS))
			ft_gui_elem_set_status(list, GUI_ELEM_NORMAL);
		ft_gui_delete_status(elem->child);
		list = list->next;
	}
}
