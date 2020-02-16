/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_but.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/02/16 12:46:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	static int but_new_door_sec(t_new_player *pl)
**	Function to find door_nb to open
** **************************************************************************
*/

static int	but_new_door_sec(t_new_player *pl)
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
**	static int	but_open_door(t_new_player *pl, int but_nb, t_new_sub_ev *se)
**	Function to open door in this sec
** **************************************************************************
*/

static int	but_open_door(t_new_player *pl, int but_nb, t_new_sub_ev *se)
{
	int	d_sec_nb;

	d_sec_nb = 0;
	if ((pl->door_nb = but_new_door_sec(pl)) >= 0)
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
**	int but_script(t_new_player *pl, int sec_nb, t_new_sub_ev *se)
**	Function to do button scipts
** **************************************************************************
*/

int			but_script(t_new_player *pl, int sec_nb, t_new_sub_ev *se)
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
	ft_strdel(&pl->lvl);
	return (0);
}

/*
** **************************************************************************
**	static void but_init(t_new_player *pl, int *sec_arr)
**	Function to init array of buttons
**	state == (-2) - open door in that sector, (-4) - end lvl
** **************************************************************************
*/

static void	but_init(t_new_player *pl, int *sec_arr)
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
**	static void but_total(t_new_player *pl)
**	Function to countdown buttons
** **************************************************************************
*/

void		but_total(t_new_player *pl)
{
	int	i;
	int	sec_arr[MAX_BUT];
	
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
		pl->buttons = (t_new_but *)ft_my_malloc(sizeof(t_new_but) * \
		pl->but_all);
	but_init(pl, sec_arr);
}
