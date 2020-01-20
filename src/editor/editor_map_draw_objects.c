/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_draw_objects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 16:46:25 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 19:35:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_draw_player(t_wolf3d *w)
{
	t_gui_coord	c;

	if (w->player_status == 1)
	{
		c = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, w->pl.pos);
		ft_gui_draw_point(w, c, GUI_CL_PLAYER);
	}
}

void	ft_gui_draw_sprites(t_wolf3d *w)
{
	t_gui_coord	c;
	t_list		*list;
	t_sprite	*sprite;

	list = w->sprite;
	while (list != NULL)
	{
		sprite = list->content;
		c = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, sprite->pos);
		ft_gui_draw_point(w, c, GUI_CL_SPRITE);
		list = list->next;
	}
}

void	ft_gui_draw_enemies(t_wolf3d *w)
{
	t_gui_coord	c;
	t_list		*list;
	t_sprite	*enemy;

	list = w->enemy;
	while (list != NULL)
	{
		enemy = list->content;
		c = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, enemy->pos);
		ft_gui_draw_point(w, c, GUI_CL_ENEMY);
		list = list->next;
	}
}