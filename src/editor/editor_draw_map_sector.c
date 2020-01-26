/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_map_sector.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 22:28:02 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/26 21:40:19 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_draw_sector_walls(t_wolf3d *w, t_sector *s)
**	
**	Function that draw sector walls for editor map.
** **************************************************************************
*/

void	ft_draw_sector_walls(t_wolf3d *w, t_sector *s)
{
	int				i;
	t_gui_coord		c1;
	t_gui_coord		c2;
	int				vtx1_n;
	int				vtx2_n;

	i = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (vtx2_n == 0 && s->status == 0)
			break ;
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx1_n]);
		c2 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx2_n]);
		ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, s->color);
		i++;
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
	int				vtx1_n;
	int				vtx2_n;

	i = 0;
	if (s->status == 0)
		s->color = 0x7b68ee;
	else
		s->color = 0xf8f32b;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == s->vertex_count)
		{
			if (s->status == 1)
				vtx2_n = 0;
			else
				break ;
		}

		// Get line coordinates  
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx1_n]);
		c2 = ft_gui_map_vertex_to_coord(w, *s->vertex[vtx2_n]);

		ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, s->color);

		i++;
	}

	i = 0;
	while (i < s->vertex_count)
	{
		c1 = ft_gui_map_vertex_to_coord(w, *s->vertex[i]);
		ft_gui_draw_point(w, c1, s->color);
		i++;
	}
}
