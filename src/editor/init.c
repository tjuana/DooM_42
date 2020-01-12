/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 18:14:27 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that init. some values...
*/
void		ft_editor_init(t_wolf3d *w)
{
	w->sector = NULL;
	w->sector_status = 0;
	w->mouse_pos = (t_vector3){0, 0, 0, 0};
	w->status = 1;
	w->sector_count = 0;

	// ui_map values
	w->ui_map.v1 = (t_vector3){20, 20, 0, 0};
	w->ui_map.v2 = (t_vector3){1720, 1060, 0, 0};
	w->ui_map.w = w->ui_map.v2.x - w->ui_map.v1.x;
	w->ui_map.h = w->ui_map.v2.y - w->ui_map.v1.y;
}