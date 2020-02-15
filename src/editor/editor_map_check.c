/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:45:52 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/15 15:46:22 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
**
**	Function that search point in the current sector.
**
**	Return:
**	0		| Point lies on the segment vertex
**			| or point don't lies inside the sector.
**	1		| Point lies inside the sector.
**	2		| Point lies on the segment conture (walls).
** **************************************************************************
*/

int		ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
{
	int				i;
	int				vtx1_n;
	int				vtx2_n;
	int				count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (ft_compare_vertexes(v, *s->vertex[vtx1_n]) || \
			ft_compare_vertexes(v, *s->vertex[vtx2_n]))
			return (0);
		if (ft_check_point_in_line_segment(v, *s->vertex[vtx1_n], \
			*s->vertex[vtx2_n]))
			return (2);
		if (ft_check_line_segment_intersect_vector(\
			(t_vector3){-10.0, -10.0, 0, 0}, v, \
			*s->vertex[vtx1_n], *s->vertex[vtx2_n]))
			count++;
		i++;
	}
	return (count % 2);
}

/*
** **************************************************************************
**	int ft_search_point_in_sector(void *a, t_vector3 v)
**
**	Function that search point in initialized sectors.
**
**	Return:
**	sector->id	| Number of the sector
**	0			| Point don't lies in initialized sectors.
** **************************************************************************
*/

int		ft_search_point_in_sector(void *a, t_vector3 v)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*sector;
	int			i;

	w = (t_wolf3d*)a;
	list = w->sector;
	i = 0;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1)
		{
			if (ft_check_point_in_sector(w, sector, v))
				return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}

int		ft_check_origin_vertex(t_sector *s, t_vector3 v)
{
	int	i;

	i = 0;
	while (i < s->vertex_count)
	{
		if (ft_compare_vertexes(v, *s->vertex[i]) && i != 0)
			return (0);
		i++;
	}
	if (s->vertex_count == 2 && ft_compare_vertexes(v, *s->vertex[0]))
		return (0);
	return (1);
}

/*
** **************************************************************************
**	int ft_new_editor_map_check_area(t_wolf3d *w)
**
**	Function that check the validity of the new point (vertex).
** **************************************************************************
*/

int		ft_new_editor_map_check_area(t_wolf3d *w)
{
	t_sector	*s;
	t_vector3	pos;

	if (w->sector == NULL)
		return (1);
	pos = ft_gui_map_coord_to_vertex(w, w->gui.mouse_pos);
	if (ft_search_point_in_sector(w, pos))
		return (0);
	s = w->sector->content;
	if (s->vertex_count == 0)
		return (1);
	if (ft_search_sector_in_sector(w, s))
		return (0);
	if (!ft_check_origin_vertex(w->sector->content, pos))
		return (0);
	if (ft_search_sectors_cross(w, *s->vertex[s->vertex_count - 1], pos))
		return (0);
	if (s->status == 1 || s->vertex_count < 2)
		return (1);
	return (ft_new_editor_map_check_halfplanes(s, pos));
}
