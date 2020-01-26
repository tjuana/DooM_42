/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/01/26 23:31:34 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static void	sub_events_2(t_new_sub_ev *se, t_new_player *pl)
**	Third function to manage key input
** **************************************************************************
*/

static void	sub_events_2(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == 'w')
		se->wsad[0] = se->ev.type == SDL_KEYDOWN;
	if (se->ev.key.keysym.sym == 's')
		se->wsad[1] = se->ev.type == SDL_KEYDOWN;
	if (se->ev.key.keysym.sym == 'a')
		se->wsad[2] = se->ev.type == SDL_KEYDOWN;
	if (se->ev.key.keysym.sym == 'd')
		se->wsad[3] = (se->ev.type == SDL_KEYDOWN);
	if (se->ev.key.keysym.sym == SDLK_LSHIFT)
		se->wsad[6] = (se->ev.type == SDL_KEYDOWN);
	if (se->ev.key.keysym.sym == 'e' && (se->ev.type == SDL_KEYDOWN))
		door_but_сlick(pl, se);
}

/*
** **************************************************************************
**	static int sub_events(t_new_sub_ev *se, t_new_player *pl)
**	Second function to manage key input
** **************************************************************************
*/

static int	sub_events(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == SDLK_ESCAPE)
	{
		UnloadData(pl);
		SDL_Quit();
		return (0);
	}
	if (se->ev.key.keysym.sym == ' ' && se->ground)
	{
		pl->velocity.z += 0.5;
		se->falling = 1;
	}
	if (se->ev.key.keysym.sym == SDLK_LCTRL)
	{
		se->ducking = se->ev.type == SDL_KEYDOWN;
		se->falling = 1;
	}
	sub_events_2(se, pl);
	return (1);
}

/*
** **************************************************************************
**	int events(t_new_sub_ev *se, t_new_player *pl)
**	First function to manage key input
** **************************************************************************
*/

int			events(t_new_sub_ev *se, t_new_player *pl)
{
	while (SDL_PollEvent(&se->ev))
	{
		// se->ev.type == SDL_QUIT ? se->quit = 1 : se->quit;
		if (se->ev.type)
		{
			if (se->ev.type == SDL_KEYDOWN || se->ev.type == SDL_KEYUP)
			{
				if (se->ev.key.keysym.sym)
					if (!sub_events(se, pl))
						return (0);
				// if (se->ev.type == SDL_QUIT)
				// {
				// 	UnloadData(pl);
				// 	SDL_Quit();
				// 	exit (0);
				// 	return (0);
				// }
			}
		}
	}
	return (1);
}
