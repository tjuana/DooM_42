/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/23 16:43:47 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_end_game(t_new_player *pl)
**	Function to end game
** **************************************************************************
*/

void			ft_game_end_game(t_new_player *pl)
{
	(void)pl;
	SDL_Delay(77);
	exit(EXIT_SUCCESS);
}

static void		ft_free(t_new_player *pl, char *lvl)
{
	ft_strdel(&lvl);
	free(pl->doors);
	pl->doors = NULL;
	free(pl->buttons);
	pl->buttons = NULL;
}

/*
** **************************************************************************
**	t_new_player *load_next(t_new_player *pl, char *map)
**	Function to open next map
** **************************************************************************
*/

t_new_player	*load_next(t_new_player *pl, char *map)
{
	char			*lvl;
	int				j;
	int				i;
	t_new_sector	*sector;

	j = -1;
	while (j++ < (pl->file.count_sectors - 1))
	{
		sector = &pl->sectors[j];
		i = -1;
		while (i++ < sector->npoints)
		{
			free(sector->vertex);
			sector->vertex = NULL;
			free(sector->neighbors);
			sector->neighbors = NULL;
		}
	}
	free(pl->sectors);
	pl->sectors = NULL;
	lvl = ft_strdup(map);
	ft_strdel(&map);
	ft_game_my_parse_map(pl, lvl);
	ft_free(pl, lvl);
	return (pl);
}
