/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_set.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:31:55 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 15:32:32 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_event_set_sector(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_sector	*sector;

	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
	sector = w->sector->content;
	if (coord.w && sector->status != SECTOR_STATUS_POLYGON)
	{
		if (!ft_new_editor_map_check_area(w))
			return ;
		ft_editor_sector_set_vertex(w, w->sector->content, \
			ft_gui_map_coord_to_vertex(w, coord), sector->vertex_count);

		if (sector->vertex_count > 1 && \
			ft_editor_sector_compare_vertexes(*sector->vertex[0], \
				*sector->vertex[sector->vertex_count - 1]))
		{
			ft_editor_delete_last_vertex(w);
			// Определяем соседей
			sector->neighbors = ft_my_malloc(sizeof(int) * sector->vertex_count);
			ft_bzero(sector->neighbors, sizeof(int) * sector->vertex_count);
			if (ft_editor_sector_search_neighbors(w, sector))
				sector->status = SECTOR_STATUS_POLYGON;
		}

		printf("===\n");
		ft_editor_sector_special_debug(w->sector);
	}
}

void	ft_gui_event_set_player(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);

		// Инициализируем игрока, если точка находится в секторе
		if (ft_search_point_in_sector((void*)w, v))
		{
			w->pl.pos = v;
			w->player_status = 1;
		}
	}
}


void	ft_gui_event_set_sprite(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);

		// Инициализируем спрайт, если точка находится в секторе
		if (ft_search_point_in_sector((void*)w, v))
		{
			ft_set_sprite(w, v, 1);
			w->sprite_status = 1;
		}
	}
}

void	ft_gui_event_set_enemy(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);

		// Инициализируем спрайт, если точка находится в секторе
		if (ft_search_point_in_sector((void*)w, v))
		{
			ft_set_enemy(w, v, 1);
			w->enemy_status = 1;
		}
	}
}