/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/24 18:51:42 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static void	ft_game_sub_events_moving(t_new_sub_ev *se, t_new_player *pl)
**	Third function to manage key input
** **************************************************************************
*/

void			ft_game_sub_events_moving(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == 'q')
		ft_game_hidden_message(((t_wolf3d*)pl->wolf3d)->gui.dom);
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
		ft_game_door_but_сlick(pl, se);
	if (se->ev.key.keysym.scancode == SDL_SCANCODE_EQUALS)
		pl->flag_move_neighbors = 1;
	if (se->ev.key.keysym.scancode == SDLK_MINUS)
		pl->flag_move_neighbors = -1;
	if (se->ev.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		pl->flag_move_neighbors = 0;
	if (se->ev.key.keysym.sym == 'f' && (se->ev.type == SDL_KEYDOWN))
		ft_game_end_game(pl, pl->file.ag);
}

void			ft_game_sub_events_player(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == ' ' && se->ground && pl->fly != 1)
	{
		pl->velo.z += 0.75f;
		se->falling = 1;
		if (pl->lunar == 1)
			pl->velo.z = .65f;
	}
	if (se->ev.key.keysym.sym == SDLK_LCTRL)
		se->ducking = se->ev.type == SDL_KEYDOWN;
	if (se->ev.key.keysym.sym == SDLK_q && pl->fly == 1 && \
		pl->pos.z < pl->sectors[pl->sector].ceil - 2)
	{
		pl->pos.z += 0.3f;
		se->falling = 0;
	}
	if (se->ev.key.keysym.sym == SDLK_e && pl->fly == 1)
	{
		pl->pos.z -= 0.3f;
		se->falling = 1;
	}
	if (se->ev.key.keysym.sym == SDLK_l)
		pl->lunar = 1;
}

/*
** **************************************************************************
**	int events(t_new_sub_ev *se, t_new_player *pl)
**	First function to manage key input
** **************************************************************************
*/

void			ft_game_mouse_events(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.button.button == SDL_BUTTON_LEFT)
		ft_game_mouse_events_click(pl);
	if (se->ev.button.button == SDL_BUTTON_RIGHT)
		pl->light = pl->light == 0.5f ? 1.0f : 0.5f;
	if (se->ev.button.button == SDL_BUTTON_MIDDLE)
	{
		se->falling = 1;
		if (pl->fly == 1)
			pl->fly = 0;
		else
		{
			pl->fly = 1;
			pl->velo.z = 0.7f;
			ft_sound_play(pl->sound_fly, 1);
		}
	}
}

int				events(t_new_sub_ev *se, t_new_player *pl)
{
	while (SDL_PollEvent(&se->ev))
	{
		se->ev.type == SDL_QUIT ? se->quit = 1 : se->quit;
		if (se->ev.type)
		{
			if (se->ev.type == SDL_KEYDOWN || se->ev.type == SDL_KEYUP)
			{
				if (se->ev.key.keysym.sym)
					if (!ft_game_sub_events(se, pl))
						return (0);
			}
			if (se->ev.type == SDL_MOUSEBUTTONDOWN)
				ft_game_mouse_events(se, pl);
		}
	}
	return (1);
}

void			ft_game_events(t_new_temp *data)
{
	events(&data->se, data->pl);
}
