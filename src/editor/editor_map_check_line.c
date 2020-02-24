/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_check_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:41:11 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/13 18:41:39 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, \
**		double d)
**
**
** **************************************************************************
*/

int		ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, \
			double d)
{
	int		i;
	int		vtx1_n;
	int		vtx2_n;
	int		count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (ft_check_point_in_line_segment_diameter(\
			v, *s->vertex[vtx1_n], *s->vertex[vtx2_n], d))
			return (i);
		i++;
	}
	return (-1);
}

/*
** **************************************************************************
**	int ft_search_point_in_sector_line_diameter(void *a, t_vector3 v, \
**	double d)
**
**
** **************************************************************************
*/

int		ft_search_point_in_sector_line_diameter(void *a, \
			t_vector3 v, double d)
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
			if (!ft_check_point_in_sector(w, sector, v))
				if (ft_check_point_in_sector_line_diameter(sector, \
					v, d) != -1)
					return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}
