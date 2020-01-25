/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/25 21:44:58 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void door_init(t_player *pl, int	*sec_arr)
**	Function to init array of doors
** **************************************************************************
*/

static void	door_init(t_player *pl, int *sec_arr)
{
	int	i;

	i = -1;
	while (++i < pl->door_all)
	{
		pl->doors[i].s_nb = sec_arr[i];
		pl->doors[i].spd = 0.1;
		pl->doors[i].max_d = 20;
		pl->doors[i].min_d = 0;
		pl->doors[i].state = 0;
	}
}

/*
** **************************************************************************
**	static void door_total(t_player *pl)
**	Function to countdown doors and malloc them
** **************************************************************************
*/

static void	door_total(t_player *pl)
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
		if (!(pl->doors = (t_door *)malloc(sizeof(t_door) * pl->door_all)))
			exit(EXIT_FAILURE);
	door_init(pl, sec_arr);
}

/*
** **************************************************************************
**	void door_сlick(t_player *pl, t_sub_ev *se)
**	Function to start lift door when pressed
** **************************************************************************
*/

void		door_but_сlick(t_player *pl, t_sub_ev *se)
{
	int	d_nb;
	int	d_sec_nb;
	int	i;

	i = -1;
	d_nb = -1;
	if ((pl->door_all == -1) || (pl->but_all == -1))
	{
		door_total(pl);
		but_total(pl);
	}
	if (pl->door_all < 1 || (but_script(pl, but_detect(pl), se) == 1))
		return ;
	d_sec_nb = door_detect(pl);
	while (++i < pl->door_all)
		if (pl->doors[i].s_nb == d_sec_nb)
			d_nb = i;
	if ((d_nb == -1) || (pl->doors[d_nb].state == 1))
		return ;
	pl->door_nb = d_nb;
	if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[d_nb].max_d)
		se->wsad[4] = 1;
	else
		se->wsad[4] = 0;
}

/*
** **************************************************************************
**	void door(t_player *pl)
**	Function to door open process
** **************************************************************************
*/

void		door(t_player *pl, t_sub_ev *se)
{
	int	d_nb;
	int	d_sec_nb;

	d_nb = pl->door_nb;
	d_sec_nb = 0;
	if ((pl->door_all < 1) || (d_nb > pl->door_all))
		return ;
	d_sec_nb = pl->doors[d_nb].s_nb;
	if (((pl->sectors[d_sec_nb].ceil + pl->doors[d_nb].spd) \
	<= pl->doors[d_nb].max_d) && (se->wsad[4] == 1))
		pl->sectors[d_sec_nb].ceil += pl->doors[d_nb].spd;
	pl->doors[d_nb].state = 1;
}
