/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:39:38 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/23 16:36:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_create_sector_door(t_wolf3d *w)
{
	t_sector	*sector;

	ft_editor_sector_create(w);
	sector = w->sector->content;
	sector->type = SECTOR_TYPE_DOOR;
	sector->status = SECTOR_STATUS_NOTHING;
	ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){0, 0, 0, 0});
	ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){1, 0, 0, 0});
	ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){1, 1, 0, 0});
	ft_editor_sector_set_vertex(w, w->sector->content, (t_vector3){0, 1, 0, 0});
}

void	ft_change_door_vertex(t_wolf3d *w, t_vector3 v1, t_vector3 v2)
{
	t_sector	*sector;
	t_vector3	vec;

	// ?!
	vec = ft_vec3_create(&v2, &v1);
	vec = ft_vec3_normalize(vec);
	vec = ft_transform_vertex(vec, ft_rz_matrix((t_matrix_4x4){1, 0, 0, 0}, -M_PI_2));

	sector = w->sector->content;
	*sector->vertex[0] = v1;
	*sector->vertex[1] = v2;
	*sector->vertex[2] = ft_vec3_add(v2, vec);
	*sector->vertex[3] = ft_vec3_add(v1, vec);
}