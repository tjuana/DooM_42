/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:40:43 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/06 17:57:46 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_print_elements(t_list *dom, int level)
**
**	Function that print gui element list.
** **************************************************************************
*/

void	ft_gui_print_element_list(t_list *dom, int level)
{
	t_list		*list;
	t_gui_elem	*elem;
	int			i;

	list = dom;
	while (list != NULL)
	{
		elem = list->content;
		i = 0;
		while (i++ < level)
			printf("  ");
		printf("%02d: %30s   w:%-6d h:%-6d   %#x\n", level, elem->name, \
			elem->w, elem->h, elem->status);
		ft_gui_print_element_list(elem->child, (level + 1));
		list = list->next;
	}
}
