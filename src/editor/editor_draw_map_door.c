/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_door.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/19 19:49:00 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_editor_draw_door(t_wolf3d *w, t_sector *s)
**
**	Function that draw door for editor map.
** **************************************************************************
*/

void		ft_editor_draw_door(t_wolf3d *w, t_sector *s)
{
	if (s->status == SECTOR_STATUS_READY || \
		s->status == SECTOR_STATUS_PRESET ||
		s->status == SECTOR_STATUS_SET)
	{
		s->color = GUI_CL_DOOR;
		ft_draw_sector_walls(w, s);
	}
}
