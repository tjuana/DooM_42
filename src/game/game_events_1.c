/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:20:12 by drafe             #+#    #+#             */
/*   Updated: 2020/02/19 17:37:42 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static void	ft_game_sub_events_2(t_new_sub_ev *se, t_new_player *pl)
**	Third function to manage key input
** **************************************************************************
*/

static void		ft_game_sub_events_2(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == 'q')
	{
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
			"win_game_diedtext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
			"win_game_diedbg"), GUI_ELEM_HIDDEN);
	}
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
}

/*
** **************************************************************************
**	static int ft_game_sub_events(t_new_sub_ev *se, t_new_player *pl)
**	Second function to manage key input
** **************************************************************************
*/

static int		ft_game_sub_events(t_new_sub_ev *se, t_new_player *pl)
{
	if (se->ev.key.keysym.sym == SDLK_ESCAPE)
	{
		se->quit = 1;
		return (0);
	}
	if (se->ev.key.keysym.sym == ' ' && se->ground && pl->fly != 1)
	{
		pl->velo.z += 0.75f;
		se->falling = 1;
	}
	if (se->ev.key.keysym.sym == SDLK_LCTRL)
		se->ducking = se->ev.type == SDL_KEYDOWN;
	ft_game_sub_events_2(se, pl);
	return (1);
}

/*
** **************************************************************************
**	int events(t_new_sub_ev *se, t_new_player *pl)
**	First function to manage key input
** **************************************************************************
*/

static	void	ft_game_mouse_events(t_new_sub_ev *se, t_new_player *pl)
{
	t_list		*list;
	t_gui_elem	*elem;
	if (se->ev.button.button == SDL_BUTTON_LEFT)
	{
		pl->count_sprite = 10;
		if (pl->bullet_count > 0)
		{
			pl->bullet_count--;
			list = ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, "win_game_hud_pistolcount");
			elem = list->content;
			free(elem->str);
			elem->str = ft_itoa(pl->bullet_count);
		}
		else if (pl->live_count > 0)
		{
			pl->live_count -= 10;
			list = ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, "win_game_hud_livescount");
			elem = list->content;
			free(elem->str);
			elem->str = ft_itoa(pl->live_count);
		}
		if (pl->live_count <= 0)
		{
			ft_gui_elem_set_status(\
				ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
				"win_game_diedtext"), GUI_ELEM_VISIBLE);
			ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
				"win_game_diedbg"), GUI_ELEM_VISIBLE);
		}
	}
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
			pl->velo.z = 1.3f;
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
