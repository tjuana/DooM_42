/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:39:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/13 18:31:05 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_create_sector_door(t_wolf3d *w)
**
**
** **************************************************************************
*/

void	ft_create_sector_door(t_wolf3d *w)
{
	t_sector	*sector;

	ft_editor_sector_create(w);
	sector = w->sector->content;
	sector->type = SECTOR_TYPE_DOOR;
	sector->status = SECTOR_STATUS_NOTHING;
	ft_editor_sector_set_vertex(w, w->sector->content, \
		(t_vector3){0, 0, 0, 0}, sector->vertex_count);
	ft_editor_sector_set_vertex(w, w->sector->content, \
		(t_vector3){1, 0, 0, 0}, sector->vertex_count);
	ft_editor_sector_set_vertex(w, w->sector->content, \
		(t_vector3){1, 1, 0, 0}, sector->vertex_count);
	ft_editor_sector_set_vertex(w, w->sector->content, \
		(t_vector3){0, 1, 0, 0}, sector->vertex_count);
	sector->neighbors = ft_my_malloc(sizeof(int) * sector->vertex_count);
	ft_bzero(sector->neighbors, sizeof(int) * sector->vertex_count);
}

/*
** **************************************************************************
**	void	ft_transform_door_vertex(t_vector3 *v1,
**		t_vector3 *v2, t_vector3 pos)
**
**	Function that calculate door vertex.
** **************************************************************************
*/

void	ft_transform_door_vertex(t_vector3 *v1, t_vector3 *v2, t_vector3 pos)
{
	int	i;

	if (v1->x == v2->x)
	{
		i = (v1->y > v2->y) ? 1 : 0;
		v1->y = (double)((int)pos.y) + i;
		v2->y = v1->y + (i ? 1 : -1);
	}
	else
	{
		i = (v1->x > v2->x) ? 1 : 0;
		v1->x = (double)((int)pos.x) + i;
		v2->x = v1->x + (i ? 1 : -1);
	}
}

/*
** **************************************************************************
**	void	ft_change_door_vertex(t_wolf3d *w, t_vector3 v1, \
**				t_vector3 v2, t_vector3 pos)
**
**
** **************************************************************************
*/

void	ft_change_door_vertex(t_wolf3d *w, t_vector3 v1, \
			t_vector3 v2, t_vector3 pos)
{
	t_sector	*sector;
	t_vector3	vec;

	ft_transform_door_vertex(&v1, &v2, pos);
	vec = ft_vec3_create(&v2, &v1);
	vec = ft_vec3_normalize(vec);
	vec = ft_transform_vertex(vec, \
		ft_rz_matrix((t_matrix_4x4){1, 0, 0, 0}, -M_PI_2));
	sector = w->sector->content;
	*sector->vertex[0] = v1;
	*sector->vertex[1] = v2;
	*sector->vertex[2] = ft_vec3_add(v2, vec);
	*sector->vertex[3] = ft_vec3_add(v1, vec);
}

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
