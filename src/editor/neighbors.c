/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:58:12 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/12 15:49:47 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_editor_sector_search_neighbors_vertex(t_wolf3d *w, t_vector3 *v1, t_vector3 *v2)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			vtx1_n;
	int			vtx2_n;
	int			i;

	ptr_list = w->sector;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status)
		{
			i = 0;
			while (i < ptr_sector->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % ptr_sector->vertex_count;

				if (
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) ||
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) ||
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1)
					)
				)
				{
					return (ptr_sector->id);
				}
				i++;
			}
		}
		ptr_list = ptr_list->next;
	}
	return (0);
}

int				ft_editor_sector_search_neighbors_item(t_wolf3d *w, t_sector *sector, t_vector3 *v1, t_vector3 *v2)
{
	t_list		*ptr_list;
	t_sector	*ptr_sector;
	int			vtx1_n;
	int			vtx2_n;
	int			i;

	ptr_list = w->sector;
	while (ptr_list)
	{
		ptr_sector = ptr_list->content;

		if (ptr_sector->status)
		{
			i = 0;
			while (i < ptr_sector->vertex_count)
			{
				vtx1_n = i;
				vtx2_n = (i + 1) % ptr_sector->vertex_count;

				if (
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v1) &&
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v2)
					) ||
					(
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx1_n], *v2) &&
						ft_editor_sector_compare_vertexes(*ptr_sector->vertex[vtx2_n], *v1)
					)
				)
				{
					ptr_sector->neighbors[i] = sector->id;
					return (ptr_sector->id);
				}
				i++;
			}
		}
		ptr_list = ptr_list->next;
	}
	return (0);
}

/*
**	int ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
**
**	Function that set neigbors for sector.
*/
int				ft_editor_sector_search_neighbors(t_wolf3d *w, t_sector *sector)
{

	int			vtx1_n;
	int			vtx2_n;
	int			i;
	int			n;
	int			v;

	sector->neighbors = ft_my_malloc(sizeof(void*) * sector->vertex_count);

	i = 0;
	while (i < sector->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % sector->vertex_count;

		n = ft_editor_sector_search_neighbors_item( \
			w, \
			sector, \
			sector->vertex[vtx1_n], \
			sector->vertex[vtx2_n]);

		// v = ft_editor_sector_search_neighbors_item( \
		// 	w, sector->vertex[vtx1_n], \
		// 	sector->vertex[vtx2_n]);

		// if (n == 0 && v > 0)
		// {
		// 	free(sector->neighbors);
		// 	return (0);
		// }

		sector->neighbors[i] = n;
		i++;
	}

	return (1);
}