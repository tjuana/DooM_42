/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   but.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/23 18:58:18 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int but_s_door(t_player *pl)
**	Function to select door to open in this sec
** **************************************************************************
*/

static int	but_s_door(t_player *pl)
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
	printf("JJJ==%d\n", j);
	j = -1;
	return (j);
}

/*
** **************************************************************************
**	int but_script(t_player *pl, int but_nb, t_subevents *se)
**	Function to do button scipts
** **************************************************************************
*/

int			but_script(t_player *pl, int sec_nb, t_subevents *se)
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
	{
		if (pl->buttons[i].s_nb == sec_nb)
			but_nb = i;
	}
	if ((but_nb > -1) && (pl->buttons[but_nb].state == -2))
	{
		d_nb = but_s_door(pl);
		if (d_nb >= 0)
		{
			pl->door_nb = d_nb;
			d_sec_nb = pl->doors[d_nb].s_nb;
			if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[d_nb].max_d)
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
	}
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
	while(++i < pl->but_all)
	{
		pl->buttons[i].s_nb = sec_arr[i];
		pl->buttons[i].state = pl->sectors[pl->buttons[i].s_nb].neighbors[0];
		printf("button%d state=%d s_nb==%d npo==%d\n", i, pl->buttons[i].state, pl->buttons[i].s_nb, pl->sectors[pl->buttons[i].s_nb].npoints);
		printf("1==%d \n", pl->sectors[pl->buttons[i].s_nb].neighbors[1]);
		printf("0==%d\n", pl->sectors[pl->buttons[i].s_nb].neighbors[0]);
	}
}

/*
** **************************************************************************
**	static void but_total(t_player *pl)
**	Function to countdown buttons
** **************************************************************************
*/

void	but_total(t_player *pl)
{	
	int	sec_arr[MAX_BUT];
	int	i;
	int	*ptr;

	pl->but_all = 0;
	i = -1;
	while(++i < pl->sectors_nb)
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
	ptr = sec_arr;
	if (pl->but_all > 0)
		if (!(pl->buttons = (t_but *)malloc(sizeof(t_but) * pl->but_all)))
			exit(EXIT_FAILURE);
	but_init(pl, ptr);
}

/*

static void	door_total(t_player *pl)
{	
	int	i;
	int	sec_arr[MAX_DOORS];
	int	*ptr;

	pl->door_all = 0;
	i = -1;
	while(++i < pl->sectors_nb)
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
	ptr = sec_arr;
	if (pl->door_all > 0)
		if (!(pl->doors = (t_door *)malloc(sizeof(t_door) * pl->door_all)))
			exit(EXIT_FAILURE);
	door_init(pl, ptr);
}
*/