/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_destruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:07:32 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/14 19:50:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_desctuct(t_list *dom)
**	
**	Function that destruct all gui values.
*/
void	ft_gui_desctuct(t_list *dom)
{
	t_list		*list;
	t_gui_elem	*elem;

	list = dom;
	if (list != NULL)
	{
		ft_gui_desctuct(list->next);
		elem = list->content;
		ft_gui_desctuct(elem->child);
		free(elem->name);
		free(elem);
		free(list);
	}
}