/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:16:26 by tjuana            #+#    #+#             */
/*   Updated: 2020/02/19 21:27:36 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector3	*ft_game_vertex_save(t_new_player *pl, t_vector3 *vertex)
{
	int	count;

	count = 2;
	if (!(pl->file.split = ft_strsplit(pl->file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	while (pl->file.split[count] != NULL)
	{
		vertex[pl->file.i].y = ft_atoi(pl->file.split[1]);
		vertex[pl->file.i].x = ft_atoi(pl->file.split[count]);
		pl->file.i++;
		count++;
	}
	if (&pl->file.split[0])
		ft_2arrclean(&pl->file.split);
	return (vertex);
}

void		ft_game_sector_save(t_new_player *pl, t_vector3 *vertex)
{
	t_new_sector	*sector;
	int				number;

	sector = &pl->sectors[pl->file.count_sectors2];
	number = pl->file.tmp[pl->file.count_sectors2];
	pl->sectors[pl->file.count_sectors2].npoints = pl->file.count_sector_vertex;
	sector->neighbors = ft_my_malloc(sizeof(int) * (number + 1));
	sector->vertex = ft_my_malloc(sizeof(t_vector3) * (number + 1));
	sector->npoints = number;
	ft_game_fill_the_sector(sector, number, pl->file, vertex);
	pl->file.count_sectors2++;
}

void		ft_game_fill_the_sector(t_new_sector *sector, int number, \
	t_file_read file, t_vector3 *vertex)
{
	int				v_c;
	int				s_c;

	if (!(file.split = ft_strsplit(file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	sector->floor = ft_atoi(file.split[1]);
	sector->ceil = ft_atoi(file.split[2]);
	v_c = 1;
	s_c = 3;
	while (number--)
	{
		sector->vertex[v_c].x = vertex[ft_atoi(file.split[s_c])].x;
		sector->vertex[v_c++].y = vertex[ft_atoi(file.split[s_c++])].y;
	}
	sector->vertex[0] = vertex[ft_atoi(file.split[s_c - 1])];
	number = file.tmp[file.count_sectors2];
	v_c = 0;
	while (number--)
	{
		sector->neighbors[v_c] = ft_atoi(file.split[s_c]);
		v_c++;
		s_c++;
		if (ft_atoi(file.split[s_c - 1]) >= (file.count_sectors + 1))
			ft_error("BAD NEIGHBOUR");
	}
	if (&file.split[0])
		ft_2arrclean(&file.split);
}

void		ft_game_player_save(t_new_player *pl)
{
	t_vector3	v;
	int			n;

	if (!(pl->file.split = ft_strsplit(pl->file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	v.x = (float)ft_atoi(pl->file.split[1]);
	v.y = (float)ft_atoi(pl->file.split[2]);
	n = ft_atoi(pl->file.split[4]);
	ft_game_player_init(pl, &v, &n);
	pl->pos.z = pl->sectors[pl->sector].floor + EYE_H * 2;
	if (pl->file.split)
		ft_2arrclean(&pl->file.split);
}

void		ft_game_level_save(t_new_player *pl)
{
	if (!(pl->file.split = ft_strsplit(pl->file.ptr_my, '\t')))
		ft_error("MALLOC_SPLIT");
	if (!(pl->lvl = ft_strdup(pl->file.split[1])))
		ft_error("fuck_off");
	if (&pl->file.split[0])
		ft_2arrclean(&pl->file.split);
}
