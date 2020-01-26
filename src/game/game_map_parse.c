/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:15:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/26 17:49:29 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_my_parse_map(t_new_player *pl, char *ag)
{
	pl->file.count_sectors = -1;
	if ((pl->file.fd = open(ag, O_RDONLY)) < 0)
		perror("Error: bad file");
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		pl->file.i = 1;
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
		{
			pl->file.count_sector_vertex = -2;
			pl->file.ptr_my += 7;
			pl->file.split = ft_strsplit(pl->file.ptr_my, ' ');
			while (pl->file.split[pl->file.i++] != NULL)
				pl->file.count_sector_vertex++;
			pl->file.count_sector_vertex /= 2;
			pl->file.count_sectors++;
			pl->file.tmp[pl->file.count_sectors] = pl->file.count_sector_vertex;
		}
		if (pl->file.split)
			ft_strdel(pl->file.split);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
	ft_alloc_save_sectors(ag, pl);
	close(pl->file.fd);
}

void			ft_alloc_save_sectors(char *ag, t_new_player *pl)
{
	t_new_xy		*vertex;
	t_new_sector	*sector;

	sector = &pl->sectors;
	ft_open_and_malloc(pl);
	if ((pl->file.fd = open(ag, O_RDONLY)) < 0)
		perror("Error: bad file");
	vertex = ft_memalloc(sizeof(t_new_xy) * (pl->file.count_sectors + 1) * \
				pl->file.count_sector_vertex + 1);
	sector = ft_memalloc(sizeof(t_new_sector) * (pl->file.count_sectors + 1));
	pl->file.i = 0;
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'v')) != NULL)
			vertex = ft_vertex_save(pl, vertex);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
			sector = ft_sector_save(pl, vertex);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
}

t_new_xy	*ft_vertex_save(t_new_player *pl, t_new_xy *vertex)
{
	int	i;

	i = 0;
	pl->file.ptr_my += 7;
	i = ft_atoi(pl->file.ptr_my);
	pl->file.ptr_my++;
	while(*pl->file.ptr_my++ != '\0')
	{
		vertex[pl->file.i].y = i;
		vertex[pl->file.i].x = ft_atoi(pl->file.ptr_my);
		pl->file.ptr_my++;
		if (vertex[pl->file.i].x > 9)
			pl->file.ptr_my++;
		pl->file.i++;
	}
	return (vertex);
}

t_new_sector	*ft_sector_save(t_new_player *pl, t_new_xy *vertex)
{
	
}