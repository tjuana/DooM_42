/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/02/03 17:52:33 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void end_game(t_new_player *pl)
**	Function to end game
** **************************************************************************
*/

void	end_game(t_new_player *pl)
{	
	//// printf "END OF GAME!!!"
	SDL_Delay(50);
	//free and clean all old stuff
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

t_new_player		*load_next(t_new_player *pl)
{
	t_new_player	*pl_next;

	pl_next = NULL;
	if (pl->lvl == NULL)
		end_game(pl);
	if (!(pl_next = (t_new_player *)malloc(sizeof(t_new_player))))
	{
		ft_putstr_fd("load_next malloc error.\n", 2);
		exit(EXIT_FAILURE);
	}
	pl_next->sectors_nb = 0;
	pl_next->win = pl->win;
	// load_file(pl->lvl, pl_next);
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
	return(pl);
}

/*
** **************************************************************************
**	int but_script(t_new_player *pl, int sec_nb, t_subevents *se)
**	Function to do button scipts
** **************************************************************************
*/