/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_win_map_set.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:31:55 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:36:52 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_event_set_sector(t_wolf3d *w, SDL_Event e, t_list *elem)
** **************************************************************************
*/

void	ft_gui_event_set_sector(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_sector	*s;

	(void)e;
	coord = ft_gui_map_check_mouse(w, w->gui.mouse_pos, elem->content);
	s = w->sector->content;
	if (coord.w && s->status != SECTOR_STATUS_POLYGON)
	{
		if (!ft_new_editor_map_check_area(w))
			return ;
		ft_editor_sector_set_vertex(w->sector->content, \
			ft_gui_map_coord_to_vertex(w, coord), s->vertex_count);
		if (s->vertex_count > 1 && \
			ft_compare_vertexes(*s->vertex[0], \
				*s->vertex[s->vertex_count - 1]))
		{
			ft_editor_delete_last_vertex(w);
			ft_editor_check_turn_vertexes(w);
			s->neighbors = ft_my_malloc(sizeof(int) * s->vertex_count);
			ft_bzero(s->neighbors, sizeof(int) * s->vertex_count);
			if (ft_editor_sector_search_neighbors(w, s))
				s->status = SECTOR_STATUS_POLYGON;
		}
	}
}

/*
** **************************************************************************
**	void ft_gui_event_set_player(t_wolf3d *w, SDL_Event e, t_list *elem)
** **************************************************************************
*/

void	ft_gui_event_set_player(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	(void)e;
	coord = ft_gui_map_check_mouse(w, w->gui.mouse_pos, \
		elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);
		if (ft_search_point_in_sector((void*)w, v))
		{
			w->pl.pos = v;
			w->player_status = 1;
		}
	}
}

/*
** **************************************************************************
**	void ft_gui_event_set_sprite(t_wolf3d *w, SDL_Event e, t_list *elem)
** **************************************************************************
*/

void	ft_gui_event_set_sprite(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	(void)e;
	coord = ft_gui_map_check_mouse(w, w->gui.mouse_pos, \
		elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);
		if (ft_search_point_in_sector((void*)w, v))
		{
			ft_set_sprite(w, v, 1);
			w->sprite_status = 1;
		}
	}
}

/*
** **************************************************************************
**	void ft_gui_event_set_enemy(t_wolf3d *w, SDL_Event e, t_list *elem)
** **************************************************************************
*/

void	ft_gui_event_set_enemy(t_wolf3d *w, SDL_Event e, t_list *elem)
{
	t_gui_coord	coord;
	t_vector3	v;

	(void)e;
	coord = ft_gui_map_check_mouse(w, w->gui.mouse_pos, \
		elem->content);
	if (coord.w)
	{
		v = ft_gui_map_coord_to_vertex(w, coord);
		if (ft_search_point_in_sector((void*)w, v))
		{
			ft_set_enemy(w, v, 1);
			w->enemy_status = 1;
		}
	}
}
