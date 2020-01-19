/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events_win_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:43:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/19 16:57:11 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	void ft_gui_mousemotion_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousemotuin event.
*/
void	ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;
	t_ui_coord	coord;

	w = (t_wolf3d*)data;
	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content);
	if (coord.w)
	{
		w->gui.mouse_pos = coord;
		w->gui_map.check_vertex = 1;
	}
	return ;
}

/*
**	[TEMPORARY]
**	void ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
**	
**	Function that ??!?!?!?!??!?!?!?!
*/
void	ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	int			x_c;
	int			y_c;
	t_sector	*sector;
	int			n;
	t_ui_coord	coord;
	t_vector3	v;

	if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
	{
		coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
		if (coord.w)
		{
			if (w->sector_status == 0)
			{
				w->sector_status = 1;
				ft_editor_sector_create(w);
				w->sector_count++;
			}

			ft_editor_sector_set_vertex(w, w->sector->content, \
				ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord));

			sector = w->sector->content;
			if (sector->vertex_count > 1 && \
				ft_editor_sector_compare_vertexes(*sector->vertex[0], \
					*sector->vertex[sector->vertex_count - 1]))
			{
				ft_editor_delete_last_vertex(w);
				if (ft_editor_sector_search_neighbors(w, sector))
				{
					sector->status = 1;
					w->sector_status = 0;
					ft_editor_init_sectors_item_area(w, sector);
				}
			}

			printf("===\n");
			ft_editor_sector_special_debug(w->sector);
		}
	}
	else if (w->gui.mode == GUI_MD_ME_SET_PLAYER)
	{
		coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
		if (coord.w)
		{
			v = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord);

			// Инициализируем игрока, если точка находится
			if (ft_search_point_in_sector((void*)w, v))
			{
				w->pl.pos = v;
				w->player_status = 1;
			}
		}
	}
}

/*
**	void ft_gui_mousebuttondown_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousebuttondown event.
*/
void	ft_gui_mousebuttondown_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_gui_elem	*elem;
	t_ui_coord	coord;

	w = (t_wolf3d*)data;
	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content);
	if (coord.w)
	{
		w->gui.mouse_pos = coord;
		ft_gui_mouse_click_map(w, e, dom);
	}
	return ;
}

/*
**	void ft_gui_mousebuttonup_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousebuttonup event.
*/
void	ft_gui_mousebuttonup_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;

	w = (t_wolf3d*)data;
	return ;
}

/*
**	void ft_gui_mousewheel_win_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousewheel event.
*/
void	ft_gui_mousewheel_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	t_vector3	new_offset;
	t_vector3	old_offset;
	t_vector3	v;

	w = (t_wolf3d*)data;
	old_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, \
		w->gui.mouse_pos);

	if (e.wheel.y > 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale - 1 < 8) ? \
			8 : w->gui_map.grid_scale - 2;
	else if (e.wheel.y < 0)
		w->gui_map.grid_scale = (w->gui_map.grid_scale + 1 > 64) ? \
			64 : w->gui_map.grid_scale + 2;
	new_offset = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, \
		w->gui.mouse_pos);
	w->gui_map.v = (t_vector3){
		w->gui_map.v.x - new_offset.x + old_offset.x, \
		w->gui_map.v.y - new_offset.y + old_offset.y, \
		0, 0
	};
	return ;
}