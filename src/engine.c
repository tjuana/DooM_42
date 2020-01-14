/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/14 18:55:16 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	void engine_preset(t_player *pl)
**	Function to set up some arrays and lists for engine
** **************************************************************************
*/

void		engine_preset(t_player *pl, t_cycle	*cycle)
{
	int	i;
	int	*rend_sec;

	if ((i = -1) && !(rend_sec = (int *)malloc(sizeof(int) * (pl->sectors_nb + 1))))
	{
		ft_putstr_fd("engine_preset - malloc error.\n", 2);
		exit (-1);
	}
	while(++i < pl->sectors_nb)
		rend_sec[i] = 0;
	cycle->rend_sec = rend_sec;
	i = -1;
	while(++i < WIN_W)
		pl->y_top[i] = 0;
	i = -1;
	while(++i < WIN_W)
		pl->y_bot[i] = WIN_H - 1;
	cycle->head = cycle->queue;
	cycle->tail = cycle->queue;
	cycle->head->sec_nb = (int)pl->sector;
	cycle->head->sx1 = 0;
	cycle->head->sx2 = WIN_W - 1;
	if(++cycle->head == cycle->queue + MAX_QUEUE)
		cycle->head = cycle->queue;
}

/*
** **************************************************************************
**	int engine_scale(t_player *pl, int sx1, int sx2)
**	Function to scale floor & ceil
** **************************************************************************
*/

int		engine_scale(t_player *pl, int sx1, int sx2)
{
	pl->scale_1.x = hfov / pl->t1.y;
	pl->scale_1.y = vfov / pl->t1.y;
	pl->scale_2.x = hfov / pl->t2.y;
	pl->scale_2.y = vfov / pl->t2.y;
	//Do perspective transformation
	pl->x1 = WIN_W / 2 - (int)(pl->t1.x * pl->scale_1.x);
	pl->x2 = WIN_W / 2 - (int)(pl->t2.x * pl->scale_2.x);
	//Project our ceiling & floor heights into screen coordinates (Y coordinate)
	pl->ceil.y1a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, pl->t1.y, pl) * pl->scale_1.y);
	pl->floor.y1b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, pl->t1.y, pl) * pl->scale_1.y);
	pl->ceil.y2a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, pl->t2.y, pl) * pl->scale_2.y);
	pl->floor.y2b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, pl->t2.y, pl) * pl->scale_2.y);
	//The same for the neighboring sector
	pl->ceil.ny1a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, pl->t1.y, pl) * pl->scale_1.y);
	pl->floor.ny1b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, pl->t1.y, pl) * pl->scale_1.y);
	pl->ceil.ny2a = WIN_H / 2 - (int)(Yaw(pl->ceil.nyceil, pl->t2.y, pl) * pl->scale_2.y);
	pl->floor.ny2b = WIN_H / 2 - (int)(Yaw(pl->floor.nyfloor, pl->t2.y, pl) * pl->scale_2.y);
	if(pl->x1 >= pl->x2 || pl->x2 < sx1 || pl->x1 > sx2)
		return (0);
	return (1);
}

/*
** **************************************************************************
**	void engine_begin(t_player *pl)
**	Function to start engine calculations and draw all lines
** **************************************************************************
*/

void	engine_begin(t_player *pl)
{
	int			neib;
	t_cycle		cycle;
	t_sector	*sect;//was CONSTx2
	int			s;

	engine_preset(pl, &cycle);
    while(cycle.head != cycle.tail)
	{
        //Pick a sector & slice from the queue to draw
        cycle.current = cycle.tail;//const struct item now = *cycle.tail;
        if(++cycle.tail == cycle.queue + MAX_QUEUE)
			cycle.tail = cycle.queue;
        if(cycle.rend_sec[cycle.current->sec_nb] & 0x21)
			continue; // Odd = still rendering, 0x20 = give up
        ++cycle.rend_sec[cycle.current->sec_nb];
        sect = &pl->sectors[cycle.current->sec_nb];//SECT CREATED
		s = -1;
		while (++s < sect->npoints)
		{
			if (engine_cross(pl, cycle.current->sec_nb, s) == 0)
				continue;
			//Acquire the floor and ceiling heights, relative to where the player's view is
			pl->ceil.yceil = sect->ceil - pl->where.z;
			pl->floor.yfloor = sect->floor - pl->where.z;
			//Check the edge type. neighbor=-1 means wall, other=boundary between two sectors.
			neib = sect->neighbors[s];
			if(neib >= 0) // Is another sector showing through this portal? This permit us draw other sectors after the one where we are
			{
				pl->ceil.nyceil  = pl->sectors[neib].ceil  - pl->where.z;
				pl->floor.nyfloor = pl->sectors[neib].floor - pl->where.z;
			}
			if (engine_scale(pl, cycle.current->sx1, cycle.current->sx2) == 0)
				continue; // Only render if it's visible
			engine_put_lines(pl, &cycle, neib);//Render all.
		}
        ++cycle.rend_sec[cycle.current->sec_nb];
    }  // render any other queued sectors (was while(cycle.head != cycle.tail);)
}
