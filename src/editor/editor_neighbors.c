/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_neighbors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:58:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/20 17:50:25 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	int		ft_editor_sector_search_neighbors_item(t_wolf3d *w,
**				t_sector *s, t_vector3 *v1, t_vector3 *v2)
**
**	Function that search neighbors sector.
** **************************************************************************
*/

int		ft_editor_sector_search_neighbors_item(t_wolf3d *w, \
			t_sector *sector, t_vector3 *v1, t_vector3 *v2)
{
	t_list		*list;
	t_sector	*s;
	int			vtx1_n;
	int			vtx2_n;
	int			i;

	list = w->sector;
	while (list)
	{
		sector = list->content;
		if (s->id != sector->id && s->status)
		{
			i = -1; // bad
			while (i++ < s->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % s->vertex_count;
				if (ft_check_general_segment_line(*s->vertex[vtx1_n], \
					*s->vertex[vtx2_n], *v1, *v2))
					return (s->id);
			}
		}
		list = list->next;
	}
	return (0);
}

/*
** **************************************************************************
**	int	ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
**
**	Function that set neigbors for sector.
** **************************************************************************
*/

int		ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
{
	int		vtx1_n;
	int		vtx2_n;
	int		i;
	int		v;

	sector->neighbors = ft_my_malloc(sizeof(void*) * sector->vertex_count);
	i = 0;
	while (i < sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % sector->vertex_count;
		sector->neighbors[i] = ft_editor_sector_search_neighbors_item(\
			w, sector, sector->vertex[vtx1_n], sector->vertex[vtx2_n]);
		i++;
	}
	return (1);
}
