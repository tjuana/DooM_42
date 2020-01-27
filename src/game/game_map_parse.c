/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:15:15 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/27 16:13:57 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_my_parse_map(t_new_player *pl, char *ag)
{
	pl->file.count_sectors = -1;
	if ((pl->file.fd = open(ag, O_RDONLY)) < 0)
		perror("Error: bad file");
	pl->file.vertex_count = 0;
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		pl->file.i = 1;
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'v')) != NULL)
			ft_vertex_count(pl);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
			ft_sector_count(pl);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
	close(pl->file.fd);
	ft_alloc_save_sectors(ag, pl);
}

void		ft_vertex_count(t_new_player *pl)
{
	int	i;

	i = 2;
	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	while (pl->file.split[i++] != NULL)
		pl->file.vertex_count++;
	if (pl->file.split)
		ft_strdel(pl->file.split);
}

void		ft_sector_count(t_new_player *pl)
{
	int	count;
	char *s;

	pl->file.count_sector_vertex = 0;
	count = 3;
	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	while (pl->file.split[count] != NULL)
	{
		pl->file.count_sector_vertex++;
		// s = ft_strdup(pl->file.split[count]);
		count++;
		// ft_strdel(s);

	}
	pl->file.count_sector_vertex /= 2;
	pl->file.count_sectors++;
	pl->file.tmp[pl->file.count_sectors] = pl->file.count_sector_vertex;
	if (pl->file.split)
		ft_strdel(pl->file.split);
}

void		ft_alloc_save_sectors(char *ag, t_new_player *pl)
{
	t_new_xy		*vertex;

	vertex = ft_malloc_sec_vertex(pl, ag);
	pl->file.count_sectors = 0;
	pl->file.i = 0;
	while ((pl->file.res = get_next_line(pl->file.fd, &pl->file.line)) > 0)
	{
		if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'v')) != NULL)
			vertex = ft_vertex_save(pl, vertex);
		else if ((pl->file.ptr_my = ft_strchr(pl->file.line, (int)'s')) != NULL)
			ft_sector_save(pl, vertex);
		ft_strdel(&pl->file.line);
		free(pl->file.line);
	}
	free(pl->file.line);
}

t_new_xy	*ft_malloc_sec_vertex(t_new_player *pl, char *v)
{
	t_new_xy		*vertex;

	if ((pl->file.fd = open(v, O_RDONLY)) < 0)
		perror("Error: bad file");
	vertex = ft_my_malloc(sizeof(t_new_xy) * (pl->file.vertex_count));
	pl->sectors = ft_my_malloc(sizeof(t_new_sector) * (pl->file.count_sectors + 1));
	pl->sectors_nb = pl->file.count_sectors + 1;
	return (vertex);
}

t_new_xy	*ft_vertex_save(t_new_player *pl, t_new_xy *vertex)
{
	int	count;

	count = 2;
	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	while(pl->file.split[count] != NULL)
	{
		vertex[pl->file.i].y = ft_atoi(pl->file.split[1]);
		vertex[pl->file.i].x = ft_atoi(pl->file.split[count]);
		printf("NUM: %d [ x:%f ], [ y:%f ]\n",(pl->file.i),  vertex[pl->file.i].y, vertex[pl->file.i].x);
		pl->file.i++;
		count++;
	}
	if (pl->file.split)
		ft_strdel(pl->file.split);
	return (vertex);
}

void		ft_sector_save(t_new_player *pl, t_new_xy *vertex)
{
	t_new_sector	*sector;
	int				number;
	int				v_c;
	int				s_c;

	sector = &pl->sectors[pl->file.count_sectors];
	number = pl->file.tmp[pl->file.count_sectors];
	pl->sectors[pl->file.count_sectors].npoints = pl->file.count_sector_vertex;
	sector->neighbors = ft_my_malloc(sizeof(char) * (number + 1));
	sector->vertex = ft_my_malloc(sizeof(t_new_xy) * number);
	sector->npoints = number;
	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	sector->floor = ft_atoi(pl->file.split[1]);
	sector->ceil = ft_atoi(pl->file.split[2]);
	v_c = 1;
	s_c = 3;
	while (number--)
	{
		sector->vertex[v_c].x = \
		vertex[ft_atoi(pl->file.split[s_c])].x;
		sector->vertex[v_c].y = \
		vertex[ft_atoi(pl->file.split[s_c])].y;
		printf("NUMBER  : %d, Y  : %f, X   : %f\n", v_c, \
		 sector->vertex[v_c].y, sector->vertex[v_c].x);
		v_c++;
		s_c++;
	}
	sector->vertex[0].x = vertex[ft_atoi(pl->file.split[s_c - 1])].x;
	sector->vertex[0].y = vertex[ft_atoi(pl->file.split[s_c - 1])].y;
	number = pl->file.tmp[pl->file.count_sectors];
	v_c = 0;
	while (number--)
	{
		sector->neighbors[v_c] = ft_atoi(pl->file.split[s_c]);
		s_c++;
		v_c++;
	}
	pl->file.count_sectors++;
	// if (pl->file.split)
	// 	ft_strdel(pl->file.split);
}