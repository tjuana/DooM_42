/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_sector_neighbors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:58:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 21:40:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		s = list->content;
		if (s->id != sector->id && s->status)
		{
			i = -1; // bad
			while (++i < s->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % s->vertex_count;
				if (ft_check_general_segment_line(*s->vertex[vtx1_n], \
					*s->vertex[vtx2_n], *v1, *v2))
				{
					s->neighbors[i] = sector->id; // ?!?!?
					return (s->id);
				}
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

/*
** **************************************************************************
**	void ft_editor_sector_reset_neighbors(t_wolf3d *w)
**
**	Function that reset neigbors for sectors.
** **************************************************************************
*/

void	ft_editor_sectors_reset_neighbors(t_wolf3d *w)
{
	t_list		*list;
	t_sector	*s;

	list = w->sector;
	while (list)
	{
		s = list->content;
		if (s->neighbors != NULL)
			ft_bzero(s->neighbors, sizeof(int) * s->vertex_count);
		list = list->next;
	}
}

/*
** **************************************************************************
**	int ft_sectors_set_all_neighbors(t_wolf3d *w)
**
**	Function that set all sectors neighbors.
** **************************************************************************
*/

int		ft_sectors_set_all_neighbors(t_wolf3d *w)
{
	t_list		*list;
	t_sector	*sector;

	ft_editor_sectors_reset_neighbors(w);
	list = w->sector;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1 || sector->status == SECTOR_STATUS_SET)
			ft_editor_sector_search_neighbors(w, sector);
		list = list->next;
	}
	return (0);
}

/*
** **************************************************************************
**	int ft_check_neighbors_sector_vertex(t_sector *s, t_vector3 v)
**
**	Function that check neighbors sector vertex.
** **************************************************************************
*/

int		ft_check_neighbors_sector_vertex(t_sector *s, t_vector3 v)
{
	int	i;
	
	i = 0;
	while (i < s->vertex_count)
	{
		if (ft_compare_vertexes(*s->vertex[i], v))
			return (1);
		i++;
	}
	return (0);
}