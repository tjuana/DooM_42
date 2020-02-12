/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/02/12 15:24:35 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

/*
** **************************************************************************
**	static int engine_pick_sec(t_new_player *pl)
**	Function to pick a sector & slice from the queue to draw
** **************************************************************************
*/

static int	engine_pick_sec(t_new_player *pl)
{
	pl->cycle.current = pl->cycle.tail;//const struct item now = *cycle.tail;
	if(++pl->cycle.tail == pl->cycle.queue + MAX_QUEUE)
		pl->cycle.tail = pl->cycle.queue;
	if(pl->cycle.rend_sec[pl->cycle.current->sec_nb] & 0x21)
	{
		return (-2); // Odd = still rendering, 0x20 = give up
	}
	++pl->cycle.rend_sec[pl->cycle.current->sec_nb];
	pl->sect = &pl->sectors[pl->cycle.current->sec_nb];//SECT CREATED
	return (-1);
}

/*
** **************************************************************************
**	static void engine_preset(t_new_player *pl)
**	Function to set up some arrays and lists for engine
** **************************************************************************
*/

static void	engine_preset(t_new_player *pl)
{
	int	i;
	int	*rend_sec;

	i = -1;
	rend_sec = (int *)ft_my_malloc(sizeof(int) * (pl->sectors_nb + 1));

	while(++i < pl->sectors_nb)
		rend_sec[i] = 0;
	pl->cycle.rend_sec = rend_sec;
	i = -1;
	while(++i < WIN_W)
		pl->y_top[i] = 0;
	i = -1;
	while(++i < WIN_W)
		pl->y_bot[i] = WIN_H - 1;
	pl->cycle.head = pl->cycle.queue;
	pl->cycle.tail = pl->cycle.queue;
	pl->cycle.head->sec_nb = (int)pl->sector;
	pl->cycle.head->sx1 = 0;
	pl->cycle.head->sx2 = WIN_W - 1;
	if(++pl->cycle.head == pl->cycle.queue + MAX_QUEUE)
		pl->cycle.head = pl->cycle.queue;
}

/*
** **************************************************************************
**	int engine_scale(t_new_player *pl, int sx1, int sx2)
**	Function to scale floor & ceil
** **************************************************************************
*/

int		engine_scale(t_new_player *pl, int sx1, int sx2)/*perspective*/
{
	pl->scale_1.x = hfov / pl->t1.y;
	pl->scale_1.y = vfov / pl->t1.y;
	pl->scale_2.x = hfov / pl->t2.y;
	pl->scale_2.y = vfov / pl->t2.y;
	pl->x1 = WIN_W / 2 - (int)(pl->t1.x * pl->scale_1.x);
	pl->x2 = WIN_W / 2 - (int)(pl->t2.x * pl->scale_2.x);
	pl->ceil.y1a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, pl->t1.y, pl) * pl->scale_1.y);
	pl->floor.y1b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, pl->t1.y, pl) * pl->scale_1.y);
	pl->ceil.y2a = WIN_H / 2 - (int)(Yaw(pl->ceil.yceil, pl->t2.y, pl) * pl->scale_2.y);
	pl->floor.y2b = WIN_H / 2 - (int)(Yaw(pl->floor.yfloor, pl->t2.y, pl) * pl->scale_2.y);
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
**	void engine_begin(t_new_player *pl)
**	Function to start engine calculations and draw all lines
** **************************************************************************
*/

void	engine_begin(t_new_player *pl)
{
	int			neib;
	int			s;
	int 		sector_number;

	printf("=== player_pos: [%f, %f]\n", pl->where.x, pl->where.y);
	sector_number = 0;
	engine_preset(pl);
    while(pl->cycle.head != pl->cycle.tail)
	{
		if ((s = engine_pick_sec(pl)) == -2)
			continue;
		while (++s < pl->sect->npoints)
		{
			if(s == 0) {
				sector_number += 1;
			}
		    pl->s = s;
			pl->f = GREEN;
   			pl->n = ROCK1;
   			if (s==0)
   				pl->n = FENCE;
   			if (s==2)
   				pl->n = 11;
			if (engine_cross(pl) == 0)
				continue;
			pl->ceil.yceil = pl->sect->ceil - pl->where.z;
			pl->floor.yfloor = pl->sect->floor - pl->where.z;
			neib = pl->sect->neighbors[s];
			if(neib >= 0)
			{
				pl->ceil.nyceil  = pl->sectors[neib].ceil  - pl->where.z;
				pl->floor.nyfloor = pl->sectors[neib].floor - pl->where.z;
			}
			if (engine_scale(pl, pl->cycle.current->sx1, pl->cycle.current->sx2) == 0)
				continue;

            engine_put_lines(pl, neib);
		}
        ++pl->cycle.rend_sec[pl->cycle.current->sec_nb];
    }
	free(pl->cycle.rend_sec); 
}
