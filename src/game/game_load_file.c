/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/12 20:33:15 by drafe            ###   ########.fr       */
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
	
	SDL_Delay(50);
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
	t_new_player	*pl_next;

	pl_next = NULL;
	printf("LVL==%s\n", pl->lvl);
	if (pl->lvl == NULL)
		end_game(pl);
	pl_next = (t_new_player *)ft_my_malloc(sizeof(t_new_player));
	pl_next->sectors_nb = 0;
	pl_next->lvl = pl->lvl;
	pl_next->win = pl->win;
	ft_my_parse_map(pl_next, pl->lvl);
	pl->srf ? SDL_FreeSurface(pl->srf) : 0;
	pl->srf = NULL;
	free(pl);
	pl = NULL;
	pl = pl_next;
	pl->srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
	!pl->srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	pl->rend = SDL_GetRenderer(pl->win);
	!pl->rend ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	return (pl);
}
