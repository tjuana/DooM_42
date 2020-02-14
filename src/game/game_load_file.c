/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/14 17:26:08 by dorange-         ###   ########.fr       */
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
	int i;
	i = -1;
	//better use free(pl);
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
	t_new_player	*pl_next;

	pl_next = NULL;
	printf("LVL==%s\n", pl->lvl);
	if (pl->lvl == NULL)
		end_game(pl);
		
	pl_next = (t_new_player *)ft_my_malloc(sizeof(t_new_player));
	pl_next->srf = pl->srf;
	pl_next->tex = pl->tex;
	pl_next->textures_nb = 15;
	pl_next->sectors_nb = 0;
	pl_next->lvl = pl->lvl;
	pl_next->win = pl->win;
	pl->srf ? SDL_FreeSurface(pl->srf) : 0;
	pl->srf = NULL;
	pl_next->srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
	!pl_next->srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	ft_my_parse_map(pl_next, pl->lvl);
	

	//free(pl);
	pl = NULL;
	pl = pl_next;

	pl->rend = SDL_GetRenderer(pl->win);
	!pl->rend ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	return (pl);
}
