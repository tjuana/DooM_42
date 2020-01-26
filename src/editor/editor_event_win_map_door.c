/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_door.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:34:51 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 15:35:22 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_gui_mousemotion_win_map_door(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	t_gui_elem	*elem;
	// t_gui_coord	coord;
	int			sector_id;
	t_vector3	pos;
	t_sector	*s;
	int			i;
	t_sector	*door;

	if (((t_sector*)w->sector->content)->status == SECTOR_STATUS_PRESET)
		return ;

	((t_sector*)w->sector->content)->status = SECTOR_STATUS_NOTHING;

	// Перевели в координаты карты
	// coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content); // ??!
	pos = ft_gui_map_coord_to_vertex(w, w->gui.mouse_pos);

	sector_id = ft_search_point_in_sector_line_diameter((void*)w, pos, 5);
	// Поиск стены
	if (sector_id > 0)
	{
		s = ft_editor_search_sector_by_id(w, w->sector, sector_id);
		if (s == NULL)
			ft_error("ERROR!");
		i = ft_check_point_in_sector_line_diameter(s, pos, 5);

		// Перпендикулярная линия (как именовать?)
		if (!ft_map_check_straight_line(*s->vertex[i], *s->vertex[(i + 1) % s->vertex_count]))
			return ;

		ft_change_door_vertex(w, *s->vertex[i], *s->vertex[(i + 1) % s->vertex_count], pos);

		door = w->sector->content;

		// incorrect (!)
		// Проверяем, не совпадает ли дверь с существующими вершинами
		// if (ft_check_neighbors_sector_vertex(door, *s->vertex[i]) || \
		// 	ft_check_neighbors_sector_vertex(door, *s->vertex[(i + 1) % s->vertex_count]))
		// 	return ;

		// А записывать соседей?!
		((t_sector*)w->sector->content)->status = SECTOR_STATUS_READY;
	}

	elem = dom->content;
}

void	ft_map_click_door(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	if (((t_sector*)w->sector->content)->status == SECTOR_STATUS_READY)
		((t_sector*)w->sector->content)->status = SECTOR_STATUS_PRESET;
}