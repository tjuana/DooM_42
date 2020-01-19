/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw_map_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 16:46:25 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 17:01:49 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_draw_player(t_wolf3d *w)
{
	t_ui_coord c;

	if (w->player_status == 1)
	{
		c = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, w->pl.pos);
		ft_gui_draw_point(w, c, GUI_CL_PLAYER);
	}
}