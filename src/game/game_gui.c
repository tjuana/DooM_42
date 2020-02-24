/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:15:04 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 18:37:59 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_game_gui_dead(t_wolf3d *w)
** **************************************************************************
*/

void	ft_game_gui_dead(t_wolf3d *w)
{
	t_new_player	*pl;

	pl = ((t_new_temp*)w->new_data)->pl;
	if (w->gui.mode != GUI_MD_GAME)
		return ;
	if (pl->status == PL_STATUS_DEAD)
	{
		sleep(3);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_diedtext"), GUI_ELEM_HIDDEN);
		ft_gui_elem_set_status(ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_diedbg"), GUI_ELEM_HIDDEN);
		w->player_status = 0;
		ft_game_end_game(pl, pl->file.ag);
		return ;
	}
}

/*
** **************************************************************************
**	void ft_game_gui_exit(t_wolf3d *w)
** **************************************************************************
*/

void	ft_game_gui_exit(t_wolf3d *w)
{
	t_new_player	*pl;

	pl = ((t_new_temp*)w->new_data)->pl;
	if (w->gui.mode != GUI_MD_GAME)
		return ;
	if (pl->status == PL_STATUS_EXIT_GAME)
	{
		sleep(3);
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(w->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
		w->player_status = 0;
		w->sdl->running = 0;
		return ;
	}
}

/*
** **************************************************************************
**	void ft_game_set_dead(t_new_player *pl, t_list *dom)
** **************************************************************************
*/

void	ft_game_set_dead(t_new_player *pl, t_list *dom)
{
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(dom, \
		"win_game_diedtext"), GUI_ELEM_VISIBLE);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(dom, \
		"win_game_diedbg"), GUI_ELEM_VISIBLE);
	pl->status = PL_STATUS_DEAD;
}

/*
** **************************************************************************
**	void ft_game_set_exit(t_new_player *pl, t_list *dom)
** **************************************************************************
*/

void	ft_game_set_exit(t_new_player *pl, t_list *dom)
{
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(dom, \
		"win_game_exittext"), GUI_ELEM_VISIBLE);
	ft_gui_elem_set_status(ft_gui_search_elem_by_name(dom, \
		"win_game_exitbg"), GUI_ELEM_VISIBLE);
	pl->status = PL_STATUS_EXIT_GAME;
}
