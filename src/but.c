/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   but.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/25 21:44:07 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int but_door_sec(t_player *pl)
**	Function to find door_nb to open
** **************************************************************************
*/

static int	but_door_sec(t_player *pl)
{
	int	i;
	int	j;
	int	s_nb;

	i = -1;
	j = -1;
	s_nb = -1;
	while (++i < pl->sectors[pl->sector].npoints)
	{
		j = -1;
		s_nb = pl->sectors[pl->sector].neighbors[i];
		if ((pl->sectors[pl->sector].neighbors[i] >= 0) && \
		(pl->sectors[s_nb].floor == 0 && pl->sectors[s_nb].ceil == 0))
		{
			while (++j < pl->door_all)
				if (pl->doors[j].s_nb == s_nb)
					return (j);
		}
	}
	j = -1;
	return (j);
}

/*
** **************************************************************************
**	static int	but_open_door(t_player *pl, int but_nb, t_sub_ev *se)
**	Function to open door in this sec
** **************************************************************************
*/

static int	but_open_door(t_player *pl, int but_nb, t_sub_ev *se)
{
	int	d_sec_nb;

	d_sec_nb = 0;
	if ((pl->door_nb = but_door_sec(pl)) >= 0)
	{
		d_sec_nb = pl->doors[pl->door_nb].s_nb;
		if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[pl->door_nb].max_d)
		{
			se->wsad[4] = 1;
			return (1);
		}
		else
		{
			se->wsad[4] = 0;
			pl->buttons[but_nb].state = -1;
		}
	}
	else
		pl->door_nb = -1;
	return (0);
}

/*
** **************************************************************************
**	int but_script(t_player *pl, int sec_nb, t_sub_ev *se)
**	Function to do button scipts
** **************************************************************************
*/

int			but_script(t_player *pl, int sec_nb, t_sub_ev *se)
{
	int	i;
	int	d_nb;
	int	d_sec_nb;
	int	but_nb;

	d_nb = -1;
	d_sec_nb = -1;
	i = -1;
	if (sec_nb <= -1)
		return (0);
	while (++i < pl->but_all)
		if (pl->buttons[i].s_nb == sec_nb)
			but_nb = i;
	if ((but_nb > -1) && (pl->buttons[but_nb].state == -2))
		return (but_open_door(pl, but_nb, se));
	if ((but_nb > -1) && (pl->buttons[but_nb].state == -4))
		*pl = *load_next(pl);
	return (0);
}

/*
** **************************************************************************
**	static void but_init(t_player *pl, int *sec_arr)
**	Function to init array of buttons
**	state == -1 - do nothing, (-2) - open door in that sector,
**	(-3) - move platform, (-4) - end lvl
** **************************************************************************
*/

static void	but_init(t_player *pl, int *sec_arr)
{
	int	i;

	i = -1;
	while (++i < pl->but_all)
	{
		pl->buttons[i].s_nb = sec_arr[i];
		pl->buttons[i].state = pl->sectors[pl->buttons[i].s_nb].neighbors[0];
	}
}

/*
** **************************************************************************
**	static void but_total(t_player *pl)
**	Function to countdown buttons
** **************************************************************************
*/

void		but_total(t_player *pl)
{
	int	sec_arr[MAX_BUT];
	int	i;

	pl->but_all = 0;
	i = -1;
	while (++i < pl->sectors_nb)
	{
		if (pl->sectors[i].npoints == 2)
		{
			sec_arr[pl->but_all] = i;
			if (pl->but_all++ >= MAX_BUT)
			{
				ft_putstr_fd("Too much buttons", 2);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (pl->but_all > 0)
		if (!(pl->buttons = (t_but *)malloc(sizeof(t_but) * pl->but_all)))
		{
			ft_putstr_fd("Buttons malloc.\n", 2);
			exit(EXIT_FAILURE);
		}
	but_init(pl, sec_arr);
}
