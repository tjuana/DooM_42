/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:40:43 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 18:50:01 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_print_elements(t_list *dom, int level)
**	
**	Function that print gui element list.
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
		printf("%02d: w:%-6d h:%-6d\n", level, elem->w, elem->h);

		ft_gui_print_element_list(elem->child, (level + 1));
		list = list->next;
	}
}