/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/13 19:48:17 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void end_game(t_new_player *pl)
**	Function to end game
** **************************************************************************
*/

void			end_game(t_new_player *pl)
{
	SDL_Delay(777);
	if (pl)
		free(pl);
	exit(EXIT_SUCCESS);
}

/*
** **************************************************************************
**	t_new_player *load_next(t_new_player *pl)
**	Function to open next map
** **************************************************************************
*/

t_new_player	*load_next(t_new_player *pl)
{
	char			*lvl;
	int				j;
	t_new_sector	*sector;

	j = -1;
	while (j++ < pl->sectors->npoints)
	{
		sector = &pl->sectors[j];
		free(sector->vertex);
		sector->vertex = NULL;
		free(sector->neighbors);
		sector->neighbors = NULL;
	}
	free(pl->sectors);
	pl->sectors = NULL;
	lvl = ft_strdup(pl->lvl);
	ft_strdel(&pl->lvl);
	ft_my_parse_map(pl, lvl);
	ft_strdel(&lvl);
	free(pl->doors);
	pl->doors = NULL;
	free(pl->buttons);
	pl->buttons = NULL;
	return (pl);
}
