/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   but.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/22 21:18:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static void but_init(t_player *pl)
**	Function to init array of buttons
**	state == 4000 - do nothing, 4001 - open door in that sector, 
**	4002 - move platform, 4003 - end lvl
** **************************************************************************
*/

static void	but_init(t_player *pl, int	*sec_arr)
{
	int	i;

	i = -1;
	while(++i < pl->but_all)
	{
		printf("button%d\n", i);
		pl->buttons[i].s_nb = sec_arr[i];
		//pl->buttons[i].spd = 0.1;
		//pl->buttons[i].max_d = 20;
		//pl->buttons[i].min_d = 0;
		pl->buttons[i].state = 4000;
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
		if (pl->sectors[i].npoints == 2)
		{
			sec_arr[pl->but_all] = i;
			if (pl->but_all++ >= MAX_BUT)
			{
				ft_putstr_fd("Too much buttons", 2);
				exit(EXIT_FAILURE);
			}
		}
	ptr = sec_arr;
	if (pl->but_all > 0)
		if (!(pl->buttons = (t_but *)malloc(sizeof(t_but) * pl->but_all)))
			exit(EXIT_FAILURE);
	but_init(pl, ptr);
}
