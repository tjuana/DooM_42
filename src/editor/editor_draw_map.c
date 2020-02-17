/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:47:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/16 19:18:18 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_draw_map_sectors(t_wolf3d *w, t_list *list)
**
**	Function that draw sectors for editor map.
** **************************************************************************
*/

void	ft_gui_draw_map_sectors(t_wolf3d *w, t_list *list)
{
	t_sector	*s;

	if (list)
	{
		ft_gui_draw_map_sectors(w, list->next);
		s = list->content;
		if (s->type == SECTOR_TYPE_SECTOR)
			ft_gui_draw_map_sector_walls(w, s);
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_map_doors(t_wolf3d *w, t_list *list)
**
**	Function that draw doors for editor map.
** **************************************************************************
*/

void	ft_gui_draw_map_doors(t_wolf3d *w, t_list *list)
{
	t_sector	*s;

	if (list)
	{
		ft_gui_draw_map_doors(w, list->next);
		s = list->content;
		if (s->type == SECTOR_TYPE_DOOR)
			ft_editor_draw_door(w, s);
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**
**	Function that draw editor map.
** **************************************************************************
*/

void	ft_gui_draw_map(t_wolf3d *w, t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	ft_gui_draw_map_grid_limit_sector(w, elem, w->gui_map.r1, \
		GUI_MAP_GRID_LIMIT_TL);
	ft_gui_draw_map_grid_limit_sector(w, elem, w->gui_map.r2, \
		GUI_MAP_GRID_LIMIT_BR);
	ft_gui_draw_map_grid(w, elem, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, elem, w->gui_map.r1, \
		w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, elem, w->gui_map.r2, \
		w->gui_map.grid_scale);
	w->gui_map.check_vertex = ft_gui_draw_map_vertex(w, w->gui.mouse_pos, \
		w->gui_map.check_vertex, w->gui.mode);
	ft_gui_draw_map_vertex_line(w, w->gui.mouse_pos);
	ft_gui_draw_map_doors(w, w->sector);
	ft_gui_draw_map_sectors(w, w->sector);
	ft_gui_draw_player(w);
	ft_gui_draw_sprites(w);
	ft_gui_draw_enemies(w);
}
