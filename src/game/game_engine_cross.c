/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine_cross.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nshelly <nshelly@student.21school.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:32:04 by nshelly           #+#    #+#             */
/*   Updated: 2020/02/15 19:17:56 by nshelly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			xy_vertex_of_sectors(t_new_xy *v_start, t_new_xy *v_end,\
	t_new_player *pl)
{
	v_start->x = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 0].x \
	- pl->where.x;
	v_start->y = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 0].y - \
	pl->where.y;
	v_end->x = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 1].x - \
	pl->where.x;
	v_end->y = pl->sectors[pl->cycle.current->sec_nb].vertex[pl->s + 1].y - \
	pl->where.y;
	pl->t1.x = v_start->x * pl->anglesin - v_start->y * pl->anglecos;
	pl->t1.y = v_start->x * pl->anglecos + v_start->y * pl->anglesin;
	pl->t2.x = v_end->x * pl->anglesin - v_end->y * pl->anglecos;
	pl->t2.y = v_end->x * pl->anglecos + v_end->y * pl->anglesin;
}

/*
** Acquire the x,y coordinates of the two endpoints
** (vertices) of this edge of the sector
** also rotate them around the player's view
*/

static void		engine_cross2(t_new_player *pl, t_new_xy i1, t_new_xy i2)
{
	pl->org1.x = pl->t1.x;
	pl->org1.y = pl->t1.y;
	pl->org2.x = pl->t2.x;
	pl->org2.y = pl->t2.y;
	(pl->t1.y < pl->nearz && i1.y > 0) ? pl->t1 = i1 : pl->t1;
	(pl->t1.y < pl->nearz && i1.y < 0) ? pl->t1 = i2 : pl->t1;
	(pl->t2.y < pl->nearz && i1.y > 0) ? pl->t2 = i1 : pl->t2;
	(pl->t2.y < pl->nearz && i1.y < 0) ? pl->t2 = i2 : pl->t2;
	if (fabsf(pl->t2.x - pl->t1.x) > fabsf(pl->t2.y - pl->t1.y))
	{
		pl->u0 = ((pl->t1.x - pl->org1.x) * 1000 / (pl->org2.x - pl->org1.x));
		pl->u1 = ((pl->t2.x - pl->org1.x) * 1000 / (pl->org2.x - pl->org1.x));
	}
	else
	{
		pl->u0 = ((pl->t1.y - pl->org1.y) * 1000 /
				(pl->org2.y - pl->org1.y));
		pl->u1 = ((pl->t2.y - pl->org1.y) * 1000 /
				(pl->org2.y - pl->org1.y));
	}
}

/*
** **************************************************************************
**	int engine_cross(t_new_player *pl, int sec_n, unsigned s)
**	Function to find intersections and set t1 & t2
**	t1.y was tz1 before recontruction
** **************************************************************************
*/

int				engine_cross(t_new_player *pl)
{
	t_new_xy	i1;
	t_new_xy	i2;
	t_new_xy	v_start;
	t_new_xy	v_end;

	xy_vertex_of_sectors(&v_start, &v_end, pl);
	if ((pl->t1.y <= 0) && (pl->t2.y <= 0))
	{
		return (0);
	}
	pl->u0 = 0;
	pl->u1 = 1000;
	if ((pl->t1.y <= 0) || (pl->t2.y <= 0))
	{
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i1 = intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		pl->near_point.x = pl->near_point.x * (-1);
		pl->far_point.x = pl->far_point.x * (-1);
		i2 = intersect(pl->t1, pl->t2, pl->near_point, pl->far_point);
		if (i1.y < 0 && i2.y < 0)
			return (0);
		engine_cross2(pl, i1, i2);
	}
	return (1);
}
