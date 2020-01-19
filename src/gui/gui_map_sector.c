/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_map_sector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:46:39 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 19:47:13 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_delete_sector(t_wolf3d *w)
{
	t_list	*list;

	if (w->sector == NULL)
		return ;
	list = w->sector;
	w->sector = w->sector->next;
	free(list->content);
	free(list);
}