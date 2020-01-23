/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_events_win_map.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:43:00 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/23 16:59:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// ?!
typedef struct	s_line
{
	t_vector3	v1;	// line vertex 1
	t_vector3	v2;	// line vertex 2
}				t_line;

void	ft_gui_mousemotion_win_map_door(t_wolf3d *w, SDL_Event e, t_list *dom)
{
	t_gui_elem	*elem;
	// t_gui_coord	coord;
	int			sector_id;
	t_vector3	pos;
	t_sector	*s;
	int			i;

	if (((t_sector*)w->sector->content)->status == SECTOR_STATUS_PRESET)
		return ;

	((t_sector*)w->sector->content)->status = SECTOR_STATUS_NOTHING;

	// Перевели в координаты карты
	// coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content); // ??!
	pos = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, w->gui.mouse_pos);

	sector_id = ft_search_point_in_sector_line_diameter((void*)w, pos, 5);
	// Поиск стены
	if (sector_id > 0)
	{
		// printf(">>> SECTOR: %d\n", sector_id);

		s = ft_editor_search_sector_by_id(w, w->sector, sector_id);
		if (s == NULL)
			ft_error("ERROR!");
		i = ft_check_point_in_sector_line_diameter(s, pos, 5);

		if (!ft_map_check_straight_line(*s->vertex[i], *s->vertex[(i + 1) % s->vertex_count]))
			return ;

		((t_sector*)w->sector->content)->status = SECTOR_STATUS_READY;
		ft_change_door_vertex(w, *s->vertex[i], *s->vertex[(i + 1) % s->vertex_count]);
	}

	elem = dom->content;
}

void	ft_map_click_door(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	if (((t_sector*)w->sector->content)->status == SECTOR_STATUS_READY)
		((t_sector*)w->sector->content)->status = SECTOR_STATUS_PRESET;
}

/*
**	void ft_gui_mousemotion_map(void *data, SDL_Event e, t_list *dom, int type)
**	
**	Function that transform map status for mousemotuin event.
*/
void	ft_gui_mousemotion_win_map(void *data, SDL_Event e, \
			t_list *dom, int type)
{
	t_wolf3d	*w;
	// t_gui_elem	*elem;
	t_gui_coord	coord;

	w = (t_wolf3d*)data;
	if (w->gui.mode == GUI_MD_ME_SET_DOOR)
		ft_gui_mousemotion_win_map_door(w, e, dom);
	else
	{
		coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content);
		if (coord.w)
		{
			w->gui.mouse_pos = coord;
			w->gui_map.check_vertex = 1;
		}
	}
	return ;
}

void	ft_gui_event_set_sector(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_sector	*sector;

	coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, elem->content);
	sector = w->sector->content;
	if (coord.w && sector->status != SECTOR_STATUS_POLYGON)
	{
		ft_editor_sector_set_vertex(w, w->sector->content, \
			ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord));

		if (sector->vertex_count > 1 && \
			ft_editor_sector_compare_vertexes(*sector->vertex[0], \
				*sector->vertex[sector->vertex_count - 1]))
		{
			ft_editor_delete_last_vertex(w);
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
		v = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord);

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
		v = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord);

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
		v = ft_gui_map_coord_to_vertex(w, (t_gui_rect){0, 0, 0, 0}, coord);

		// Инициализируем спрайт, если точка находится в секторе
		if (ft_search_point_in_sector((void*)w, v))
		{
			ft_set_enemy(w, v, 1);
			w->enemy_status = 1;
		}
	}
}

/*
**	[TEMPORARY]
**	void ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
**	
**	Function that ??!?!?!?!??!?!?!?!
*/
void	ft_gui_mouse_click_map(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	// Открытие элемента по клику
	// if (w->gui.mode == GUI_MD_ME)
	//	ft_gui_event_open_elem(w, e, elem);
	if (w->gui.mode == GUI_MD_ME_SET_SECTOR)
		ft_gui_event_set_sector(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_PLAYER)
		ft_gui_event_set_player(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_SPRITE)
		ft_gui_event_set_sprite(w, e, elem);
	else if (w->gui.mode == GUI_MD_ME_SET_ENEMY)
		ft_gui_event_set_enemy(w, e, elem);
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
	t_gui_coord	coord;

	w = (t_wolf3d*)data;
	if (w->gui.mode == GUI_MD_ME_SET_DOOR)
		ft_map_click_door(w, e, dom);
	else
	{
		coord = ft_gui_map_check_mouse_vertex_pos(w, w->gui.mouse_pos, dom->content);
		if (coord.w)
		{
			w->gui.mouse_pos = coord;
			ft_gui_mouse_click_map(w, e, dom);
		}
		return ;
	}
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