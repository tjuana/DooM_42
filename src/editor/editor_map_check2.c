/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_check2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:39:09 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/13 18:47:38 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_check_sector_cross(t_wolf3d *w, t_sector *s, \
**		t_vector3 v1, t_vector3 v2)
** **************************************************************************
*/

int		ft_check_sector_cross(t_wolf3d *w, t_sector *s, \
			t_vector3 v1, t_vector3 v2)
{
	int				i;
	int				vtx1_n;
	int				vtx2_n;
	t_vector3		c;

	i = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		c = ft_find_line_intersect(v1, v2, *s->vertex[vtx1_n], \
			*s->vertex[vtx2_n]);
		if (\
			(ft_check_point_in_line_segment(c, v1, v2) && \
			ft_check_point_in_line_segment(c, *s->vertex[vtx1_n], \
				*s->vertex[vtx2_n])))
			return (1);
		i++;
	}
	return (0);
}

int		ft_search_sectors_cross(void *a, t_vector3 v1, t_vector3 v2)
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
			if (ft_check_sector_cross(w, sector, v1, v2))
				return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}

int		ft_new_editor_map_check_halfplanes(t_sector *s, t_vector3 pos)
{
	t_vector3	vec1;
	t_vector3	vec2;

	if (s->vertex_count == 2)
	{
		vec1 = ft_vec3_create(s->vertex[0], &pos);
		vec2 = ft_vec3_create(s->vertex[0], s->vertex[1]);
		if (ft_vxs_vector(vec1, vec2) > 0.0)
			return (0);
	}
	else
	{
		vec1 = ft_vec3_create(s->vertex[s->vertex_count - 1], &pos);
		vec2 = ft_vec3_create(s->vertex[s->vertex_count - 2], \
			s->vertex[s->vertex_count - 1]);
		if (ft_vxs_vector(vec1, vec2) > 0.0)
			return (0);
		vec2 = ft_vec3_create(s->vertex[0], s->vertex[s->vertex_count - 1]);
		if (ft_vxs_vector(vec1, vec2) > 0.0)
			return (0);
		if (ft_check_line_segment_intersect_vector(*s->vertex[1], \
			*s->vertex[0], *s->vertex[s->vertex_count - 1], pos))
			return (0);
	}
	return (1);
}
