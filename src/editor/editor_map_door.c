/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:39:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/21 17:23:14 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_set_new_vertex_for_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
**
**
** **************************************************************************
*/

void	ft_set_new_vertex_for_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
{
	int	i;
	int	vtx1_n;
	int	vtx2_n;

	i = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (ft_check_point_in_line_segment(v, *s->vertex[vtx1_n], \
			*s->vertex[vtx2_n]))
			ft_editor_sector_set_vertex(w, s, v, i + 1);
		i++;
	}
}

/*
** **************************************************************************
**	int ft_set_new_vertex_for_sector_list(void *a, t_vector3 **v, int count)
**
**
** **************************************************************************
*/

int		ft_set_new_vertex_for_sector_list(void *a, t_vector3 **v, int count)
{
	t_list		*list;
	t_sector	*s;
	int			i;
	int			j;

	list = ((t_wolf3d*)a)->sector;
	i = 0;
	while (list)
	{
		s = list->content;
		if (s->status == 1 && s->type == SECTOR_TYPE_SECTOR)
		{
			j = -1;
			while (++j < count)
				ft_set_new_vertex_for_sector((t_wolf3d*)a, s, *v[j]);
			free(s->neighbors);
			s->neighbors = ft_my_malloc(sizeof(void*) * s->vertex_count);
			ft_bzero(s->neighbors, sizeof(void*) * s->vertex_count);
		}
		list = list->next;
		i++;
	}
	return (0);
}
