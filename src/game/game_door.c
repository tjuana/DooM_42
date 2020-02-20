/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/02/20 13:56:33 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static void ft_game_door_init(t_new_player *pl, int	*sec_arr)
**	Function to init array of doors
** **************************************************************************
*/

static void	ft_game_door_init(t_new_player *pl, int *sec_arr)
{
	int	i;

	i = -1;
	while (++i < pl->door_all)
	{
		pl->doors[i].s_nb = sec_arr[i];
		pl->doors[i].spd = 0.5;
		pl->doors[i].max_d = 20;
		pl->doors[i].min_d = 0;
		pl->doors[i].state = 0;
	}
}

/*
** **************************************************************************
**	static void ft_game_door_total(t_new_player *pl)
**	Function to countdown doors and malloc them
** **************************************************************************
*/

void		ft_game_door_total(t_new_player *pl)
{
	int	i;
	int	sec_arr[MAX_DOORS];

	pl->door_all = 0;
	i = -1;
	while (++i < pl->sectors_nb)
	{
		if ((pl->sectors[i].ceil == 0) && (pl->sectors[i].floor == 0))
		{
			sec_arr[pl->door_all] = i;
			if (pl->door_all++ >= MAX_DOORS)
			{
				ft_putstr_fd("Too much doors", 2);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (pl->door_all > 0)
		pl->doors = (t_new_door *)ft_my_malloc(sizeof(t_new_door) * \
		pl->door_all);
	ft_game_door_init(pl, sec_arr);
}

/*
** **************************************************************************
**	void door_сlick(t_new_player *pl, t_new_sub_ev *se)
**	Function to start lift door when pressed
** **************************************************************************
*/

void		ft_game_door_but_сlick(t_new_player *pl, t_new_sub_ev *se)
{
	int	d_nb;
	int	d_sec_nb;
	int	i;

	i = -1;
	d_nb = -1;
	if ((pl->door_all == -1) || (pl->but_all == -1))
	{
		ft_game_door_total(pl);
		ft_game_but_total(pl);
	}
	if (pl->door_all < 1 || (ft_game_but_script(pl, ft_game_but_detect(pl), se) == 1))
		return ;
	d_sec_nb = ft_game_door_detect(pl);
	while (++i < pl->door_all)
		if (pl->doors[i].s_nb == d_sec_nb)
			d_nb = i;
	if ((d_nb == -1) || (pl->doors[d_nb].state == 1))
		return ;
	else
	{
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
			"win_game_doortext"), GUI_ELEM_VISIBLE);
		sound(pl, "Sounds/door.wav", 3);
	}
	pl->door_nb = d_nb;
	if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[d_nb].max_d)
	{
		se->wsad[4] = 1;
	}
	else
	{
		se->wsad[4] = 0;
	}
}

/*
** **************************************************************************
**	void door(t_new_player *pl)
**	Function to door open process
** **************************************************************************
*/

void		door(t_new_player *pl, t_new_sub_ev *se)
{
	int	d_nb;
	int	d_sec_nb;

	d_nb = pl->door_nb;
	d_sec_nb = 0;
	if (pl->door_all < 1 || (d_nb > pl->door_all) || d_nb < 0)
		return ;
	d_sec_nb = pl->doors[d_nb].s_nb;
	if (((pl->sectors[d_sec_nb].ceil + pl->doors[d_nb].spd) \
	<= pl->doors[d_nb].max_d) && (se->wsad[4] == 1))
		pl->sectors[d_sec_nb].ceil += pl->doors[d_nb].spd;
	else if (se->wsad[4] == 1 && pl->doors[d_nb].state == 1)
	{
		// Попробовать сделать так, чтобы операция проделывалась
		// всего один раз (!)
		ft_gui_elem_set_status(\
			ft_gui_search_elem_by_name(((t_wolf3d*)pl->wolf3d)->gui.dom, \
			"win_game_doortext"), GUI_ELEM_HIDDEN);
	}
	pl->doors[d_nb].state = 1;
}
