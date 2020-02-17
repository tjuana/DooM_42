/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_generate_triangles.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:51:25 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/17 15:40:20 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#define MAP_WIDTH		10
#define MAP_HEIGHT		10
#define	SECTOR_W		1

void	ft_me_recursion_algorithm(t_wolf3d *w, int i, int j, int n)
{
	t_sector	*sector;

	if (i >= MAP_WIDTH || j >= MAP_HEIGHT)
		return ;
	ft_editor_sector_create(w);
	w->sector_count++;
	sector = w->sector->content;
	sector->type = SECTOR_TYPE_SECTOR;
	sector->status = SECTOR_STATUS_BROKEN_LINE;
	if (n == 0)
	{
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i, j, 0, 0}, sector->vertex_count);
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i + SECTOR_W, j, 0, 0}, sector->vertex_count);
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i, j + SECTOR_W, 0, 0}, sector->vertex_count);
	}
	else
	{
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i + SECTOR_W, j, 0, 0}, sector->vertex_count);
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i + SECTOR_W, j + SECTOR_W, 0, 0}, sector->vertex_count);
		ft_editor_sector_set_vertex(w, sector, \
			(t_vector3){i, j + SECTOR_W, 0, 0}, sector->vertex_count);
	}

	sector->height = 28;



	ft_editor_check_turn_vertexes(w);
	sector->neighbors = ft_my_malloc(sizeof(int) * sector->vertex_count);
	ft_bzero(sector->neighbors, sizeof(int) * sector->vertex_count);
	if (ft_editor_sector_search_neighbors(w, sector))
		sector->status = SECTOR_STATUS_POLYGON;
	else
		printf("error!\n");

	ft_map_set_new_sector(w, sector);
	sector->status = SECTOR_STATUS_POLYGON;
	
	if (n == 0)
		ft_me_recursion_algorithm(w, i, j, 1);
	else
	{
		if (j <= MAP_WIDTH)
			ft_me_recursion_algorithm(w, i, j + SECTOR_W, 0);
		if (j == 0)
			ft_me_recursion_algorithm(w, i + SECTOR_W, j, 0);
	}
}

void	ft_me_generate_triangles(t_wolf3d *w)
{
	ft_me_recursion_algorithm(w, 0, 0, 0);
}