/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/01/27 15:58:01 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	nearz_change(t_player *pl)
{
	printf(" 1 - nearz_change\n\
	pl->nearz==%f (1e-4f) || pl->nearside==%f (1e-5f) \n\
	pl->farz==%f (5) ||pl->farside==%f (20)\
	\n", pl->nearz, pl->nearside, pl->farz, pl->farside);
	pl->nearz += 1;//1e-5f

	/*	pl->nearz = 0;//1e-4f 
    pl->nearside = 0;//1e-5f
	pl->farz = 0;//5
	pl->farside = 0;//20*/
}

static void	nearside_change(t_player *pl)
{
	printf(" 2 - nearside_change\n\
	pl->nearz==%f (1e-4f) || pl->nearside==%f (1e-5f) \n\
	pl->farz==%f (5) ||pl->farside==%f (20)\
	\n", pl->nearz, pl->nearside, pl->farz, pl->farside);
	pl->nearside += 1;

	/*	pl->nearz = 0;//1e-4f
    pl->nearside = 0;//1e-5f
	pl->farz = 0;//5
	pl->farside = 0;//20*/
}

static void	farz_change(t_player *pl)
{
	printf(" 3 - farz_change\n\
	pl->nearz==%f (1e-4f) || pl->nearside==%f (1e-5f)  \n\
	pl->farz==%f (5) ||pl->farside==%f (20)\
	\n", pl->nearz, pl->nearside, pl->farz, pl->farside);
	pl->farz += 1;

	/*	pl->nearz = 0;//1e-4f
    pl->nearside = 0;//1e-5f
	pl->farz = 0;//5
	pl->farside = 0;//20*/
}

static void	farside_change(t_player *pl)
{
	printf(" 4 - farside_change\n\
	pl->nearz==%f (1e-4f) || pl->nearside==%f (1e-5f)  \n\
	pl->farz==%f (5) ||pl->farside==%f (20)\
	\n", pl->nearz, pl->nearside, pl->farz, pl->farside);
	pl->farside += 1;
	
	/*	pl->nearz = 0;//1e-4f
    pl->nearside = 0;//1e-5f
	pl->farz = 0;//5
	pl->farside = 0;//20*/
}

/*
** **************************************************************************
**	static void	sub_events_2(t_sub_ev *se, t_player *pl)
**	Third function to manage key input
** **************************************************************************
*/

static void	sub_events_2(t_sub_ev *se, t_player *pl)
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
	if (se->ev.key.keysym.sym == '1' && (se->ev.type == SDL_KEYDOWN))
		nearz_change(pl);
	if (se->ev.key.keysym.sym == '2' && (se->ev.type == SDL_KEYDOWN))
		nearside_change(pl);
	if (se->ev.key.keysym.sym == '3' && (se->ev.type == SDL_KEYDOWN))
		farz_change(pl);
	if (se->ev.key.keysym.sym == '4' && (se->ev.type == SDL_KEYDOWN))
		farside_change(pl);
}

/*
** **************************************************************************
**	static int sub_events(t_sub_ev *se, t_player *pl)
**	Second function to manage key input
** **************************************************************************
*/

static int	sub_events(t_sub_ev *se, t_player *pl)
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
**	int events(t_sub_ev *se, t_player *pl)
**	First function to manage key input
** **************************************************************************
*/

int			events(t_sub_ev *se, t_player *pl)
{
	while (SDL_PollEvent(&se->ev))
	{
		se->ev.type == SDL_QUIT ? se->quit = 1 : se->quit;
		if (se->ev.type)
		{
			if (se->ev.type == SDL_KEYDOWN || se->ev.type == SDL_KEYUP)
			{
				if (se->ev.key.keysym.sym)
					if (!sub_events(se, pl))
						return (0);
				if (se->ev.type == SDL_QUIT)
				{
					UnloadData(pl);
					SDL_Quit();
					return (0);
				}
			}
		}
	}
	return (1);
}
