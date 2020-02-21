/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_sector.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 22:28:02 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:11:29 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_gui_draw_map_sector_vertex(t_wolf3d *w, t_sector *s)
{
	int			i;
	t_gui_coord	c1;

	i = 0;
	while (i < s->vertex_count)
	{
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[i++]);
		ft_gui_draw_point(w, c1, s->color);
	}
	if (s->status == 0 && s->vertex_count > 0)
	{
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[0]);
		ft_gui_draw_point(w, c1, 0xffffff);
	}
}

/*
** **************************************************************************
**	void ft_gui_draw_map_sectors(t_wolf3d *w, t_list *list)
**
**	Function that draw sectors for editor map.
** **************************************************************************
*/

void		ft_gui_draw_map_sector_walls(t_wolf3d *w, t_sector *s)
{
	int				i;
	t_gui_coord		c1;
	t_gui_coord		c2;
	int				vtx_n[2];
	t_gui_elem		*elem;

	i = -1;
	s->color = (s->status == 0) ? 0x7b68ee : 0xf8f32b;
	elem = (t_gui_elem*)w->gui_map.ptr->content;
	while (++i < s->vertex_count)
	{
		vtx_n[0] = i;
		vtx_n[1] = (i + 1) % s->vertex_count;
		if (vtx_n[1] == 0 && s->status != 1)
			break ;
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx_n[0]]);
		c2 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx_n[1]]);
		ft_fdf_wu_rect_color(w, (t_gui_rect){c1, c2, 0, 0}, \
			(t_gui_rect){elem->v1, elem->v2, 0, 0}, s->color);
	}
	ft_gui_draw_map_sector_vertex(w, s);
}
